/*
 * config.h
 *
 *  Created on: 23 okt. 2017
 *      Author: peter_000
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "usart.h"

/* Check for GNUC */
#if defined (__GNUC__)
	#ifndef __weak
		#define __weak   	__attribute__((weak))
	#endif	/* Weak attribute */
	#ifndef __packed
		#define __packed 	__attribute__((__packed__))
	#endif	/* Packed attribute */
#endif

/* USART Config */
#define TM_USART1_HARDWARE_FLOW_CONTROL		TM_USART_HardwareFlowControl_None
#define TM_USART1_MODE						USART_Mode_Tx | USART_Mode_Rx
#define TM_USART1_PARITY					USART_Parity_No
#define TM_USART1_STOP_BITS					USART_StopBits_1
#define TM_USART1_WORD_LENGTH				USART_WordLength_8b
#define TM_USART1_BUFFER_SIZE				4096

#ifndef DEBUG
#define DEBUG_TEST 0
#else
#define DEBUG_TEST 1
#endif

#define debug_print(fmt, ...) \
            do { if (DEBUG_TEST) printf(fmt, ##__VA_ARGS__); } while (0)

#endif /* CONFIG_H_ */
