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





#define        FILE_NAME_MAX    16                                         //文件名长度
#define        PAGE_SIZE        2048                                       //可读写页的大小
#define        PAGE_PER_BLOCK   64                                         //每个 Block 有64个Page


#define        NAND_FONT             0                                     //字库区
#define        NAND_PICTURE          1                                     //图片区


/*
文件信息结构体
*/
typedef struct
{
	char filename[FILE_NAME_MAX];                                            //文件名
	int file_size;                                                           //文件大小, 字节单位
	int index;                                                               //当前文件读写索引
	int start_page;                                                          //文件存储起始扇区
	int stop_page;                                                           //文件存储结束扇区
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
屏幕显示方向设置
*/
#define    EPD_NORMAL                         0                                                        //屏幕正常显示方向, PCB模块名称丝印在右边
#define    EPD_INVERSION                      1                                                        //屏幕反转显示, PCB模块丝印在左边


extern unsigned char memory_mode;



typedef		unsigned char							BYTE;									//8 bit
typedef		unsigned short 						WORD;									//16 bit ,2 BYTE
typedef   unsigned long							DWORD;								//32 bit ,4 BYTE
typedef		long 						          LONG;

/*

位图文件的组成：
1.位图文件头
2.位图信息头
3.彩色表(调色板)
4.图像数据阵列

*/

/*
位图文件头   14Bytes
*/
#pragma pack(2)																						//双字节对齐
typedef struct{
	WORD	bfType;																						//文件类型,0x42 0x4D BM
	DWORD	bfSize;																						//整个文件的大小
	WORD	bfReserved0;																			//保留
	WORD  bfReserved1;																			//保留
	DWORD	bfOffBytes;																			  //位图数据的从头开始偏移的字节数
} BITMAP_FILE_HEADER;
/*
位图信息头   40Bytes
*/
typedef struct{
	DWORD biSize;																						//信息头大小 40 Bytes
	LONG	biWidth;																					//位图宽
	LONG	biHeight;																					//位图高
	WORD  biPlanes;																					//必须是1
	WORD	biBitCount;																				//表示颜色需要用到的位数. 1(黑白) 4(16色) 8(256色) 24(真彩色)
	DWORD	biCompression;																		//指定位图是否压缩
	DWORD biSizeImage;																			//位图像素点值
	LONG	biXPelsPerMeter;																	//设备水平分辨率
	LONG  biYPelsPerMeter;																	//设备垂直分辨率
	DWORD biClrUsed;																				//实际用到的颜色数,若为0 则颜色数位2的 biBitCount
	DWORD	biClrImportant;																		//指定重要的颜色数,若为0 则都重要
} BITMAP_INFO_HEADER;
#pragma pack()
/*
位图调色板
*/
#pragma pack(1)	
typedef struct{
	BYTE	rgbBlue;																					//蓝色分量
	BYTE	rgbGreen;																					//绿色分量
	BYTE  rgbRed;																						//红色分量
	BYTE  rgbReserved;																			//保留
} RGBQUAD;
#pragma pack()

int DrawBitmap(char *pFileName, DWORD x, DWORD y);




void epd_hard_init(void);

	
	
#endif



