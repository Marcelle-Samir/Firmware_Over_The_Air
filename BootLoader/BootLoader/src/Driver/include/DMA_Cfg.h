/**
 * @file	DMA_Cfg.h
 * @author 	Marcelle (marcelle.samir.s@gmail.com)
 * @brief 	This file is DMA Configuration for DMA Driver for STM32F103
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef DMA_CFG_H_
#define DMA_CFG_H_

/**
 * @def 	DMA1_GET_INT_GLx
 * @brief 	Enable all Interrupts of Dma 
 * 			x : 1 up to 7
 */
#define DMA1_GET_INT_GL1         0x00000001
#define DMA1_GET_INT_GL2         0x00000010
#define DMA1_GET_INT_GL3         0x00000100
#define DMA1_GET_INT_GL4         0x00001000
#define DMA1_GET_INT_GL5         0x00010000
#define DMA1_GET_INT_GL6         0x00100000
#define DMA1_GET_INT_GL7         0x01000000

/**
 * @def 	DMA1_GET_INT_TCx
 * @brief 	Enable Transfer complete Interrupt of Dma 
 * 			x : 1 up to 7
 */
#define DMA1_GET_INT_TC1         0x00000002
#define DMA1_GET_INT_TC2         0x00000020
#define DMA1_GET_INT_TC3         0x00000200
#define DMA1_GET_INT_TC4         0x00002000
#define DMA1_GET_INT_TC5         0x00020000
#define DMA1_GET_INT_TC6         0x00200000
#define DMA1_GET_INT_TC7         0x02000000

/**
 * @def 	DMA1_GET_INT_TEx
 * @brief 	Transmission error Interrupt of Dma 
 * 			x : 1 up to 7
 */

#define DMA1_GET_INT_TE1         0x00000008
#define DMA1_GET_INT_TE2         0x00000080
#define DMA1_GET_INT_TE3         0x00000800
#define DMA1_GET_INT_TE4         0x00008000
#define DMA1_GET_INT_TE5         0x00080000
#define DMA1_GET_INT_TE6         0x00800000
#define DMA1_GET_INT_TE7         0x08000000

/**
 * @def 	DMA1_GET_INT_HTx
 * @brief 	Half Transmission Interrupt of Dma 
 * 			x : 1 up to 7
 */
#define DMA1_GET_INT_HT1         0x00000004
#define DMA1_GET_INT_HT2         0x00000040
#define DMA1_GET_INT_HT3         0x00000400
#define DMA1_GET_INT_HT4         0x00004000
#define DMA1_GET_INT_HT5         0x00040000
#define DMA1_GET_INT_HT6         0x00400000
#define DMA1_GET_INT_HT7         0x04000000


/**
 * @def 	MEMORY2MEMORY
 * @brief 	used to enable memory to memory transfer  
 */
#define MEMORY2MEMORY			 0x00004000
/**
 * @def 	MEMORY2PERIPHERAL
 * @brief  	used to enable Memory to Peripheral transfer  	 
 */
#define MEMORY2PERIPHERAL		 0x00000000

/**
 * @def 	PRIORITY_LOW
 * @brief  	Priority level for channels  	 
 */
#define PRIORITY_LOW			 0x00000000
#define PRIORITY_MEDIUM			 0x00001000
#define PRIORITY_HIGH			 0x00002000
#define PRIORITY_VERYHIGH		 0x00003000

/**
 * @def 	MEMORY_SIZE_x_BYTE 	
 * @brief 	Memory size 
 * 			x : 1 | 2 | 4  
 */
#define MEMORY_SIZE_1_BYTE 		 0x00000000
#define MEMORY_SIZE_2_BYTE		 0x00000400
#define MEMORY_SIZE_4_BYTE		 0x00000800

/**
 * @def 	PERIPHERAL_SIZE_x_BYTE  	
 * @brief 	Peripheral size 
 * 			x : 1 | 2 | 4  
 */
#define PERIPHERAL_SIZE_1_BYTE 	 0x00000000
#define PERIPHERAL_SIZE_2_BYTE	 0x00000100
#define PERIPHERAL_SIZE_4_BYTE	 0x00000200

/**
 * @def 	MEMORY_INCREMENT_Status 	
 * @brief 	Memory Increment 
 * 			Status : ON/OFF 
 */
#define MEMORY_INCREMENT_ON		 0x00000080
#define MEMORY_INCREMENT_OFF	 0x00000000

/**
 * @def 	PERIPHERAL_INCREMENT_Status 	
 * @brief 	PERIPHERAL Increment 
 * 			Status : ON/OFF 
 */
#define PERIPHERAL_INCREMENT_ON  0x00000040
#define PERIPHERAL_INCREMENT_OFF 0x00000000

/**
 * @def 	CIRCULER_INT_Status 	
 * @brief 	Begin from same place after finshing  
 * 			Status : ON/OFF 
 */

#define CIRCULER_INT_ON			 0x00000020
#define CIRCULER_INT_OFF		 0x00000000
/**
 * @def 	DIR_PERI_TO_MEMORY	
 * @brief 	Direction Peripheral To Memory   
 */
#define DIR_PERI_TO_MEMORY		 0x00000000
/**
 * @def 	DIR_MEMORY_TO_PERI	
 * @brief 	Direction Memory to Peripheral    
 */
#define DIR_MEMORY_TO_PERI	 	 0x00000010
/**
 * @def 	TRANSFER_ERROR_INT_Status 	
 * @brief 	Interrupt Transfer Error  
 * 			Status : ON/OFF 
 */
#define TRANSFER_ERROR_INT_ON  	 0x00000008
#define TRANSFER_ERROR_INT_OFF	 0x00000000
/**
 * @def 	HALF_TRANSFER_INT_Status 	
 * @brief 	Interrupt Half Transfer   
 * 			Status : ON/OFF 
 */
#define HALF_TRANSFER_INT_ON	 0x00000004
#define HALF_TRANSFER_INT_OFF	 0x00000000
/**
 * @def 	TRANSFER_COMP_INT_Status 	
 * @brief 	Interrupt Transfer Complete  
 * 			Status : ON/OFF 
 */
#define TRANSFER_COMP_INT_ON	 0x00000002
#define TRANSFER_COMP_INT_OFF	 0x00000000

/**
 * @def 	MAX_NUMBER_OF_CHANNELS
 * @brief 	Number of channels tobe used 
 */
#define MAX_NUMBER_OF_CHANNELS	3

/**
 * @typedef DMA_Config
 * @brief 	Configuration Parameters of DMA
 * 
 */
typedef struct
{
	uint_32t Mem2Mem;
	uint_32t PL;
	uint_32t MSIZE;
	uint_32t PSIZE;
	uint_32t MINC;
	uint_32t PINC;
	uint_32t CIRC;
	uint_32t DIR;
	uint_32t TEIE;
	uint_32t HTIE;
	uint_32t TCIE;
	uint_8t	 ChannelNumber;
}DMA_Config;





#endif /* DMA_CFG_H_ */
