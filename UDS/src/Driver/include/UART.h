/**
 * @file UART.h
 * @author Mostafa Nader (mnader96@gmail.com)
 * @brief  This file is User Interface for UART Driver in STM32F103
 * @version 0.1
 * @date 2020-06-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef UART_H_
#define UART_H_

/**
 * @def     USART_TCEIE_ENABLE
 * @brief   Uart Transmit Complete Interupt Enable 
 */ 
#define USART_TCEIE_ENABLE				0x00000040
/**
 * @def     USART_TXEIE_ENABLE
 * @brief   Uart Transmit Interupt Enable 
 */ 
#define USART_TXEIE_ENABLE				0x00000080
/**
 * @def     USART_RXNEIE_ENABLE
 * @brief   Uart Receive Interupt Enable 
 */
#define USART_RXNEIE_ENABLE				0x00000020
/**
 * @typedef TxCbf_t
 * @brief	Pointer to function of TX Call Back Function
 */
typedef void(*TxCbf_t)(void);
/**
 * @typedef RxCbf_t
 * @brief	Pointer to function of RX Call Back Function
 */
typedef void(*RxCbf_t)(void);
/**
 * @typedef LBDCbf_t
 * @brief	Pointer to function of LBDCbf Call Back Function
 */
typedef void(*LBDCbf_t)(void);
/**
 * @brief   Function initializes UART 
 * @param   BaudRate   Variable of uint_32t, variable that contains Baud Rate  
 * @param   ParityBits Variable of uint_32t, variable that contains ParityState ex (PARITY_DISABLED, PARITY_EVEN)
 * @param   DataSize   Variable of uint_32t, variable that contains DataSize (DATA_8_BITS OR DATA_9_BITS) 
 * @param   StopBits   Variable of uint_32t, variable that contains number of StopBits (ONE_STOP_BIT OR TWO_STOP_BIT)
 * @return  uint_8t : OK | NOT_OK
 */
uint_8t UART_Init(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);

/**
 * @brief   Function sends buffer of data thorught uart using Interrupt or DMA modes 
 * @param   Buffer Pointer of uint_8t, Buffer that contains data to be sent
 * @param   Length Variable of uint_16t, Length of data to be received
 * @return  uint_8t : OK | NOK
 */
uint_8t UART_Send(uint_8t *Buffer, uint_16t Length);

/**
 * @brief   Function receives a buffer of data DMA
 * @param   Buffer Pointer of uint_8t, buffer that store the received data
 * @param   Length Variable of uint_16t, Length of data to be received
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_SendDMA(uint_8t *Buffer, uint_16t Length);
/**
 * @brief   Function receives a buffer of data using interrupt or DMA
 * @param   Buffer Pointer of uint_8t, buffer that store the received data
 * @param   Length Variable of uint_16t, Length of data to be received
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_Receive(uint_8t *Buffer, uint_16t Length);
/**
 * @brief   Function configure the UART   
 * @param   BaudRateMantissa  Variable of uint_32t, Baudrate's mantissa paramter
 * @param   BaudRateFraction  Variable of uint_32t, Baudrate's fraction paramter
 * @param   ParityBits Variable of uint_32t, even parity , odd parity
 * @param   ParityBits Variable of uint_32t, Data length 5->9 bits
 * @param   StopBits Variable of uint_32t, one stop bit , two stop bits 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_Config(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);
/**
 * @brief   Function that sets the call back function of the transmission complete   
 * @param   TxCbf pointer to function, Call Back Function
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_SetTxCbf(TxCbf_t TxCbf);
/**
 * @brief   Function that sets the call back function of the receiving is complete
 * @param   RxCbf  pointer to function, Call Back Function
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_SetRxCbf(RxCbf_t RxCbf);
/**
 * @brief   Function that sets the call back function of the LIN break detection
 * @param   LBDCbf  pointer to function, Call Back Function
 * @return  uint_8t : OK | NOK
 */ 
uint_8t UART_SetLBDCbf(LBDCbf_t LBDCbf);
/**
 * @brief   Function called when UART finishes transmission through DMA 
 * @param   NA
 * @return  NA
 */ 
void DMA_ChannelFour_Finish(void);
/**
 * @brief   Function called when UART finishes receiving through DMA 
 * @param   NA
 * @return  NA
 */ 
void DMA_ChannelFive_Finish(void);

/**
 * @brief   Function that enables the bit that send a LIN break 
 * @param   NA
 * @return  NA
 */ 
void UART_SendBreak(void);

#endif
