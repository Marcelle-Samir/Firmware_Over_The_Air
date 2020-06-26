/**
 * @file	HUART_config.h
 * @author 	Mohanad (mohanad_sallam@hotmail.com)
 * @brief 	This file is the Configuration for UART Handler for UART Driver in STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef HUART_CONFIG_H_
#define HUART_CONFIG_H_


/**
 * @def     SEND_MODE_INTERRUPT
 * @brief   Interrupt Mode for Sending 
 */
#define SEND_MODE_INTERRUPT			0
/**
 * @def     SEND_MODE_DMA
 * @brief   DMA Mode for Sending  
 */
#define SEND_MODE_DMA				1
/**
 * @def     RECEIVE_MODE_INTERRUPT
 * @brief   Interrupt Mode for Receiving 
 */
#define RECEIVE_MODE_INTERRUPT		0
/**
 * @def     RECEIVE_MODE_DMA
 * @brief   DMA Mode for Receiving   
 */
#define RECEIVE_MODE_DMA			1
/**
 * @def     LIN_ON
 * @brief   Enable LIN
 */
#define LIN_ON                      0
/**
 * @def     LIN_OFF
 * @brief   Disable LIN
 */
#define LIN_OFF                     1

/**
 * @def     INTERRUPT_MODE
 * @brief   used to Enable Interrupt Mode 
 */  
#define INTERRUPT_MODE				0
/**
 * @def     DMA_MODE
 * @brief   used to Enable DMA Mode 
 */  
#define DMA_MODE					1
/**
 * @def     PARITY_DISABLED
 * @brief   used to Disable Parity 
 */
#define PARITY_DISABLED		0x00000000
/**
 * @def     PARITY_EVEN
 * @brief   used to Enable Even Parity 
 */
#define PARITY_EVEN			0x00000400
/**
 * @def     PARITY_ODD
 * @brief   used to Enable ODD Parity 
 */
#define PARITY_ODD			0x00000600
/**
 * @def     ONE_STOP_BIT
 * @brief   used to Enable One Stop Bit
 */
#define ONE_STOP_BIT		0x00000000
/**
 * @def     TWO_STOP_BIT
 * @brief   used to Enable Two Stop Bit
 */
#define TWO_STOP_BIT		0x00002000
/**
 * @def     DATA_8_BITS
 * @brief   used to Enable 8 Data bits 
 */
#define DATA_8_BITS			0x00000000
/**
 * @def     DATA_8_BITS
 * @brief   used to Enable 9 Data bits 
 */
#define DATA_9_BITS			0x00001000
/**
 * @def     PARITY_BIT
 * @brief   used to Configure Parity Bit (PARITY_DISABLED OR PARITY_EVEN OR PARITY_ODD) 
 */
#define PARITY_BIT			PARITY_DISABLED
/**
 * @def     STOP_BITS
 * @brief   used to Configure Stop Bits (ONE_STOP_BIT OR TWO_STOP_BIT) 
 */
#define STOP_BITS			ONE_STOP_BIT
/**
 * @def     DATA_BITS
 * @brief   used to Configure Data Bits (DATA_8_BITS OR DATA_9_BITS) 
 */
#define DATA_BITS			DATA_8_BITS
/**
 * @def     BAUD_RATE_9600
 * @brief   Baud Rate is 9600 
 */
#define BAUD_RATE_9600		9600
/**
 * @def     BAUD_RATE_115200
 * @brief   Baud Rate is 115200 
 */
#define BAUD_RATE_115200	115200
/**
 * @def     SEND_MODE
 * @brief   used to Configure Mode (SEND_MODE_INTERRUPT OR SEND_MODE_DMA) 
 */
#define SEND_MODE				SEND_MODE_DMA
/**
 * @def     RECEIVE_MODE
 * @brief   used to Configure Mode (RECEIVE_MODE_DMA OR RECEIVE_MODE_INTERRUPT) 
 */ 
#define RECEIVE_MODE			RECEIVE_MODE_DMA
/**
 * @def     MODE
 * @brief   used to Configure Mode (DMA_MODE OR INTERRUPT_MODE) 
 */ 
#define MODE					DMA_MODE
/**
 * @def     LIN_MODE 
 * @brief   used to Enable LIN
 */ 
#define LIN_MODE                LIN_ON

/**
 * @def     BAUD_RATE
 * @brief   used to Configure Baud Rate (BAUD_RATE_115200 OR BAUD_RATE_9600) 
 */
#define BAUD_RATE			BAUD_RATE_115200



#endif /* HUART_CONFIG_H_ */
