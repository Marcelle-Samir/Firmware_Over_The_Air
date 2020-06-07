/**
 * @file 	EXT_INT_cfg.c
 * @author 	Amr (Ibrahimamr222@gmail.com)
 * @brief 	This file is the Implementation for External Interrupt Configuration for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */
/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"
/**
 * @headerfile DGPIO.h
 */
#include "DGPIO.h"
/**
 * @headerfile EXT_INT.h
 */
#include "EXT_INT.h"
/**
 * @headerfile EXT_INT_cfg.h
 */
#include "EXT_INT_cfg.h"


EXTI_CFG_t EXTI_CFG[NUMOFEXTI] = {
		{ .GPIO_PIN.Pin = PIN_0,
		  .GPIO_PIN.Mode = MODE_PIN0_AF_PP,
		  .GPIO_PIN.Speed =SPEED_PIN0_INPUT,
		  .GPIO_PIN.Port = PORT_A,
		  .Edge = RISING_EDGE,
		  .EXTICR_Channel = EXTICR1,
		  .EXTI_Port = EXTI_PORTA,
		  .EXTI_Pin = EXTI_PIN0
		}
};
