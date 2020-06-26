/**
 * @file DNVIC.h
 * @author Ahmed Qandeel (Ahmed.qandeel96@gmail.com)
 * @brief This file is the user interface for NVIC Driver for Cortex M3
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef DNVIC_H_
#define DNVIC_H_

/**
 * @def     Peripheral 
 * @brief   Numbers asssigned to peripherals is the offest of them in vector table array 
 * 
 */
#define WWDG				0
#define PVD					1
#define TAMPER				2
#define RTC					3
#define FLASH				4
#define RCCINT				5
#define EXTI0				6
#define EXTI1				7
#define EXTI2				8
#define EXTI3				9
#define EXTI4				10
#define DMA1_CHANNEL1		11
#define DMA1_CHANNEL2		12
#define DMA1_CHANNEL3		13
#define DMA1_CHANNEL4		14
#define DMA1_CHANNEL5		15
#define DMA1_CHANNEL6		16
#define DMA1_CHANNEL7		17
#define ADC1_2				18
#define USB_HP_CAN_TX		19
#define USB_LP_CAN_RX0		20
#define CAN_RX1				21
#define CAN_SCE				22
#define EXTI9_5				23
#define TIM1_BRK			24
#define TIM1_UP				25
#define TIM1_TRG_COM		26
#define TIM1_CC				27
#define TIM2				28
#define TIM3				29
#define TIM4				30
#define I2C1_EV				31
#define I2C1_ER				32
#define I2C2_EV				33
#define I2C2_ER				34
#define SPI1				35
#define SPI2				36
#define USART1				37
#define USART2				38
#define USART3				39
#define EXTI15_10			40
#define RTCALARM			41
#define USBWAKEUP			42
#define TIM8_BRK			43
#define TIM8_UP				44
#define TIM8_TRG_COM		45
#define TIM8_CC				46
#define ADC3				47
#define FSMC				48
#define SDIO				49
#define TIM5				50
#define SPI3				51
#define UART4				52
#define UART5				53
#define TIM6				54
#define TIM7				55
#define DMA2_CHANNEL1		56
#define DMA2_CHANNEL2		57
#define DMA2_CHANNEL3		58
#define DMA2_CHANNEL4_5		59

/**
 * @brief   Function to Enable peripheral Interrupt 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_EnableIRQ(uint_8t IRQn);

/**
 * @brief   Function to Disable peripheral Interrupt 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_DisableIRQ(uint_8t IRQn);

/**
 * @brief   Function to Set Peripheral Pending Interrupt Flag By Software 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_SetPendingIRQ (uint_8t IRQn);

/**
 * @brief   Function to Reset Peripheral Pending Interrupt Flag By Software 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_ClearPendingIRQ (uint_8t IRQn);

/**
 * @brief   Function to get Pending Flag Value 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   Val  pointer  of uint_8t , Pending Flag which to be read assigned to pointer 
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_GetPendingIRQ (uint_8t IRQn, uint_8t *Val);

/**
 * @brief   Function to get Active Flag Value 
 * @param   IRQn Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   Val  pointer  of uint_8t , Active Flag which to be read assigned to pointer 
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_GetActive (uint_8t IRQn, uint_8t *Val);

/**
 * @def    NUM_PREEMPTION_NUM_SUBGROUP
 * @brief  define Groups and Subgroups ex (ALL_PREEMPTION , ONE_PREEMPTION_THREE_SUBGROUP) 
 */
#define ALL_PREEMPTION						0X00000300
#define THREE_PREEMPTION_ONE_SUBGROUP		0X00000400
#define TWO_PREEMPTION_TWO_SUBGROUP			0X00000500
#define ONE_PREEMPTION_THREE_SUBGROUP		0X00000600
#define ALL_SUBGROUP						0X00000700

/**
 * @brief   Function provides priority grouping control for the exception model
 * @param   priority_grouping Variable of uint_32t , Priority Type (ALL_PREEMPTION , THREE_PREEMPTION_ONE_SUBGROUP)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_SetPriorityGrouping(uint_32t priority_grouping);

/**
 * @brief   Function to Set Interrupt Priority 
 * @param   IRQn        Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   priority    Variable of uint_8t , Priority (0..16)
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_SetPriority (uint_8t IRQn, uint_8t priority);

/**
 * @brief   Function to Read peripheral Priority 
 * @param   IRQn        Variable of uint_8t , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   priority    Pointer to uint_8t , Priority which to be read
 * @return  OK | NOT_OK
 */
uint_8t DNVIC_GetPriority (uint_8t IRQn, uint_8t *priority);

/**
 * @brief   Function to Disable All peripherals interrupt
 * @param   NA
 * @return  NA
 */
void DNVIC_voidDisableAllPeripherals(void);

/**
 * @brief   Function to Enable All peripherals Interrupt
 * @param   NA
 * @return  NA
 */
void DNVIC_voidEnableAllPeripherals(void);

/**
 * @brief   Function to Disable all faults Interrupts
 * @param   NA
 * @return  NA
 */
void DNVIC_voidDisableAllFaults(void);

/**
 * @brief   Function to Enable all faults Interrupts
 * @param   NA
 * @return  NA
 */

void DNVIC_voidEnableAllFaults(void);

/**
 * @brief   Function to disable interrupts only with priority lower than certain level 
 * @param   priority Variable of uint_8t , Priority (0..16)
 * @return  NA
 */
void DNVIC_voidSetBASEPRI(uint_8t priority);
/**
 * @brief   Function to change vector Table offest  
 * @param   offset Variable of uint_32t , Change vector Table offest  
 * @return  NA
 */
void DNVIC_voidChangeVectorOffset (uint_32t offset);
/**
 * @brief   Function to make Software reset 
 * @param   NA 
 * @return  NA
 */
void DNVIC_voidSysReset(void);
#endif /* DNVIC_H_ */
