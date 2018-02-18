/*********************************************************************************
*
*文件名  ：gui_text_bar.h
*
*文件描述：文本条控件
*
*创建人  ：阎文来, 20141017
*
*版本号  ：1.0
*
*修改记录：
*
*********************************************************************************/
#ifndef    GUI_TEXT_BAR_H
  #define  GUI_TEXT_BAR_H

/*
文本条创建信息
*/
typedef struct
{
	int x0, y0;                                                               //起点坐标
	int xsize;                                                                //文本条宽度
	int line_hight;                                                           //每行的高度
	int m;                                                                    //文本条行数
	int line_color;                                                           //分隔线条颜色
	int bar_color;                                                            //文本条背景色
	int unsel_color;                                                          //未选择字体前景色
	int unsel_bkcolor;                                                        //未选择字体背景色
	int sel_color;                                                            //选择字体颜色
	int sel_bkcolor;                                                          //选择字体背景色
} GUI_TEXT_BAR_INFO;


typedef struct
{
	int x0;
	int y0;
} GUI_TEXT_BAR_POS;

/*
文本条
*/
typedef struct
{
	GUI_TEXT_BAR_INFO bar_info;                                               //初始化信息
	GUI_TEXT_BAR_POS line_pos[20];                                            //每个文本条显示起点坐标
} GUI_TEXT_BAR;
	
	
	
	
	
GUI_TEXT_BAR * gui_create_text_bar(GUI_TEXT_BAR_INFO * p);

void gui_text_bar_active(GUI_TEXT_BAR * p, int m, const unsigned char * ptr, int n);
	
	
	
#endif



