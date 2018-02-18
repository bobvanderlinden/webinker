#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "gde043a2.h"
#include "sram.h"
#include "usart.h"
#include "imgdec.h"
#include "config.h"

// Add images
#include "images/ap_setup.h"
//#include "images/lost_connection.h"
//#include "images/low_battery.h"
//#include "images/sleep.h"
//#include "images/dhcp_error.h"
//#include "images/dns_error.h"
//#include "images/connection_error.h"
//#include "images/invalid_image.h"

#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_pwr.h>
#include <system_stm32f10x.h>

// Prototypes
extern void initialise_monitor_handles(void);

void initHW() {
	// Init basic stuff
	SystemInit();

	/* Debug support for low power modes: */
	DBGMCU_Config(DBGMCU_SLEEP, ENABLE);
	DBGMCU_Config(DBGMCU_STOP, ENABLE);
	DBGMCU_Config(DBGMCU_STANDBY, ENABLE);

	// Enable clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	// Disable the fucking JTAG!
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

	//GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
}

void sync_blink() {
	// Some blink
	int i;
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	for (i = 0; i < 300000; i++) { asm volatile(""); }
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
	for (i = 0; i < 300000; i++) { asm volatile(""); }
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	for (i = 0; i < 300000; i++) { asm volatile(""); }
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
	for (i = 0; i < 300000; i++) { asm volatile(""); }
}

const void * image_table[1] =
{
	ap_setup,
	//lost_connection,
	//low_battery,
	//sleep_mode,
	//dhcp_error,
	//dns_error,
	//connection_error,
	//invalid_image
};

unsigned char scratch[(800*600*2)/8] __attribute__((section(".extdata"), used));

void GPIO_Initialize()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	// Configure PB3 as LED output
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure PA9 / PA10 as UART1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);

}

uint8_t USART_Receive_Task()
{
	uint32_t timeout = 0;

	// Wait for the first byte, that tells us what to do:
	while(TM_USART_BufferEmpty(USART1) == SET);
	unsigned char cmd = TM_USART_Getc(USART1);

	// Bit   7 defines direction hint (which can be ignored by the device)
	// Bit   6 tells whether to show a predefined picture (0) or to load a picture (1)
	//         If the bit is 1, it will be followed by 120000 bytes with the picture content
	// Bit   5 indicates whether the battery icon should be overlayed to the image
	// Bit 2,0 defines which preloaded picture to show (from the 4 in-ROM available)

	int direction = (cmd & 0x80) ? 1 : 0;
	int int_image = ((cmd & 0x40) == 0);
	int show_bat  = ((cmd & 0x20) == 0);
	int imageidx  =  cmd & 0x7;

	if (!int_image) {
		// Keep reading for external image!
		unsigned int spointer = 0;
		while (spointer < sizeof(scratch)) {
			// Read buffer to scratch!
			while(TM_USART_BufferEmpty(USART1) == SET) {
				if (timeout++ == 5000000) {
					sync_blink();
					return 0;
				}
			}
			scratch[spointer++] = TM_USART_Getc(USART1);
		}
	}
	else {
		// Copy the internal compressed image
		memcpy(scratch, image_table[imageidx], sizeof(scratch));
	}

	return 1;
}

int main() {
	// Init HW for the micro
	initHW();

	// Enable semihosting
#ifdef DEBUG
	initialise_monitor_handles();
#endif

	debug_print("Hallo\n");

	/* Initialize SRAM */
	FSMC_SRAM_Init();

	GPIO_Initialize();

	// Initialize USART1 on default pins
	TM_USART_Init(USART1, TM_USART_PinsPack_1, 1000000);

	sync_blink();

	// Initialize tables (according to direction)
	//einkd_init(direction);

	// Power ON, draw and OFF again!
	//einkd_PowerOn();
	//einkd_refresh_compressed(scratch);
	//einkd_PowerOff();

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, DISABLE);
	//einkd_deinit();

	// Turn ourselves OFF, hopefully save some power before final power gate off
	//PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

	// Clear the screenbuffer
	memset(scratch, 0xFF, sizeof(scratch));

	einkd_init(0);
	einkd_PowerOn();
	einkd_refresh(scratch);

	while (1) {
		//uint8_t c = TM_USART_Getc(USART1);
		//if (c)
		//	TM_USART_Putc(USART1, c);
		if (USART_Receive_Task()) {
			einkd_refresh(scratch);
			//einkd_PowerOff();
		}
	}

	return 0;
}


