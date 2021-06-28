/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-14 19:03:53
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-11-30 11:36:10
 * @FilePath     : \Simple_TeenyUSB_TX\USER\hex2bin.c
 */
#include "hex2bin.h"
#include <stdio.h>
#include "ff.h"
#include "oled.h"
#include "string.h"
static uint8_t HexCharToBinBinChar(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	return 0xff;
}

static uint8_t Hex2Bin(const char *p)
{
	uint8_t tmp = 0;
	tmp = HexCharToBinBinChar(p[0]);
	tmp <<= 4;
	tmp |= HexCharToBinBinChar(p[1]);
	return tmp;
}
/********************************************************************************
input:
	src: hex单行字符串
	p->type: 如果函数返回结果正确，这里就存着转化后的类型
	p->len: 如果函数运行正确，这里就存着转化后的bin数据长度
	p->data: 如果函数运行正确，长度并且不为0，该指针就只想转化后的数据
	p->addr[0]: 如果函数返回结果正确，这里就存着地址的低字节
	p->addr[1]: 如果函数返回结果正确，这里就存着地址的低字节
output:
	返回hex格式流分析的结果
********************************************************************************/
static RESULT_STATUS HexFormatUncode(const char *src, BinFarmat *p)
{
	uint8_t check = 0, tmp[4], binLen;
	uint16_t hexLen = strlen(src);
	uint16_t num = 0, offset = 0;
	if (hexLen > HEX_MAX_LENGTH) //数据内容过长
		return F_RES_DATA_TOO_LONG;
	if (hexLen < HEX_MIN_LEN)
		return F_RES_DATA_TOO_SHORT; //数据内容过短
	if (src[0] != ':')
		return F_RES_NO_COLON; //没有冒号
	if ((hexLen - 1) % 2 != 0)
		return F_RES_LENGTH_ERROR; //hexLen的长度应该为奇数
	binLen = (hexLen - 1) / 2;	   //bin总数据的长度，包括长度，地址，类型校验等内容
	while (num < 4)
	{
		offset = (num << 1) + 1;
		tmp[num] = Hex2Bin(src + offset);
		check += tmp[num];
		num++;
	}
	p->len = tmp[0]; //把解析的这些数据保存到结构体中
	p->addr = tmp[1];
	p->addr <<= 8;
	p->addr += tmp[2];
	p->type = tmp[3];
	while (num < binLen)
	{
		offset = (num << 1) + 1; //保存真正的bin格式数据流
		p->data[num - 4] = Hex2Bin(src + offset);
		check += p->data[num - 4];
		num++;
	}
	if (p->len != binLen - 5) //检查hex格式流的长度和数据的长度是否一致
		return F_RES_LENGTH_ERROR;
	if (check != 0) //检查校验是否通过
		return F_RES_CHECK_ERROR;
	return F_RES_OK;
}

RESULT_STATUS HexFile2BinFile(char *src, char *dest)
{
	FILE *src_file, *dest_file;
	FIL f_hex, f_bin;
	uint16_t addr_low = 0;
	uint32_t addr_hign = 0;
	char buffer_hex[600];
	uint8_t buffer_bin[255];
	BinFarmat gBinFor;
	RESULT_STATUS res;
	gBinFor.data = buffer_bin;
	src_file = fopen(src, "r"); //以文本的形式打开一个hex文件
	if (!src_file)
		return F_RES_HEX_FILE_NOT_EXIST;
	dest_file = fopen(dest, "wb"); //以二进制写的方式打开文件，文件不存在也没影响
	if (!dest_file)
		return F_RES_BIN_FILE_PATH_ERROR;
	fseek(src_file, 0, SEEK_SET); //定位到开头，准备开始读取数据

	f_open(&f_hex, (const TCHAR *)src, FA_READ);
	f_open(&f_bin, (const TCHAR *)"write.bin", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	OLED_Clear();
	OLED_ShowString(20, 2, "Inverting", 12, 1);

	while (!feof(src_file))
	{
		fscanf(src_file, "%s\r\n", buffer_hex);
		res = HexFormatUncode(buffer_hex, &gBinFor);
		if (res != F_RES_OK)
		{
			fclose(src_file);
			fclose(dest_file);
			return res;
		}
		switch (gBinFor.type)
		{
		case 0: //数据记录
			addr_low = gBinFor.addr;
			//数据指针偏移
			fseek(dest_file, addr_low + addr_hign, SEEK_SET);
			f_lseek(&f_bin, addr_low + addr_hign);
			for (uint32_t i = 0; i < gBinFor.len; i++)
				f_putc(gBinFor.data[i], &f_bin);
			if (fwrite((const uint8_t *)gBinFor.data, gBinFor.len, 1, dest_file) != 1)
			{
				fclose(src_file);
				fclose(dest_file);
				return F_RES_WRITE_ERROR;
			}
			break;
		case 1: //数据结束
			fclose(src_file);
			fclose(dest_file);
			return F_RES_OK;
		case 2:
			addr_hign = ((uint32_t)gBinFor.addr) << 2;
			break;
		case 4: //线性段地址
			addr_hign = ((uint32_t)gBinFor.addr) << 16;
			break;
		default:
			fclose(src_file);
			fclose(dest_file);
			return F_RES_TYPE_ERROR;
		}
	}
	f_close(&f_bin);
	fclose(src_file);
	fclose(dest_file);
	return F_RES_HEX_FILE_NO_END;
}

// char HexFormatUncode(unsigned char *File)
// {
// 	FIL fp_hex, fp_bin;
// 	char buff[64] = "";
// 	unsigned char length = 0;
// 	unsigned short offset = 0; //0~65535
// 	unsigned char type = 0;
// 	//	unsigned char checksum = 0;
// 	unsigned char i = 0;
// 	f_open(&fp_hex, (const TCHAR *)File, FA_READ);
// 	f_open(&fp_bin, (const TCHAR *)"write.bin", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
// 	OLED_Clear();
// 	OLED_ShowString(20, 2, "Inverting", 12, 1);
// 	while (f_gets(buff, 64, &fp_hex) != NULL)
// 	{
// 		if (buff[0] != ':')
// 			return 0;
// 		else
// 		{
// 			length = Char2toByte(&buff[1]);
// 			offset = Char2toByte(&buff[3]) * 256 + Char2toByte(&buff[5]);
// 			type = Char2toByte(&buff[7]);
// 			if (type == 0)
// 			{
// 				f_lseek(&fp_bin, offset);
// 				for (i = 0; i < length; i++)
// 					f_putc(Char2toByte(&buff[9 + 2 * i]), &fp_bin);
// 			}
// 		}
// 	}
// 	f_close(&fp_bin);
// 	f_close(&fp_hex);
// 	return 1;
// }
