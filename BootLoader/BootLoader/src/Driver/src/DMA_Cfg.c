/**
 * @file	DMA.h
 * @author 	Marcelle (marcelle.samir.s@gmail.com)
 * @brief 	This file is Implemtation of DMA Configuration for DMA Driver for STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 * 
 */

/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"
/**
 * @headerfile DMA.h
 */
#include "DMA.h"
/**
 * @headerfile DMA_Cfg.h
 */
#include "DMA_Cfg.h"



const DMA_Config DMA_Configure[MAX_NUMBER_OF_CHANNELS]={

		{
				.Mem2Mem= MEMORY2PERIPHERAL,
				.PL     = PRIORITY_LOW,
				.MSIZE  = MEMORY_SIZE_1_BYTE,
				.PSIZE  = PERIPHERAL_SIZE_1_BYTE,
				.MINC   = MEMORY_INCREMENT_ON,
				.PINC   = PERIPHERAL_INCREMENT_OFF,
				.CIRC   = CIRCULER_INT_OFF,
				.DIR    = DIR_MEMORY_TO_PERI,
				.TEIE   = TRANSFER_ERROR_INT_OFF,
				.HTIE   = HALF_TRANSFER_INT_OFF,
				.TCIE   = TRANSFER_COMP_INT_ON,
				.ChannelNumber = CHANNEL_FOUR
		},
		{
				.Mem2Mem= MEMORY2PERIPHERAL,
				.PL     = PRIORITY_MEDIUM,
				.MSIZE  = MEMORY_SIZE_1_BYTE,
				.PSIZE  = PERIPHERAL_SIZE_1_BYTE,
				.MINC   = MEMORY_INCREMENT_ON,
				.PINC   = PERIPHERAL_INCREMENT_OFF,
				.CIRC   = CIRCULER_INT_OFF,
				.DIR    = DIR_PERI_TO_MEMORY,
				.TEIE   = TRANSFER_ERROR_INT_OFF,
				.HTIE   = HALF_TRANSFER_INT_OFF,
				.TCIE   = TRANSFER_COMP_INT_ON,
				.ChannelNumber = CHANNEL_FIVE
		},
		{
				.Mem2Mem= MEMORY2MEMORY,
				.PL     = PRIORITY_LOW,
				.MSIZE  = MEMORY_SIZE_1_BYTE,
				.PSIZE  = PERIPHERAL_SIZE_1_BYTE,
				.MINC   = MEMORY_INCREMENT_ON,
				.PINC   = PERIPHERAL_INCREMENT_ON,
				.CIRC   = CIRCULER_INT_OFF,
				.DIR    = DIR_PERI_TO_MEMORY,
				.TEIE   = TRANSFER_ERROR_INT_OFF,
				.HTIE   = HALF_TRANSFER_INT_OFF,
				.TCIE   = TRANSFER_COMP_INT_ON,
				.ChannelNumber = CHANNEL_ONE
		}

};
