
#include "include.h"
#include "lcd_menu.h"
/*
*********************************************************************************************************
*    函 数 名: LCD_InitMenu
*    功能说明: 初始化菜单结构
*    形    参: _pMenu : 菜单结构体指针; 由主程序申请全局菜单结构体变量。
*             _Text : 菜单文本的数组指针。 由主程序分配空间保存数组
*    返 回 值: 无
*********************************************************************************************************
*/
void LCD_InitMenu(MENU_T *_pMenu, char **_Text)
{
   _pMenu->Text = _Text; /* 菜单文本 */
    for (uint8_t i = 0; i < 255; i++)
    {
        if (_pMenu->Text[i][0] == '&')
        {
            _pMenu->Count = i;
            break;
        }
    }
    _pMenu->Cursor = 0; /* 当前屏幕第1行对应的索引 */
    _pMenu->Offset = 0; /* 选中行的索引 */
}

/*
*********************************************************************************************************
*    函 数 名: LCD_ClearMenu
*    功能说明: 显示菜单 清屏
*    形    参: 
*    返 回 值: 无
*********************************************************************************************************
*/
void LCD_ClearMenu(MENU_T *_pMenu)
{
    OLED_Clear();
}

/*
*********************************************************************************************************
*    函 数 名: LCD_DispMenu
*    功能说明: 显示菜单 显示光标行
*    形    参: _pMenu : 菜单文字数组
*              _Count : 菜单项个数
*              _Cursor : 光标行
*              _FocusLine :  焦点行(0-3)
*    返 回 值: 无
*********************************************************************************************************
*/
void LCD_DispMenu(MENU_T *_pMenu)
{
    uint8_t i;
    uint8_t FontHeight;//字体大小
    uint16_t y;
    uint8_t line_cap1;

    FontHeight = _pMenu->Font;

    line_cap1 = _pMenu->LineCap / 2;         /* 菜单文本前的高度 */

    for (i = 0; i < _pMenu->ViewLine; i++)
    {
        if (i >= _pMenu->Count)
        {
            break;
        }

        if (i + _pMenu->Offset == _pMenu->Cursor)   /* 选钟行 */
        {
            /* 设置为反白 */
            y = _pMenu->Top + i * (FontHeight + _pMenu->LineCap);
            OLED_ShowString(_pMenu->Left, y + line_cap1,(uint8_t *)_pMenu->Text[_pMenu->Offset + i],_pMenu->Font,0);
        }
        else
        {
            y = _pMenu->Top + i * (FontHeight + _pMenu->LineCap);

            OLED_ShowString(_pMenu->Left, y + line_cap1,(uint8_t *)_pMenu->Text[_pMenu->Offset + i],_pMenu->Font,1);            
        }
    }
}

/*
*********************************************************************************************************
*    函 数 名: LCD_MoveDownMenu
*    功能说明: 向下移动选中的菜单行, 并刷新显示.
*    形    参: _pMenu : 菜单结构体指针
*    返 回 值: 无
*********************************************************************************************************
*/
void LCD_MoveDownMenu(MENU_T *_pMenu)
{
    if (_pMenu->Cursor < _pMenu->Count - 1)
    {
        _pMenu->Cursor++;

        if (_pMenu->Cursor - _pMenu->Offset >= _pMenu->ViewLine)
        {
            _pMenu->Offset++;
        }

        LCD_DispMenu(_pMenu); /* 刷新显示 */
    }
    else
    {
        if (_pMenu->RollBackEn == 1)    /* 回滚 */
        {        
            _pMenu->Cursor = 0;
            _pMenu->Offset = 0;
            LCD_DispMenu(_pMenu); /* 刷新显示 */
        }
    }
}

/*
*********************************************************************************************************
*    函 数 名: LCD_MoveUpMenu
*    功能说明: 向上移动选中的菜单行, 并刷新显示.
*    形    参: _pMenu : 菜单结构体指针
*    返 回 值: 无
*********************************************************************************************************
*/
void LCD_MoveUpMenu(MENU_T *_pMenu)
{
    if (_pMenu->Cursor > 0)
    {
        _pMenu->Cursor--;

        if (_pMenu->Cursor < _pMenu->Offset)
        {
            _pMenu->Offset--;
        }

        LCD_DispMenu(_pMenu); /* 刷新显示 */
    }
    else
    {
        if (_pMenu->RollBackEn == 1)    /* 回滚 */
        {
            _pMenu->Cursor = _pMenu->Count - 1;
            if (_pMenu->Count > _pMenu->ViewLine)
            {
                _pMenu->Offset = _pMenu->Count - _pMenu->ViewLine;
            }
            else
            {
                _pMenu->Offset = 0;
            }
            LCD_DispMenu(_pMenu); /* 刷新显示 */
        }
    }
}

