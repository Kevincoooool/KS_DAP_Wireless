#ifndef HEX2BIN_H
#define HEX2BIN_H
 
#include "stdint.h"
#define HEX_MAX_LENGTH		521
#define HEX_MIN_LEN		11
 
typedef enum {
	F_RES_OK = 0,		//正确
	F_RES_DATA_TOO_LONG,	//数据太长
	F_RES_DATA_TOO_SHORT,	//数据太短
	F_RES_NO_COLON,		//无标号
	F_RES_TYPE_ERROR,		//类型出错，或许不存在
	F_RES_LENGTH_ERROR,	//数据长度字段和内容的总长度不对应
	F_RES_CHECK_ERROR,	//校验错误
	F_RES_HEX_FILE_NOT_EXIST,	//HEX文件不存在
	F_RES_BIN_FILE_PATH_ERROR,//BIN文件路径可能不正确
	F_RES_WRITE_ERROR,	//写数据出错
	F_RES_HEX_FILE_NO_END	//hex文件没有结束符
} RESULT_STATUS;
 
typedef struct {
	uint8_t len;
	uint8_t	type;
	uint16_t addr;
	uint8_t *data;
} BinFarmat;
 
RESULT_STATUS HexFile2BinFile(char *src, char *dest);
#endif


