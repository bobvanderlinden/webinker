/*************************************************************
*
*文件名  ：lcd_l0.c
*
*文件描述：minigui 底层接口文件,用于实现与LCD连接
           实现的功能函数包括
					 1. void lcd_on(void);                                   背光开
					 2. void lcd_off(void);                                  背光关
					 3. void lcd_l0_init(void);                              lcd初始化
					 4. void lcd_l0_setpixel(int x, int y, int pixel);       画点
					 5. int lcd_l0_getpixel(int x, int y);                   读点
					 6. void lcd_l0_draw_hline(int x0, int y, int x1);       画水平线
					 7. void lcd_l0_draw_vline(int x, int y0, int y1);       画垂直线
					 8. void lcd_l0_fillrect(int x0, int x1, int y0, int y1);绘制填充区
*
*创建人  ：阎文来, 20140509
*
*版本号  ：1.0
*
*修改记录：
*
*************************************************************/
#ifndef    LCD_L0_H
  #define  LCD_L0_H

/*
LCD 状态
*/
typedef struct
{
	int bklight;
} LCD_STATUS;

	
#include "epd.h"
#include "gui.h"





extern LCD_STATUS lcd_status;
	

void lcd_on(void);
void lcd_off(void);
void lcd_l0_init(void);
void lcd_l0_setpixel(int x, int y, int pixel);
int lcd_l0_getpixel(int x, int y);
void lcd_l0_draw_hline(int x0, int y, int x1);
void lcd_l0_draw_vline(int x, int y0, int y1);
void lcd_l0_fillrect(int x0, int y0, int x1, int y1);
void lcd_l0_drawbitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const unsigned char * pData);

	
	
#endif


