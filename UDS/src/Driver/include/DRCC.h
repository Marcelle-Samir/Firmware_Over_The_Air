/**
 * @file DRCC.h
 * @author Mostafa (mnader96@gmail.com)
 * @brief This file is a user interface for RCC Driver for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef DRCC_H_
#define DRCC_H_

/**
 * @def     HSI_ENABLE
 * @brief   Used to Enable HSI
 */
#define HSI_ENABLE 0x10000001
/**
 * @def     HSE_ENABLE
 * @brief   Used to Enable HSE
 */
#define HSE_ENABLE 0x10010000
/**
 * @def     PLL_ENABLE
 * @brief   Used to Enable PLL
 */
#define PLL_ENABLE 0x11000000

/**
 * @brief   Function to set the Clock State
 * @param   clk      Variable of uint_32t describe Clock Type
 * @param   status   Variable of uint_8t describe Clock Status (ON,OFF)
 * @return  uint_8t :   OK  | NOK
 */

uint_8t DRCC_SetClkStatus (uint_32t clk,uint_8t status);

/**
 * @def     HSI_SYS
 * @brief   used to make HSI Clock the System Clock 
 */

#define HSI_SYS    0x20000000
/**
 * @def     HSE_SYS
 * @brief   used to make HSE Clock the System Clock 
 */
#define HSE_SYS    0x20000001
/**
 * @def     PLL_SYS
 * @brief   used to make PLL Clock the System Clock 
 */
#define PLL_SYS    0x20000002

/**
 * @brief   Function to set the System Clock 
 * @param   clk      Variable of uint_32t describe Clock Type to be System Clock(HSI_SYS,HSE_SYS,PLL_SYS)
 * @return  uint_8t :   OK  | NOK
 */

uint_8t DRCC_SetSystemClk (uint_32t clk);

/**
 * @def      HSE_SRC 
 * @brief    HSE Clock without Division 
 */
#define HSE_SRC				0x40010000
/**
 * @def      HSE_SRC_DIV_TWO	 
 * @brief    HSE Clock divide by Two 
 */
#define HSE_SRC_DIV_TWO		0x40030000
/**
 * @def      HSI_SRC_DIV_TWO	 
 * @brief    HSI Clock divide by Two 
 */
#define HSI_SRC_DIV_TWO		0x40000000

/**
 * @def  	PLL_input_clock_x_NUM  
 * @brief	Prescaler of PLL 
 *          NUM Range: 2 up to 16 
 * 					
 */
#define PLL_input_clock_x_2    0
#define PLL_input_clock_x_3    1
#define PLL_input_clock_x_4    2
#define PLL_input_clock_x_5    3
#define PLL_input_clock_x_6    4
#define PLL_input_clock_x_7    5
#define PLL_input_clock_x_8    6
#define PLL_input_clock_x_9    7
#define PLL_input_clock_x_10   8
#define PLL_input_clock_x_11   9
#define PLL_input_clock_x_12   10
#define PLL_input_clock_x_13   11
#define PLL_input_clock_x_14   12
#define PLL_input_clock_x_15   13
#define PLL_input_clock_x_16   14

/**
 * @brief   Function to Configure Clock Source of PLL and it's Multiplication Factor
 * @param   src  Variable of uint_32t describe Clock Source to PLL (HSE_SRC,HSE_SRC_DIV_TWO,HSI_SRC_DIV_TWO)
 * @param   MULL  Variable of uint_8t describe Miltiplication Factor (PLL_input_clock_x_2 up to PLL_input_clock_x_16)
 * @return  uint_8t :   OK  | NOK
 */

uint_8t DRCC_SetPLLConfig (uint_32t src, uint_8t MULL);



/**
 * @def    PERIPHERAL_ENABLE  
 * @brief  Macros used to enable Peripherals Clock   
 * 
 */
#define GPIO_A_ENABLE 	0x20000004
#define GPIO_B_ENABLE 	0x20000008
#define GPIO_C_ENABLE 	0x20000010
#define GPIO_D_ENABLE 	0x20000020
#define GPIO_E_ENABLE 	0x20000040
#define GPIO_F_ENABLE 	0x20000080
#define GPIO_G_ENABLE 	0x20000100
#define USART_1_ENABLE	0x20004000
#define DMA_1_ENABLE	0x80000001

/**
 * @brief   Function to Enable/Disable Clock to peripheral
 * @param   priephral Variable of uint_32t describe Peripheral ex (GPIO_A_ENABLE,DMA_1_ENABLE)
 * @param   Status  Variable of uint_8t describe Clock Status of Peripheral (ON,OFF)
 * @return  uint_8t :   OK  | NOK
 */
uint_8t DRCC_SetPriephralStatus (uint_32t priephral,uint_8t Status);


/**
 * @def      AHB_PRESCALER
 * @brief    used to select AHB Bus 
 */
#define AHB_PRESCALER  0x08000000
/**
 * @def      APB1_PRESCALER
 * @brief    used to select APB1 Bus 
 */
#define APB1_PRESCALER 0x08000001
/**
 * @def      APB2_PRESCALER
 * @brief    used to select APB2 Bus 
 */
#define APB2_PRESCALER 0x08000002

/**
 * @def      APB2_PRESCALER_x
 * @brief    APB2 Prescaler 
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16   
 */

#define APB2_PRESCALER_NOT_DIVIDED 0
#define APB2_PRESCALER_DIV_2       4
#define APB2_PRESCALER_DIV_4       5
#define APB2_PRESCALER_DIV_8       6
#define APB2_PRESCALER_DIV_16      7

/**
 * @def      APB1_PRESCALER_x
 * @brief    APB1 Prescaler 
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16   
 */
#define APB1_PRESCALER_NOT_DIVIDED 0
#define APB1_PRESCALER_DIV_2       4
#define APB1_PRESCALER_DIV_4       5
#define APB1_PRESCALER_DIV_8       6
#define APB1_PRESCALER_DIV_16      7

/**
 * @def      AHB_PRESCALER_x
 * @brief    AHB Prescaler 
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16 or 64 or 128 or 256 or 512  
 */
#define AHB_PRESCALER_NOT_DIVIDED 0
#define AHB_PRESCALER_DIV_2       8
#define AHB_PRESCALER_DIV_4       9
#define AHB_PRESCALER_DIV_8   	 10
#define AHB_PRESCALER_DIV_16     11
#define AHB_PRESCALER_DIV_64     12
#define AHB_PRESCALER_DIV_128    13
#define AHB_PRESCALER_DIV_256    14
#define AHB_PRESCALER_DIV_512    15

/**
 * @brief   Function to set Bus Prescaler
 * @param   Bus       Variable of uint_32t describe Bus Number (AHB_PRESCALER, APB1_PRESCALER, APB2_PRESCALER)
 * @param   Prescale  Variable of uint_8t describe  Bus Prescaler ex  (APB2_PRESCALER_NOT_DIVIDED,APB1_PRESCALER_DIV_8,AHB_PRESCALER_DIV_256)
 * @return  uint_8t :   OK  | NOK
 */

uint_8t DRCC_SetBusPrescale (uint_32t Bus,uint_8t Prescale);

/**
 * @def      HSI_FREQ
 * @brief    describe HSI Frequency     
 */
#define HSI_FREQ	8000000
/**
 * @def      HSE_FREQ
 * @brief    describe HSE Frequency     
 */
#define HSE_FREQ	8000000

/**
 * @def      AHB_BUS
 * @brief    used to check AHB Bus 
 */
#define AHB_BUS  77
/**
 * @def      APB1_BUS
 * @brief    used to check APB1 Bus 
 */
#define APB1_BUS 78
/**
 * @def      APB2_BUS
 * @brief    used to check APB2 Bus 
 */
#define APB2_BUS 79


/**
 * @brief   Function to get bus Clock
 * @param   Bus   Variable of uint_32t describe Bus Number (AHB_PRESCALER, APB1_PRESCALER, APB2_PRESCALER)
 * @param   CLK   pointer to uint_32t Clock which to be read  
 * @return  uint_8t :   OK  | NOK
 */
uint_8t DRCC_GetBusClock (uint_32t Bus,uint_32t *CLK);


#endif 