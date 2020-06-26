/**
 * @file	HUART.h
 * @author 	Mohanad (mohanad_sallam@hotmail.com)
 * @brief 	This file is the User Interface for UART Handler for UART Driver in STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 */


#ifndef HUART_H_
#define HUART_H_

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
 * @brief	Pointer to function of LIN Break Call Back Function
 */
typedef void(*LBDCbf_t)(void);

/**
 * @brief   Function initilaize HUART 
 * @param   NA
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_Init(void);

/**
 * @brief   Function sends bytes using UART 
 * @param   Buffer  Pointer to uint_8t, pointer that contain the bytes to be sent
 * @param   Length  Variable of uint_16t, variable that contains the number of Bytes to be sent 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_Send(uint_8t *Buffer, uint_16t Length);

/**
 * @brief   Function receives bytes using UART 
 * @param   Buffer  Pointer to uint_8t, pointer that receive bytes  
 * @param   Length  Variable of uint_16t, variable that contains the Received bytes 
 * @return  uint_8t : OK | NOK
 */  
uint_8t HUART_Receive(uint_8t *Buffer, uint_16t Length);

/**
 * @brief   Function configure HUART 
 * @param   BaudRate   Variable of uint_32t, variable that contains Baud Rate  
 * @param   ParityBits Variable of uint_32t, variable that contains ParityState ex (PARITY_DISABLED, PARITY_EVEN)
 * @param   DataSize   Variable of uint_32t, variable that contains DataSize (DATA_8_BITS OR DATA_9_BITS) 
 * @param   StopBits   Variable of uint_32t, variable that contains number of StopBits (ONE_STOP_BIT OR TWO_STOP_BIT)
 * @return  uint_8t : OK | NOK
 */
uint_8t HUART_Config(uint_32t BaudRate,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);

/**
 * @brief   Function sets the send call back function 
 * @param   TxCbf Pointer to function , Take address of call back fuction 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_SetTxCbf(TxCbf_t TxCbf);

/**
 * @brief   Function sets the Received call back function 
 * @param   RxCbf Pointer to function , Take address of call back fuction 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_SetRxCbf(RxCbf_t RxCbf);
/**
 * @brief   Function sets the LIN Break call back function 
 * @param   LBDCbf Pointer to function , Take address of call back fuction 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_SetLBDCbf(LBDCbf_t LBDCbf);
/**
 * @brief   Function of Send LIN Break   
 * @param   NA 
 * @return  uint_8t : OK | NOK
 */ 
uint_8t HUART_SendBreak(void);




#endif /* HUART_H_ */
