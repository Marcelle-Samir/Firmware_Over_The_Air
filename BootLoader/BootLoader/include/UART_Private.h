/*
 * UART_Private.h
 *
 *  Created on: Apr 16, 2020
 *      Author: MOSTAFA
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define USART_TC_FLAG					0x00000040

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

#define UART ((UART_t*)0x40013800)



#endif /* UART_PRIVATE_H_ */
