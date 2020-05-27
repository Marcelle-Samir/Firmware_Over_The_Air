/*
 * DMA.h
 *
 *  Created on: Apr 15, 2020
 *      Author: MOSTAFA
 */

#ifndef DMA_H_
#define DMA_H_


typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK	0
#define NOK	1



/************************************************************************
 * Function name: D_DMA_Init
 *
 * parameters:  Input:  NA
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to initialize DMA
 ***************************************************************************/

uint_8t D_DMA_Init(void);

/********************************************************************************************************************/

/*************************************
 *********DMA_CHANNEL_NUMBER**********
 *************************************/
#define CHANNEL_ONE		0
#define CHANNEL_TWO		1
#define CHANNEL_THREE	2
#define CHANNEL_FOUR	3
#define CHANNEL_FIVE	4
#define CHANNEL_SIX		5
#define CHANNEL_SEVEN	6

/************************************************************************
 * Function name: DRCC_SetBusPrescale
 *
 * parameters:  Input:
 *                 MemoryAddress
 *                     type: uint_32t
 *                     Description: Takes Memory Address
 *                 PeripheralAddress
 *                     type: uint_32t
 *                     Description: Takes Peripheral Address
 *                 Counter
 *                     type: uint_8t
 *                     Description: Takes Counter of Data Transmission
 *                 ChannelNumber
 *                     type: uint_8t
 *                     Description: DMA Channel Number ( CHANNEL_ONE   , CHANNEL_TWO
 *                                                       CHANNEL_THREE , CHANNEL_FOUR
 *                                                       CHANNEL_FIVE  , CHANNEL_SIX
 *                                                       CHANNEL_SEVEN             )
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to Make DMA Start Transfering Data according to it's Parameters
 ***************************************************************************/

uint_8t D_DMA_Start(uint_32t MemoryAddress,uint_32t PeripheralAddress,uint_32t Counter,uint_8t ChannelNumber);

/********************************************************************************************************************/

/*************************************
 *********DMA_CHANNEL_NUMBER**********
 *************************************/
#define CHANNEL_ONE		0
#define CHANNEL_TWO		1
#define CHANNEL_THREE	2
#define CHANNEL_FOUR	3
#define CHANNEL_FIVE	4
#define CHANNEL_SIX		5
#define CHANNEL_SEVEN	6

/*************************************
 *********DMA_POINTER_TO_FUNCTION*****
 *************************************/
typedef void (*TC_Notification)(void);
typedef void (*HTC_Notification)(void);
typedef void (*TE_Notification)(void);

/***************FLAGS_OF_DMA***********************/
typedef struct
{
	TC_Notification		TC;
	HTC_Notification	HTC;
	TE_Notification		TE;
}Notify_t;

/************************************************************************
 * Function name: DRCC_SetBusPrescale
 *
 * parameters:  Input:
 *                 MemoryAddress
 *                     type       : Notify_t ( Pointer To function )
 *                     Description: Takes Function to Execute
 *                 ChannelNumber
 *                     type: uint_8t
 *                     Description: DMA Channel Number ( CHANNEL_ONE   , CHANNEL_TWO
 *                                                       CHANNEL_THREE , CHANNEL_FOUR
 *                                                       CHANNEL_FIVE  , CHANNEL_SIX
 *                                                       CHANNEL_SEVEN             )
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to Set DMA Call Back Function
 ***************************************************************************/

uint_8t D_DMA_SetNotifyCbf(Notify_t *Notification, uint_8t Channel_Number);



#endif /* DMA_H_ */
