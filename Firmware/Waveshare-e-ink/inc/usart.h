/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2014/04/library-04-connect-stm32f429-discovery-to-computer-with-usart/
 * @version v2.5
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   USART Library for STM32F4 with receive interrupt
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */
#ifndef TM_USART_H
#define TM_USART_H 250

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup TM_STM32F10x_Libraries
 * @{
 */

/**
 * @defgroup TM_USART
 * @brief    TM USART Library for STM32F4xx - http://stm32f4-discovery.com/2014/04/library-04-connect-stm32f429-discovery-to-computer-with-usart/
 * @{
 *
 * <b>Library works for all 3 U(S)ARTs which are supported on STM32F10x devices.</b>
 * 
 * \par USART receive interrupt handlers
 *
 * Every USART channel has it's own receive interrupt which stores incoming data into cyclic buffer.
 * If you want to use your own receive handler, then you have to open defines.h files and set a define.
@verbatim
//Use custom IRQ Receive handler
//Change X with possible U(S)ARTs: USART1, USART2, USART3
#define TM_X_USE_CUSTOM_IRQ
@endverbatim
 * After you set define, you have to create a function, which will handle custom request
@verbatim
//Change X with possible U(S)ARTs: USART1, USART2, USART3
//Parameter c is a received character
void TM_X_ReceiveHandler(uint8_t c) {
   //Do your stuff here when byte is received
}
@endverbatim
 * @note If you use custom receive interrupt handler, then incoming data is not stored in internal buffer
 *
 * \par USART Internal cyclic buffer
 *
 * In your project you can set internal cyclic buffer length, default is 32Bytes, with:
@verbatim
//Set buffer sie for all buffers
#define USART_BUFFER_SIZE number_of_bytes
@endverbatim
 * in your project's defines.h file. This will set default length for each buffer.
 * So if you are working with F429 (it has 8 U(S)ARTs) then you will use 8kB RAM if 
 * you set define above to 1024.
 *
 * As of version 2.0, you can now set different buffer sizes for different U(S)ARTs.
 * If you don't change anything, then all USART's have buffer length of value, stored in
 * <code>USART_BUFFER_SIZE</code> define. If you want let's say just for USART1 to be 1kB, but others default value,
 * you can add define below in defines.h file:
@verbatim
//Buffer length for USART1 is 1kB, for others is still TM_USART_BUFFER_SIZE
#define TM_USART1_BUFFER_SIZE 1024
@endverbatim
 *
 * Other possible settings are (for other U(S)ARTs):
 *   - TM_USART1_BUFFER_SIZE
 *   - TM_USART2_BUFFER_SIZE
 *   - TM_USART3_BUFFER_SIZE
 *	
 * \par Custom string delimiter for @ref TM_USART_Gets() function
 * 
 * As of version 2.5, you can now set custom string delimiter for @ref TM_USART_Gets() function.
 * By default, LF (Line Feed) character was used, but now you can select custom character using @ref TM_USART_SetCustomStringEndCharacter() function.
 *
 * \par Pinout
 *
@verbatim
             |PINSPACK 1     |PINSPACK 2     |PINSPACK 3	
U(S)ARTX     |TX     RX      |TX     RX      |TX     RX

USART1       |PA9    PA10    |PB6    PB7     |-      -
USART2       |PA2    PA3     |PD5    PD6     |-      -
USART3       |PB10   PB11    |PC10   PC11    |PD8    PD9
@endverbatim
 *
 * In case these pins are not good for you, you can use
 * TM_USART_PinsPack_Custom in function and callback function will be called,
 * where you can initialize your custom pinout for your USART peripheral
 *
 * \par Change USART default operation modes
 * 
 * In this section, you can change USART functionality.
 * Do this only in case you know what are you doing!
 * 
 * Open \ref defines.h file, copy define you want to change and fill settings
@verbatim
//Change X with possible U(S)ARTs: USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8
//Set flow control
#define TM_X_HARDWARE_FLOW_CONTROL		TM_USART_HardwareFlowControl_None
//Set mode
#define TM_X_MODE						USART_Mode_Tx | USART_Mode_Rx
//Set parity
#define TM_X_PARITY						USART_Parity_No
//Set stopbits
#define TM_X_STOP_BITS					USART_StopBits_1
//Set USART datasize
#define TM_X_WORD_LENGTH				USART_WordLength_8b
@endverbatim
 *
 * \par Changelog
 *
@verbatim
 Version 2.5
   - April 15, 2015
   - Added support for custom character for string delimiter
   
 Version 2.4
   - April 09, 2015
   - Added support for new function TM_USART_InitWithFlowControl()
   
 Version 2.3.2
   - March 21, 2015
   - Code optimizations
   
 Version 2.3.2
   - March 17, 2015
   - Added support for Doxygen
   
 Version 2.3
   - March 14, 2015
   - Added support for STM32F446xx devices
   - Changed function name for custom pins initialization callback

 Version 2.2
   - March 10, 2015
   - Updated to be more independent of STD/HAL drivers but still not totally

 Version 2.1
   - March 08, 2015
   - Output pins are more clear initialized. 
   - TM GPIO library is now required to get USART to work properly

 Version 2.0
   - December 21, 2014
   - New cyclic buffer system,
      each U(S)ART can have different buffer size (less RAM can be used for USART purpose)
   - Added function to check if buffer is full,
   - TM_USART_Gets now returns 0 till '\n' is not available in buffer or buffer is full
      Useful for prevent infinite loop if '\n' never happen
	  
 Version 1.0
   - First release
@endverbatim
 *
 * \b Dependencies
 *
@verbatim
 - STM32F10x
 - STM32F10x RCC
 - STM32F10x GPIO
 - STM32F10x USART
@endverbatim
 */
#include "misc.h"
#include "config.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

/* F101/F102/F103/F105/F107 */
#if defined (STM32F10X_HD)
#define USE_USART1
//#define USE_USART2
//#define USE_USART3
#endif

/**
 * @defgroup TM_USART_Typedefs
 * @brief    USART Typedefs
 * @{
 */
 
/**
 * @brief  USART PinsPack enumeration to select pins combination for USART
 */
typedef enum {
	TM_USART_PinsPack_1,     /*!< Select PinsPack1 from Pinout table for specific USART */
	TM_USART_PinsPack_2,     /*!< Select PinsPack2 from Pinout table for specific USART */
	TM_USART_PinsPack_3,     /*!< Select PinsPack3 from Pinout table for specific USART */
} TM_USART_PinsPack_t;

/**
 * @brief  USART Hardware flow control selection
 * @note   Corresponsing pins must be initialized in case you don't use "None" options
 */
typedef enum {
	TM_USART_HardwareFlowControl_None = 0x0000,   /*!< No flow control */
	TM_USART_HardwareFlowControl_RTS = 0x0100,    /*!< RTS flow control */
	TM_USART_HardwareFlowControl_CTS = 0x0200,    /*!< CTS flow control */
	TM_USART_HardwareFlowControl_RTS_CTS = 0x0300 /*!< RTS and CTS flow control */
} TM_USART_HardwareFlowControl_t;

/**
 * @}
 */

/**
 * @defgroup TM_USART_Macros
 * @brief    USART default values for defines
 * @{
 *
 * All values can be overwritten in your project's defines.h file.
 * 
 * Do this only in case you know what are you doing.
 */

/* Default buffer size for each USART */
#ifndef USART_BUFFER_SIZE
#define USART_BUFFER_SIZE 				32
#endif

/* Set default buffer size for specific USART if not set by user */
#ifndef TM_USART1_BUFFER_SIZE
#define TM_USART1_BUFFER_SIZE			USART_BUFFER_SIZE
#endif
#ifndef TM_USART2_BUFFER_SIZE
#define TM_USART2_BUFFER_SIZE			USART_BUFFER_SIZE
#endif
#ifndef TM_USART3_BUFFER_SIZE
#define TM_USART3_BUFFER_SIZE			USART_BUFFER_SIZE
#endif

/* NVIC Global Priority */
#ifndef USART_NVIC_PRIORITY
#define USART_NVIC_PRIORITY				0x06
#endif

/* U(S)ART settings, can be changed in your defines.h project file */
/* USART1 default settings */
#ifndef TM_USART1_HARDWARE_FLOW_CONTROL
#define TM_USART1_HARDWARE_FLOW_CONTROL		TM_USART_HardwareFlowControl_None
#endif
#ifndef TM_USART1_MODE
#define TM_USART1_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef TM_USART1_PARITY
#define TM_USART1_PARITY					USART_Parity_No
#endif
#ifndef TM_USART1_STOP_BITS
#define TM_USART1_STOP_BITS					USART_StopBits_1
#endif
#ifndef TM_USART1_WORD_LENGTH
#define TM_USART1_WORD_LENGTH				USART_WordLength_8b
#endif

/* USART2 default settings */
#ifndef TM_USART2_HARDWARE_FLOW_CONTROL
#define TM_USART2_HARDWARE_FLOW_CONTROL		TM_USART_HardwareFlowControl_None
#endif
#ifndef TM_USART2_MODE
#define TM_USART2_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef TM_USART2_PARITY
#define TM_USART2_PARITY					USART_Parity_No
#endif
#ifndef TM_USART2_STOP_BITS
#define TM_USART2_STOP_BITS					USART_StopBits_1
#endif
#ifndef TM_USART2_WORD_LENGTH
#define TM_USART2_WORD_LENGTH				USART_WordLength_8b
#endif

/* USART3 default settings */
#ifndef TM_USART3_HARDWARE_FLOW_CONTROL
#define TM_USART3_HARDWARE_FLOW_CONTROL		TM_USART_HardwareFlowControl_None
#endif
#ifndef TM_USART3_MODE
#define TM_USART3_MODE						USART_Mode_Tx | USART_Mode_Rx
#endif
#ifndef TM_USART3_PARITY
#define TM_USART3_PARITY					USART_Parity_No
#endif
#ifndef TM_USART3_STOP_BITS
#define TM_USART3_STOP_BITS					USART_StopBits_1
#endif
#ifndef TM_USART3_WORD_LENGTH
#define TM_USART3_WORD_LENGTH				USART_WordLength_8b
#endif

/**
 * @brief  Wait till USART finishes transmission
 */
#define USART_TXEMPTY(USARTx)               ((USARTx)->SR & USART_FLAG_TXE)
#define USART_WAIT(USARTx)                  do { while (!USART_TXEMPTY(USARTx)); } while (0)

/**
 * @brief  Default string delimiter for USART
 */
#define USART_STRING_DELIMITER              '\n'

 /**
 * @}
 */

/**
 * @defgroup TM_USART_Functions
 * @brief    USART Functions
 * @{
 */

/**
 * @brief  Initializes USARTx peripheral and corresponding pins
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  pinspack: This parameter can be a value of @ref TM_USART_PinsPack_t enumeration
 * @param  baudrate: Baudrate number for USART communication
 * @retval None
 */
void TM_USART_Init(USART_TypeDef* USARTx, TM_USART_PinsPack_t pinspack, uint32_t baudrate);

/**
 * @brief  Initializes USARTx peripheral and corresponding pins with custom hardware flow control mode
 * @note   Hardware flow control pins are not initialized. Easy solution is to use @arg TM_USART_PinsPack_Custom pinspack option 
 *         when you call @ref TM_USART_Init() function and initialize all USART pins at a time inside @ref TM_USART_InitCustomPinsCallback() 
 *         callback function, which will be called from my library
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  pinspack: This parameter can be a value of @ref TM_USART_PinsPack_t enumeration
 * @param  baudrate: Baudrate number for USART communication
 * @param  FlowControl: Flow control mode you will use. This parameter can be a value of @ref TM_USART_HardwareFlowControl_t enumeration
 * @retval None
 */
void TM_USART_InitWithFlowControl(USART_TypeDef* USARTx, TM_USART_PinsPack_t pinspack, uint32_t baudrate, TM_USART_HardwareFlowControl_t FlowControl);

/**
 * @brief  Puts character to USART port
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  c: character to be send over USART
 * @retval None
 */
static __INLINE void TM_USART_Putc(USART_TypeDef* USARTx, volatile char c) {
	/* Check USART if enabled */
	if ((USARTx->CR1 & USART_CR1_UE)) {	
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
		/* Send data */
		USARTx->DR = (uint16_t)(c & 0x01FF);
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
	}
}

/**
 * @brief  Puts string to USART port
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  *str: Pointer to string to send over USART
 * @retval None
 */
void TM_USART_Puts(USART_TypeDef* USARTx, char* str);

/**
 * @brief  Sends data array to USART port
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  *DataArray: Pointer to data array to be sent over USART
 * @param  count: Number of elements in data array to be send over USART
 * @retval None
 */
void TM_USART_Send(USART_TypeDef* USARTx, uint8_t* DataArray, uint16_t count);

/**
 * @brief  Gets character from internal USART buffer
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @retval Character from buffer, or 0 if nothing in buffer
 */
uint8_t TM_USART_Getc(USART_TypeDef* USARTx);

/**
 * @brief  Gets string from USART
 *
 *         This function can create a string from USART received data.
 *
 *         It generates string until "\n" is not recognized or buffer length is full.
 * 
 * @note   As of version 1.5, this function automatically adds 0x0A (Line feed) at the end of string.
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  *buffer: Pointer to buffer where data will be stored from buffer
 * @param  bufsize: maximal number of characters we can add to your buffer, including leading zero
 * @retval Number of characters in buffer
 */
uint16_t TM_USART_Gets(USART_TypeDef* USARTx, char* buffer, uint16_t bufsize);

/**
 * @brief  Checks if character c is available in internal buffer
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  c: character to check if it is in USARTx's buffer
 * @retval Character status:
 *            - 0: Character was not found
 *            - > 0: Character has been found in buffer
 */
uint8_t TM_USART_FindCharacter(USART_TypeDef* USARTx, uint8_t c);

/**
 * @brief  Checks if internal USARTx buffer is empty
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @retval Buffer empty status:
 *            - 0: Buffer is not empty
 *            - > 0: Buffer is empty
 */
uint8_t TM_USART_BufferEmpty(USART_TypeDef* USARTx);

/**
 * @brief  Checks if internal USARTx buffer is full
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @retval Buffer full status:
 *            - 0: Buffer is not full
 *            - > 0: Buffer is full
 */
uint8_t TM_USART_BufferFull(USART_TypeDef* USARTx);

/**
 * @brief  Clears internal USART buffer
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @retval None
 */
void TM_USART_ClearBuffer(USART_TypeDef* USARTx);

/**
 * @brief  Sets custom character for @ref TM_USART_Gets() function to detect when string ends
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  Character: Character value to be used as string end
 * @note   Character will also be added at the end for your buffer when calling @ref TM_USART_Gets() function
 * @retval None
 */
void TM_USART_SetCustomStringEndCharacter(USART_TypeDef* USARTx, uint8_t Character);

/**
 * @brief  Callback for custom pins initialization for USARTx.
 *
 *         When you call @ef TM_USART_Init() function, and if you pass @arg TM_USART_PinsPack_Custom to function,
 *         then this function will be called where you can initialize custom pins for USART peripheral.
 * @param  *USARTx: Pointer to USARTx peripheral you will use for initialization
 * @param  AlternateFunction: Alternate function which should be used for GPIO initialization
 * @retval None
 * @note   With __weak parameter to prevent link errors if not defined by user
 */
void TM_USART_InitCustomPinsCallback(USART_TypeDef* USARTx, uint16_t AlternateFunction);

/**
 * @brief  Callback function for receive interrupt on USART1 in case you have enabled custom USART handler mode 
 * @note   With __weak parameter to prevent link errors if not defined by user
 * @param  c: character received via USART
 * @retval None
 */
__attribute__((weak)) void TM_USART1_ReceiveHandler(uint8_t c);

/**
 * @brief  Callback function for receive interrupt on USART2 in case you have enabled custom USART handler mode 
 * @note   With __weak parameter to prevent link errors if not defined by user
 * @param  c: character received via USART
 * @retval None
 */
__attribute__((weak)) void TM_USART2_ReceiveHandler(uint8_t c);

/**
 * @brief  Callback function for receive interrupt on USART3 in case you have enabled custom USART handler mode 
 * @note   With __weak parameter to prevent link errors if not defined by user
 * @param  c: character received via USART
 * @retval None
 */
__attribute__((weak)) void TM_USART3_ReceiveHandler(uint8_t c);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
