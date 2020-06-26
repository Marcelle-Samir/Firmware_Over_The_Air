/**
 * @file	DGPIO.c
 * @author 	Mohanad (mohanad_sallam@hotmail.com)
 * @brief 	This file is the Implementation for GPIO Driver for STM32F103
 * @version 0.1
 * @date 	2020-06-05
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
 * @def 	GPIO_CONFIG_MASK 
 * @brief   Mask used to Clear Bits 
 */
#define GPIO_CONFIG_MASK	0x000000000000000f

/**
 * @def 	PULL_UP_MODE 
 * @brief   Configuration of Pull Up Mode
 */
#define PULL_UP_MODE    0X0C

/**
 * @def 	PULL_DOWN_MODE 
 * @brief   Configuration of Pull Down Mode
 */
#define PULL_DOWN_MODE  0X08


uint_8t GPIO_Config(GPIO_t * Pins )
{
	uint_8t i , temp = 0 ;
	uint_64t  config = 0 ;
	uint_16t  pin = 0 ;
	config  = Pins-> Mode ;
	config |= Pins-> Speed ;

	pin = Pins-> Pin ;

	for(i=0 ; i < 16 ; i++)
	{
		temp = pin &1;
		if (temp)
		{
			temp = GPIO_CONFIG_MASK & config ;
			if (temp != PULL_UP_MODE && temp != PULL_DOWN_MODE)
			{
				Pins -> Port -> CR  &= ~ ((uint_64t)GPIO_CONFIG_MASK<<i*4);
				Pins -> Port -> CR  |= ((uint_64t)temp<<i*4) ;
			}
			else if(temp == PULL_UP_MODE || temp == PULL_DOWN_MODE)
			{
				Pins -> Port -> CR  &= ~ ((uint_64t)GPIO_CONFIG_MASK<<i*4);
				Pins -> Port -> CR  |= ((uint_64t)PULL_DOWN_MODE<<i*4) ;
				if(temp==PULL_DOWN_MODE)
				{
					Pins->Port->ODR &=(uint_32t) ~(1<<i);
				}
				else if(temp==PULL_UP_MODE)
				{
					Pins->Port->ODR |= (uint_32t)(1<<i);
				}
				else
				{
					return NOK;
				}
			}
			else
			{
				return NOK;
			}
		}
		config=config>>4;
		pin=pin>>1;
	}
	return OK;
}



uint_8t GPIO_Writee(Port_t *Port, uint_16t Pins ,uint_8t State)
{

	if (State ==SET)
	{
		Port->BSRR= (uint_32t) Pins;
	}
	else if (State ==CLEAR)
	{
		Port->BRR=(uint_32t)Pins;
	}
	else
	{
		return NOK;
	}
return OK;
}

uint_8t GPIO_ReadPort(Port_t *Port,uint_16t * Value)
{
	if (Port == PORT_A ||Port == PORT_B||Port == PORT_C||Port == PORT_D)
	{

		*Value=(uint_16t)Port->IDR;
	}
	else
	{
		return NOK;
	}
	return OK;
}
uint_8t GPIO_ReadPin(Port_t *Port,uint_16t Pin,uint_8t * Value)
{

	if (Port == PORT_A ||Port == PORT_B||Port == PORT_C||Port == PORT_D)
	{
		if (Pin==PIN_0 ||Pin==PIN_1 ||Pin==PIN_2 ||Pin==PIN_3 ||Pin==PIN_4 ||Pin==PIN_5 ||Pin==PIN_6 ||Pin==PIN_7 ||Pin==PIN_8 ||Pin==PIN_9 ||Pin==PIN_10 ||Pin==PIN_11 ||Pin==PIN_12 ||Pin==PIN_13 ||Pin==PIN_14 ||Pin==PIN_15)
		{
			if (((uint_16t)Port->IDR)&Pin)
			{
				*Value=1;
			}
			else
			{
				*Value=0;
			}
		}
		else
		{
			return NOK;
		}
	}
	else
	{
		return NOK;
	}
return OK;
}



