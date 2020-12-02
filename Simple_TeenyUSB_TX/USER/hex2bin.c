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

unsigned char ChartoByte(char c)
{
	if (c - 'a' >= 0)
		return (c - 'a' + 10);
	else if (c - 'A' >= 0)
		return (c - 'A' + 10);
	else
		return (c - '0');
}

unsigned char Char2toByte(char *s)
{
	return (ChartoByte(*s) * 16 + ChartoByte(*(s + 1)));
}

char HexFormatUncode(unsigned char *File)
{
	FIL fp_hex, fp_bin;
	char buff[64] = "";
	unsigned char length = 0;
	unsigned short offset = 0; //0~65535
	unsigned char type = 0;
//	unsigned char checksum = 0;
	unsigned char i = 0;
	f_open(&fp_hex, (const TCHAR *)File, FA_READ);
	f_open(&fp_bin, (const TCHAR *)"write.bin", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	OLED_Clear();
	OLED_ShowString(20, 2, "Inverting", 12, 1);
	while (f_gets(buff, 64, &fp_hex) != NULL)
	{
		if (buff[0] != ':')
			return 0;
		else
		{
			length = Char2toByte(&buff[1]);
			offset = Char2toByte(&buff[3]) * 256 + Char2toByte(&buff[5]);
			type = Char2toByte(&buff[7]);
			if (type == 0)
			{
				f_lseek(&fp_bin, offset);
				for (i = 0; i < length; i++)
					f_putc(Char2toByte(&buff[9 + 2 * i]), &fp_bin);
			}
		}
	}
	f_close(&fp_bin);
	f_close(&fp_hex);
	return 1;
}

