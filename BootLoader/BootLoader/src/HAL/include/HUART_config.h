/*
 * HUART_config.h
 *
 *  Created on: Mar 28, 2020
 *      Author: Mohanad
 */

#ifndef HUART_CONFIG_H_
#define HUART_CONFIG_H_

#define SEND_MODE_INTERRUPT			0
#define SEND_MODE_DMA				1

#define RECEIVE_MODE_INTERRUPT		0
#define RECEIVE_MODE_DMA			1

#define LIN_ON                      0
#define LIN_OFF                     1

#define INTERRUPT_MODE				0
#define DMA_MODE					1

#define PARITY_DISABLED		0x00000000
#define PARITY_EVEN			0x00000400
#define PARITY_ODD			0x00000600

#define ONE_STOP_BIT		0x00000000
#define TWO_STOP_BIT		0x00002000

#define DATA_8_BITS			0x00000000
#define DATA_9_BITS			0x00001000

#define PARITY_BIT			PARITY_DISABLED
#define STOP_BITS			ONE_STOP_BIT
#define DATA_BITS			DATA_8_BITS

#define BAUD_RATE_9600		9600

#define SEND_MODE				SEND_MODE_DMA
#define RECEIVE_MODE			RECEIVE_MODE_DMA
#define MODE					DMA_MODE
#define LIN_MODE                LIN_ON

#define BAUD_RATE			BAUD_RATE_9600






#endif /* HUART_CONFIG_H_ */
