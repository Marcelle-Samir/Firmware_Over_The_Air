/*
 * EXT_INT_cfg.c
 *
 *  Created on: May 28, 2020
 *      Author: Amr Ibrahim
 */

#include "DGPIO.h"
#include "EXT_INT.h"
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
