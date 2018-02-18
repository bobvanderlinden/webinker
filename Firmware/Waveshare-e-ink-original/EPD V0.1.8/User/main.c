#include "stm32f10x.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "epd.h"
#include "gui.h"
#include "ff.h"
#include "sdcard.h"
#include "arm_cortex_m.h"


													
FATFS fs;                                                                                     //MMC工作区											 
															 
/*
全局函数
*/
void NVIC_Configuration(void);


/*******************************************************************************
* Function Name  : NVIC_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /*
	NVIC
	*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                                         //外部唤醒中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
}



int main(void)
{ 
  FRESULT fresult;                                                      //文件系统操作结果码	

	
  SystemInit();
  NVIC_Configuration();
	CM3_SysTickInit(72000000);
	
	/*
	仅开启SW调试接口
	*/
	RCC->APB2ENR |= 0x0001;                                               //使能AFIO时钟
	AFIO->MAPR &= ~(0x07 << 24);                                          //只启用SW调试接口
	AFIO->MAPR |= 0x02 << 24;	
	
	epd_hard_init();
	
	/*
	EPD初始化
	*/
  gui_init();
	gui_color.bkcolor = WHITE;
	gui_color.color = BLACK;		
	
	/*
	TF initinall
	*/
	fresult = f_mount(&fs, "0:", 1);                                      //文件系统初始化
	if(FR_OK != fresult)                                                  //文件系统初始化失败, LED闪烁提示
	{                 
		epd_led(LED_OPEN); 
		CM3_SysTickDelayMS(100);
		epd_led(LED_CLOSE);
		CM3_SysTickDelayMS(100);
		
		epd_led(LED_OPEN); 
		CM3_SysTickDelayMS(100);
		epd_led(LED_CLOSE);
		CM3_SysTickDelayMS(100);
		
		epd_led(LED_OPEN); 
		CM3_SysTickDelayMS(100);
		epd_led(LED_CLOSE);
		CM3_SysTickDelayMS(100);		
	}
	
	epd_led(LED_OPEN);                                                    //指示灯点亮, 正常进入系统
	gui_clear();
	epd_update(UPDATE_ALL);
	/*
	read fifo and generate command frame
	*/
  while(1)
	{
	}
}



























