/**
 * @file	UART_Private.h
 * @author 	Mostafa Nader (mnader96@gmail.com)
 * @brief 	This file is Private from user for UART Driver in STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_
/**
 * @def 	USART_TC_FLAG
 * @brief 	Transfer Complete Flag 
 */
#define USART_TC_FLAG					0x00000040
/**
 * @typedef UART_t
 * @brief 	Stucrt of Uart Registers 
 */
typedef struct
{
	uint_32t	SR;
	uint_32t	DR;
	uint_32t	BRR;
	uint_32t	CR1;
	uint_32t	CR2;
	uint_32t	CR3;
	uint_32t	GTPR;
}UART_t;
/**
 * @def		UART
 * @brief 	Base Address of Uart Driver 
 */
#define UART ((UART_t*)0x40013800)



#endif /* UART_PRIVATE_H_ */
