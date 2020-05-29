#include "DGPIO.h"


#define GPIO_CONFIG_MASK	0x000000000000000f


#define PULL_UP_MODE    0X0C
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
					return NOT_OK;
				}
			}
			else
			{
				return NOT_OK;
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
		return NOT_OK;
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
		return NOT_OK;
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
			return NOT_OK;
		}
	}
	else
	{
		return NOT_OK;
	}
return OK;
}



