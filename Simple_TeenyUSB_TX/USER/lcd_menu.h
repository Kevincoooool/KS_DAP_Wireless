/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-12-01 18:45:56
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-02 09:33:22
 * @FilePath     : \Simple_TeenyUSB_TX\USER\lcd_menu.h
 */

#ifndef _LCD_MENU_H
#define _LCD_MENU_H
#include "stdint.h"
//#define CL_MENU_TEXT1   CL_WHITE
//#define CL_MENU_BACK1   MAIN_BACK_COLOR

///* 光标选中 */
//#define CL_MENU_TEXT2   CL_BLACK
//#define CL_MENU_BACK2   CL_YELLOW

///* 菜单选中，保留另外一个颜色 */
//#define CL_MENU_TEXT3   CL_BLACK
//#define CL_MENU_BACK3   RGB(142, 209, 158)
#if OLED_0_96
#define MENU_LEFT       (0 + 0)
#define MENU_TOP        (0 + 0)
#define MENU_WIDTH      128
#define MENU_HEIGHT     64
#define MENU_CAP        0
#else
#define MENU_LEFT       (0 + 0)
#define MENU_TOP        (0 + 0)
#define MENU_WIDTH      120
#define MENU_HEIGHT     32
#define MENU_CAP        0
#endif
/* 菜单结构 */
typedef struct
{
    char **Text;         /* 菜单文本 */
    uint8_t ViewLine;       /* 可视行数 */
    uint8_t Count;          /* 菜单项个数 */
    uint8_t Offset;         /* 当前屏幕第1行对应的索引 */
    uint8_t Cursor;         /* 选中行的索引 */

    uint16_t Left;          /* X 坐标 */
    uint16_t Top;           /* Y 坐标 */
    uint16_t Height;        /* 高度 */
    uint16_t Width;         /* 宽度 */
    uint16_t LineCap;       /* 行间距 */

    uint8_t RollBackEn;     /* 回滚使能 */
    uint8_t Font;     /* 回滚使能 */
    uint8_t GBK;            /* 文字编码 0=UTF8, 1=GBK */
    
    uint8_t ActiveBackColor;    /* 选中行背景色,0表示黄色 1表示参数修改状态 */
} MENU_T;

/* 菜单显示类 */
void LCD_InitMenu(MENU_T *_pMenu, char **_Text);
void LCD_DispMenu(MENU_T *_pMenu);
void LCD_MoveDownMenu(MENU_T *_pMenu);
void LCD_MoveUpMenu(MENU_T *_pMenu);
void LCD_ClearMenu(MENU_T *_pMenu);

#endif

