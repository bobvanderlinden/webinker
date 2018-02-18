/***************************************************************************
*
*文件名  ：gui_widget_lcdseg.h
*
*文件描述：段码控件
*
*创建人  ：阎文来, 20141020
*
*版本号  ：1.0
*
*修改记录：
*
***************************************************************************/
#ifndef    GUI_WIDGET_LCDSEG_H
  #define  GUI_WIDGET_LCDSEG_H

typedef int    GUI_WIDGET_LCDSEG_HANDLE;

typedef struct
{
	int color;
	int bkcolor;
	int x0, y0;                                                           //数字显示起点坐标
	int length, width;                                                    //每个段的长宽
} GUI_WIDGET_LCDSEG_INFO;


void gui_widget_lcdseg_init(void);

GUI_WIDGET_LCDSEG_HANDLE gui_widget_lcdseg_create(GUI_WIDGET_LCDSEG_INFO * p);

void gui_widget_dispnum(GUI_WIDGET_LCDSEG_HANDLE handle, int m);
	
#endif






