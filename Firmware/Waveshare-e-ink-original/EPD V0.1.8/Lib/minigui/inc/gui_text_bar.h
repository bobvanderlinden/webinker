/*********************************************************************************
*
*�ļ���  ��gui_text_bar.h
*
*�ļ��������ı����ؼ�
*
*������  ��������, 20141017
*
*�汾��  ��1.0
*
*�޸ļ�¼��
*
*********************************************************************************/
#ifndef    GUI_TEXT_BAR_H
  #define  GUI_TEXT_BAR_H

/*
�ı���������Ϣ
*/
typedef struct
{
	int x0, y0;                                                               //�������
	int xsize;                                                                //�ı������
	int line_hight;                                                           //ÿ�еĸ߶�
	int m;                                                                    //�ı�������
	int line_color;                                                           //�ָ�������ɫ
	int bar_color;                                                            //�ı�������ɫ
	int unsel_color;                                                          //δѡ������ǰ��ɫ
	int unsel_bkcolor;                                                        //δѡ�����屳��ɫ
	int sel_color;                                                            //ѡ��������ɫ
	int sel_bkcolor;                                                          //ѡ�����屳��ɫ
} GUI_TEXT_BAR_INFO;


typedef struct
{
	int x0;
	int y0;
} GUI_TEXT_BAR_POS;

/*
�ı���
*/
typedef struct
{
	GUI_TEXT_BAR_INFO bar_info;                                               //��ʼ����Ϣ
	GUI_TEXT_BAR_POS line_pos[20];                                            //ÿ���ı�����ʾ�������
} GUI_TEXT_BAR;
	
	
	
	
	
GUI_TEXT_BAR * gui_create_text_bar(GUI_TEXT_BAR_INFO * p);

void gui_text_bar_active(GUI_TEXT_BAR * p, int m, const unsigned char * ptr, int n);
	
	
	
#endif



