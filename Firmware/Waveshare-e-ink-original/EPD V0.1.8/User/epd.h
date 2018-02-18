/*********************************************************************************************************
*
* File                : epd.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.74
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/
#ifndef    EPD_H
  #define  EPD_H
#include "stm32f10x.h"
#include "string.h"
#include "stdio.h"

/*
define color
*/
#define        WHITE        0xFF
#define        GRAY         0xAA
#define        DARK_GRAY    0x55
#define        BLACK        0x00

/*
LCD pixel
*/
#define        phy_xsize    800
#define        phy_ysize    600

#define        vir_xsize    400
#define        vir_ysize    300

/*
update mode
*/
#define        UPDATE_ALL   0
#define        UPDATE_PART  1
	
#define        LED_OPEN     0
#define        LED_CLOSE    1

void epd_init(void);
void epd_led(int mode);
void epd_set_direction(int dir);
int epd_get_direction(void);
void epd_clear(u8 color);
void epd_update(int mode);
void epd_draw_pixel(int x0, int y0, int color);
int epd_get_pixel(int x0, int y0);





#define        FILE_NAME_MAX    16                                         //�ļ�������
#define        PAGE_SIZE        2048                                       //�ɶ�дҳ�Ĵ�С
#define        PAGE_PER_BLOCK   64                                         //ÿ�� Block ��64��Page


#define        NAND_FONT             0                                     //�ֿ���
#define        NAND_PICTURE          1                                     //ͼƬ��


/*
�ļ���Ϣ�ṹ��
*/
typedef struct
{
	char filename[FILE_NAME_MAX];                                            //�ļ���
	int file_size;                                                           //�ļ���С, �ֽڵ�λ
	int index;                                                               //��ǰ�ļ���д����
	int start_page;                                                          //�ļ��洢��ʼ����
	int stop_page;                                                           //�ļ��洢��������
} F_FILE;



int load_font(void);
int load_bitmap(void);


/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t Maker_ID;
  uint8_t Device_ID;
  uint8_t Third_ID;
  uint8_t Fourth_ID;
}
NAND_IDTypeDef;

typedef struct 
{
  uint16_t Zone;
  uint16_t Block;
  uint16_t Page;
} 
NAND_ADDRESS;




/*
FONT
*/
#define    GBK32                              0x01
#define    GBK48                              0x02
#define    GBK64                              0x03

#define    FONT24                             0x00
#define    FONT32                             0x01
#define    FONT48                             0x02
#define    FONT64                             0x03


/*
Memory Mode
*/
#define    MEM_NAND                           0
#define    MEM_TF                             1

/*
��Ļ��ʾ��������
*/
#define    EPD_NORMAL                         0                                                        //��Ļ������ʾ����, PCBģ������˿ӡ���ұ�
#define    EPD_INVERSION                      1                                                        //��Ļ��ת��ʾ, PCBģ��˿ӡ�����


extern unsigned char memory_mode;



typedef		unsigned char							BYTE;									//8 bit
typedef		unsigned short 						WORD;									//16 bit ,2 BYTE
typedef   unsigned long							DWORD;								//32 bit ,4 BYTE
typedef		long 						          LONG;

/*

λͼ�ļ�����ɣ�
1.λͼ�ļ�ͷ
2.λͼ��Ϣͷ
3.��ɫ��(��ɫ��)
4.ͼ����������

*/

/*
λͼ�ļ�ͷ   14Bytes
*/
#pragma pack(2)																						//˫�ֽڶ���
typedef struct{
	WORD	bfType;																						//�ļ�����,0x42 0x4D BM
	DWORD	bfSize;																						//�����ļ��Ĵ�С
	WORD	bfReserved0;																			//����
	WORD  bfReserved1;																			//����
	DWORD	bfOffBytes;																			  //λͼ���ݵĴ�ͷ��ʼƫ�Ƶ��ֽ���
} BITMAP_FILE_HEADER;
/*
λͼ��Ϣͷ   40Bytes
*/
typedef struct{
	DWORD biSize;																						//��Ϣͷ��С 40 Bytes
	LONG	biWidth;																					//λͼ��
	LONG	biHeight;																					//λͼ��
	WORD  biPlanes;																					//������1
	WORD	biBitCount;																				//��ʾ��ɫ��Ҫ�õ���λ��. 1(�ڰ�) 4(16ɫ) 8(256ɫ) 24(���ɫ)
	DWORD	biCompression;																		//ָ��λͼ�Ƿ�ѹ��
	DWORD biSizeImage;																			//λͼ���ص�ֵ
	LONG	biXPelsPerMeter;																	//�豸ˮƽ�ֱ���
	LONG  biYPelsPerMeter;																	//�豸��ֱ�ֱ���
	DWORD biClrUsed;																				//ʵ���õ�����ɫ��,��Ϊ0 ����ɫ��λ2�� biBitCount
	DWORD	biClrImportant;																		//ָ����Ҫ����ɫ��,��Ϊ0 ����Ҫ
} BITMAP_INFO_HEADER;
#pragma pack()
/*
λͼ��ɫ��
*/
#pragma pack(1)	
typedef struct{
	BYTE	rgbBlue;																					//��ɫ����
	BYTE	rgbGreen;																					//��ɫ����
	BYTE  rgbRed;																						//��ɫ����
	BYTE  rgbReserved;																			//����
} RGBQUAD;
#pragma pack()

int DrawBitmap(char *pFileName, DWORD x, DWORD y);




void epd_hard_init(void);

	
	
#endif



