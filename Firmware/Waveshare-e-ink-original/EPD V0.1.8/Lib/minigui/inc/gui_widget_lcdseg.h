/***************************************************************************
*
*�ļ���  ��gui_widget_lcdseg.h
*
*�ļ�����������ؼ�
*
*������  ��������, 20141020
*
*�汾��  ��1.0
*
*�޸ļ�¼��
*
***************************************************************************/
#ifndef    GUI_WIDGET_LCDSEG_H
  #define  GUI_WIDGET_LCDSEG_H

typedef int    GUI_WIDGET_LCDSEG_HANDLE;

typedef struct
{
	int color;
	int bkcolor;
	int x0, y0;                                                           //������ʾ�������
	int length, width;                                                    //ÿ���εĳ���
} GUI_WIDGET_LCDSEG_INFO;


void gui_widget_lcdseg_init(void);

GUI_WIDGET_LCDSEG_HANDLE gui_widget_lcdseg_create(GUI_WIDGET_LCDSEG_INFO * p);

void gui_widget_dispnum(GUI_WIDGET_LCDSEG_HANDLE handle, int m);
	
#endif






