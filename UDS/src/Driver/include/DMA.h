
/**
 * @file	DMA.h
 * @author 	Marcelle (marcelle.samir.s@gmail.com)
 * @brief 	This file is a user interface for DMA Driver for STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DMA_H_
#define DMA_H_

/**
 * @brief	Function to initialize DMA
 * @param	NA
 * @return 	uint_8t : OK | NOK
 */
uint_8t D_DMA_Init(void);

/**
 * @def  	CHANNEL_NUMBER 
 * @brief 	Channel of DMA 
 * 			Number : ONE up to SEVEN  
 */
#define CHANNEL_ONE		0
#define CHANNEL_TWO		1
#define CHANNEL_THREE	2
#define CHANNEL_FOUR	3
#define CHANNEL_FIVE	4
#define CHANNEL_SIX		5
#define CHANNEL_SEVEN	6

/**
 * @brief	Function to Make DMA Start Transfering Data according to it's Parameters
 * @param	MemoryAddress		Variable of uint_32t , Takes Memory Address 
 * @param 	PeripheralAddress	Variable of uint_32t , Takes Peripheral Address
 * @param 	Counter				Variable of uint_8t  , Takes Counter of Data Transmission 
 * @param 	ChannelNumber 		Variable of uint_8t  , DMA Channel Number ( CHANNEL_ONE   , CHANNEL_SEVEN)
 * @return 	uint_8t : OK | NOK
 */
uint_8t D_DMA_Start(uint_32t MemoryAddress,uint_32t PeripheralAddress,uint_32t Counter,uint_8t ChannelNumber);

/**
 * @typedef 	TC_Notification
 * @brief 		Pointer to Function 	
 */ 
typedef void (*TC_Notification)(void);
/**
 * @typedef 	HTC_Notification
 * @brief 		Pointer to Function 	
 */ 
typedef void (*HTC_Notification)(void);
/**
 * @typedef 	TE_Notification
 * @brief 		Pointer to Function 	
 */ 
typedef void (*TE_Notification)(void);

/**
 * @typedef 	Notify_t
 * @brief		Struct of pointers to function 
 *   
 */ 
typedef struct
{
	TC_Notification		TC;
	HTC_Notification	HTC;
	TE_Notification		TE;
}Notify_t;

/**
 * @brief	Function to Set DMA Call Back Function
 * @param	Notification		Pointer to struct  , Takes Function to Execute 
 * @param 	ChannelNumber 		Variable of uint_8t  , DMA Channel Number ( CHANNEL_ONE   , CHANNEL_SEVEN)
 * @return 	uint_8t : OK | NOK
 */
uint_8t D_DMA_SetNotifyCbf(Notify_t *Notification, uint_8t Channel_Number);





#endif /* DMA_H_ */
