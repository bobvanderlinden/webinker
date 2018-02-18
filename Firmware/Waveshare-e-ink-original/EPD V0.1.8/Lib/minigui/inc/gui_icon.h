/*********************************************************************
*
*�ļ���  ��gui_icon.h
*
*�ļ�������ͼ�깦�ܼ�
*
*������  ��������, 20141008
*
*�汾��  ��1.0
*
*�޸ļ�¼��
*
*********************************************************************/
#ifndef    GUI_ICON_H
  #define  GUI_ICON_H
#include "gui_base.h"
#include "gui_font.h"
/*
�ṹ�嶨��
*/
typedef struct
{
	int   text_mode;                                                //���ֻ���ģʽ
	int   color;                                                    //����ǰ��ɫ
	int   bkcolor;                                                  //���ֱ���ɫ
	const unsigned char * * ptr_text;                               //ͼ������ָ��
} GUI_ICON_TEXT_INFO;

typedef struct
{
	int icon_mode;                                                  //ͼ��ģʽ, 0 :��ɫ  1 :λͼ���
	int text_pos;                                                   //����ģʽ, 0: ���� 1: �ϱ��� 2: �±���
	int x0, y0;                                                     //��ʾ�������
	int xsize, ysize;                                               //ͼ���С
	int icon_color;                                                 //��ɫͼ�����ɫ
	const GUI_BITMAP * pbitmap;                                     //λͼ����
	const GUI_ICON_TEXT_INFO * ptr_text_info;                       //�ı���Ϣ
} GUI_ICON_INFO;

/*
��������
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

