/***************************************************************
*
*�ļ���  ��gui.h
*
*�ļ�������minigui ���ĺ���
*
*������  ��������, 20140509
*
*�汾��  ��1.0
*
*�޸ļ�¼��
*
***************************************************************/
#ifndef    GUI_H
  #define  GUI_H
	
/*
gui ��ɫ�ṹ�� 
ǰ��ɫ�ͱ���ɫ
*/
typedef struct 
{
	int color;
	int bkcolor;
}GUI_COLOR;



#include "gui_base.h"
#include "gui_color.h"
#include "lcd_conf.h"
#include "gui_font.h"
#include "gui_conf.h"
#include "gui_icon.h"	
#include "gui_text_bar.h"
#include "gui_base_triangle.h"
#include "gui_base_circle.h"
#include "gui_widget_lcdseg.h"
#include "lcd_l0.h"

/*
��׼ɫ
*/
#define GUI_BLUE          0xFF0000
#define GUI_GREEN         0x00FF00
#define GUI_RED           0x0000FF
#define GUI_CYAN          0xFFFF00
#define GUI_MAGENTA       0xFF00FF
#define GUI_YELLOW        0x00FFFF
#define GUI_LIGHTBLUE     0xFF8080
#define GUI_LIGHTGREEN    0x80FF80
#define GUI_LIGHTRED      0x8080FF
#define GUI_LIGHTCYAN     0xFFFF80
#define GUI_LIGHTMAGENTA  0xFF80FF
#define GUI_LIGHTYELLOW   0x80FFFF
#define GUI_DARKBLUE      0x800000
#define GUI_DARKGREEN     0x008000
#define GUI_DARKRED       0x000080
#define GUI_DARKCYAN      0x808000
#define GUI_DARKMAGENTA   0x800080
#define GUI_DARKYELLOW    0x008080
#define GUI_WHITE         0xFFFFFF
#define GUI_LIGHTGRAY     0xD3D3D3
#define GUI_GRAY          0x808080
#define GUI_DARKGRAY      0x404040
#define GUI_BLACK         0x000000
#define GUI_BROWN         0x2A2AA5
	
#define GUI_USER_BLUE     0xA86400	

/*
��ͼģʽ,�����������
*/
#define GUI_DRAWMODE_NORMAL    0                                 //�����ı���ʾ
#define GUI_DRAWMODE_TRANS     1                                 //͸���ı���ʾ





extern GUI_COLOR gui_color;
extern int       gui_drawmode;

void gui_init(void);
void gui_set_drawmode(int mode);
#endif




