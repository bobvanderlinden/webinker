/*************************************************************
*
*�ļ���  ��lcd_l0.c
*
*�ļ�������minigui �ײ�ӿ��ļ�,����ʵ����LCD����
           ʵ�ֵĹ��ܺ�������
					 1. void lcd_on(void);                                   ���⿪
					 2. void lcd_off(void);                                  �����
					 3. void lcd_l0_init(void);                              lcd��ʼ��
					 4. void lcd_l0_setpixel(int x, int y, int pixel);       ����
					 5. int lcd_l0_getpixel(int x, int y);                   ����
					 6. void lcd_l0_draw_hline(int x0, int y, int x1);       ��ˮƽ��
					 7. void lcd_l0_draw_vline(int x, int y0, int y1);       ����ֱ��
					 8. void lcd_l0_fillrect(int x0, int x1, int y0, int y1);���������
*
*������  ��������, 20140509
*
*�汾��  ��1.0
*
*�޸ļ�¼��
*
*************************************************************/
#ifndef    LCD_L0_H
  #define  LCD_L0_H

/*
LCD ״̬
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


