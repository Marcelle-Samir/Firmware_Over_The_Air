/*
 * DNVIC.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Ahmed Qandeel
 */

#ifndef DNVIC_H_
#define DNVIC_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK		0
#define NOT_OK 	1

/*************************************
 *******PERIPHERAL_INTERRUPTS*********
 *************************************/
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

/************************************************************************
 * Function name: DNVIC_EnableIRQ
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Enable peripheral Interrupt
 ***************************************************************************/

uint_8t DNVIC_EnableIRQ(uint_8t IRQn);

/************************************************************************
 * Function name: DNVIC_DisableIRQ
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Disable peripheral Interrupt
 ***************************************************************************/

uint_8t DNVIC_DisableIRQ(uint_8t IRQn);

/************************************************************************
 * Function name: DNVIC_SetPendingIRQ
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Set Peripheral Pending Interrupt Flag By Software
 ***************************************************************************/

uint_8t DNVIC_SetPendingIRQ (uint_8t IRQn);

/************************************************************************
 * Function name: DNVIC_ClearPendingIRQ
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to ReSet Peripheral Pending Interrupt Flag By Software
 ***************************************************************************/

uint_8t DNVIC_ClearPendingIRQ (uint_8t IRQn);

/************************************************************************
 * Function name: DNVIC_GetPendingIRQ
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: VAL
 *                      type: pointer to uint_8t
 *                      Description: Pending Flag which to be read
 * return: OK, NOT_OK
 * Description: a function to get Pending Flag Value
 ***************************************************************************/

uint_8t DNVIC_GetPendingIRQ (uint_8t IRQn, uint_8t *Val);

/************************************************************************
 * Function name: DNVIC_GetActive
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: VAL
 *                      type        : pointer to uint_8t
 *                      Description : Active Flag which to be read
 * return: OK, NOT_OK
 * Description: a function indicate which interrupts are active.
 ***************************************************************************/

uint_8t DNVIC_GetActive (uint_8t IRQn, uint_8t *Val);
/**********************************************************************************************************************/

/*************************************
 ************PRIORITY_GROUPING********
 *************************************/
#define ALL_PREEMPTION						0X00000300
#define THREE_PREEMPTION_ONE_SUBGROUP		0X00000400
#define TWO_PREEMPTION_TWO_SUBGROUP			0X00000500
#define ONE_PREEMPTION_THREE_SUBGROUP		0X00000600
#define ALL_SUBGROUP						0X00000700

/************************************************************************
 * Function name: DNVIC_SetPriorityGrouping
 *
 * parameters:  Input:
 *                 priority_grouping
 *                     type: uint_32t
 *                      Description: Priority Type (ALL_PREEMPTION                , THREE_PREEMPTION_ONE_SUBGROUP
 *                                                  TWO_PREEMPTION                ,_TWO_SUBGROUP
 *                                                  ONE_PREEMPTION_THREE_SUBGROUP , ALL_SUBGROUP                )
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function provides priority grouping control for the exception model
 ***************************************************************************/

uint_8t DNVIC_SetPriorityGrouping(uint_32t priority_grouping);

/************************************************************************
 * Function name: DNVIC_SetPriority
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                      Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *                 priority
 *                     type: uint_8t
 *                     Description: Priority (0..16)
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Set Interrupt Priority
 ***************************************************************************/

uint_8t DNVIC_SetPriority (uint_8t IRQn, uint_8t priority);

/************************************************************************
 * Function name: DNVIC_GetPriority
 *
 * parameters:  Input:
 *                 IRQn
 *                     type: uint_8t
 *                     Description: Interrupt Request Number (WWDG			, PVD
 *                                                            TAMPER		, RTC
 *                                                            FLASH			, RCCINT
 *                                                            EXTI0			, EXTI1
 *                                                            EXTI2			, EXTI3
 *                                                            EXTI4			, DMA1_CHANNEL1
 *                                                            DMA1_CHANNEL2	, DMA1_CHANNEL3
 *                                                            DMA1_CHANNEL4	, DMA1_CHANNEL5
 *                                                            DMA1_CHANNEL6	, DMA1_CHANNEL7
 *                                                            ADC1_2		, USB_HP_CAN_TX
 *                                                            USB_LP_CAN_RX0, CAN_RX1
 *                                                            CAN_SCE		, EXTI9_5
 *                                                            TIM1_BRK		, TIM1_UP
 *                                                            TIM1_TRG_COM	, TIM1_CC
 *                                                            TIM2			, TIM3
 *                                                            TIM4			, I2C1_EV
 *                                                            I2C1_ER		, I2C2_EV			                                          		,
 *                                                            I2C2_ER		, SPI1
 *                                                            SPI2			, USART1
 *                                                            USART2		, USART3
 *                                                            EXTI15_10		, RTCALARM
 *                                                            USBWAKEUP		, TIM8_BRK
 *                                                            TIM8_UP		, TIM8_TRG_COM
 *                                                            TIM8_CC		, ADC3
 *                                                            FSMC			, SDIO
 *                                                            TIM5			              )
 *
 *              Output: NA
 *              In/out: VAL
 *                      type        : pointer to uint_8t
 *                      Description : Priority which to be read
 * return: OK, NOT_OK
 * Description: a function to Read peripheral Priority
 ***************************************************************************/

uint_8t DNVIC_GetPriority (uint_8t IRQn, uint_8t *priority);

/************************************************************************
 * Function name: DNVIC_voidDisableAllPeripherals
 *
 * parameters:  NA
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Disable All peripherals interrupt
 ***************************************************************************/

void DNVIC_voidDisableAllPeripherals(void);

/************************************************************************
 * Function name: DNVIC_voidEnableAllPeripherals
 *
 * parameters:  NA
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Enable All peripherals interrupt
 ***************************************************************************/

void DNVIC_voidEnableAllPeripherals(void);

/************************************************************************
 * Function name: DNVIC_voidDisableAllFaults
 *
 * parameters:  NA
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Disable all faults Interrupts
 ***************************************************************************/

void DNVIC_voidDisableAllFaults(void);

/************************************************************************
 * Function name: DNVIC_voidEnableAllFaults
 *
 * parameters:  NA
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Enable all faults Interrupts
 ***************************************************************************/

void DNVIC_voidEnableAllFaults(void);

/************************************************************************
 * Function name: DRCC_SetClkStatus
 *
 * parameters:  Input:
 *                 clk
 *                     type: uint_8t
 *                     Description: Priority (HSI_ENABLE,HSE_ENABLE,PLL_ENABLE)
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to set Base Priority
 ***************************************************************************/
void DNVIC_voidSetBASEPRI(uint_8t priority);


#endif /* DNVIC_H_ */
