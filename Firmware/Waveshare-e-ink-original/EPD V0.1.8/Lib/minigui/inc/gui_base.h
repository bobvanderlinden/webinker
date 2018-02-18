/**********************************************************************
*
*文件名  ：gui_base.h
*
*文件描述：基本的绘图接口
*
*创建人  ：阎文来, 20140509
*
*版本号  ：1.0
*
*修改记录：
*
**********************************************************************/
#ifndef    GUI_BASE_H
  #define  GUI_BASE_H
	

/*
位图信息结构体
*/
typedef struct
{
	int xsize;
	int ysize;
	int bits_perpixel;
	int bytes_perline;
	const unsigned char * pdata;
}GUI_BITMAP;

	
#include "gui_color.h"
#include "lcd_l0.h"	
#include "lcd_conf.h"




void gui_drawarc(int x0, int y0, int rx, int ry, int a0, int a1);
void gui_clear(void);
void gui_drawpixel(int x, int y);
int gui_getpixel(int x, int y);
void gui_drawline(int x0, int y0, int x1, int y1);
void gui_fillrect(int x0, int y0, int x1, int y1);
void gui_draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2);

void gui_draw_bitmap(int x, int y, const GUI_BITMAP * p);

#endif


