#include "stm32f10x.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "epd.h"
#include "gui.h"
#include "ff.h"
#include "sdcard.h"
#include "arm_cortex_m.h"


													
FATFS fs;                                                                                     //MMC������											 
															 
/*
ȫ�ֺ���
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
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                                         //�ⲿ�����ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
}



int main(void)
{ 
  FRESULT fresult;                                                      //�ļ�ϵͳ���������	

	
  SystemInit();
  NVIC_Configuration();
	CM3_SysTickInit(72000000);
	
	/*
	������SW���Խӿ�
	*/
	RCC->APB2ENR |= 0x0001;                                               //ʹ��AFIOʱ��
	AFIO->MAPR &= ~(0x07 << 24);                                          //ֻ����SW���Խӿ�
	AFIO->MAPR |= 0x02 << 24;	
	
	epd_hard_init();
	
	/*
	EPD��ʼ��
	*/
  gui_init();
	gui_color.bkcolor = WHITE;
	gui_color.color = BLACK;		
	
	/*
	TF initinall
	*/
	fresult = f_mount(&fs, "0:", 1);                                      //�ļ�ϵͳ��ʼ��
	if(FR_OK != fresult)                                                  //�ļ�ϵͳ��ʼ��ʧ��, LED��˸��ʾ
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
	
	epd_led(LED_OPEN);                                                    //ָʾ�Ƶ���, ��������ϵͳ
	gui_clear();
	epd_update(UPDATE_ALL);
	/*
	read fifo and generate command frame
	*/
  while(1)
	{
	}
}



























