/*********************************************************************
*
*文件名  ：gui_icon.h
*
*文件描述：图标功能集
*
*创建人  ：阎文来, 20141008
*
*版本号  ：1.0
*
*修改记录：
*
*********************************************************************/
#ifndef    GUI_ICON_H
  #define  GUI_ICON_H
#include "gui_base.h"
#include "gui_font.h"
/*
结构体定义
*/
typedef struct
{
	int   text_mode;                                                //文字绘制模式
	int   color;                                                    //文字前景色
	int   bkcolor;                                                  //文字背景色
	const unsigned char * * ptr_text;                               //图标名称指针
} GUI_ICON_TEXT_INFO;

typedef struct
{
	int icon_mode;                                                  //图标模式, 0 :纯色  1 :位图填充
	int text_pos;                                                   //文字模式, 0: 居中 1: 上边沿 2: 下边沿
	int x0, y0;                                                     //显示起点坐标
	int xsize, ysize;                                               //图标大小
	int icon_color;                                                 //纯色图标的颜色
	const GUI_BITMAP * pbitmap;                                     //位图数据
	const GUI_ICON_TEXT_INFO * ptr_text_info;                       //文本信息
} GUI_ICON_INFO;

/*
常量定义
*/
#define  GUI_ICONMODE_COLOR                       0
#define  GUI_ICONMODE_BITMAP                      1

#define  GUI_ICONTEXT_CENTER                      0
#define  GUI_ICONTEXT_UP                          1
#define  GUI_ICONTEXT_DOWN                        2

#define  GUI_ICONTEXT_MODE_NORMAL                 0
#define  GUI_ICONTEXT_MODE_TRANS                  1
#define  GUI_ICONTEXT_MODE_NONE                   2


	





void gui_set_icon_lang(int lang);
void gui_draw_icon(const GUI_ICON_INFO * ptr);
void gui_active_icon(const GUI_ICON_INFO * ptr, int m);


	
	
#endif

