/**
 * @file DNVIC.c
 * @author Ahmed Qandeel (Ahmed.qandeel96@gmail.com)
 * @brief This file is the Implementation for NVIC Driver for Cortex M3 
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */


/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"

/**
 * @headerfile DNVIC.h
 */
#include "DNVIC.h"

/**
 * @def 	NVIC_BASE_ADDRESS
 * @brief 	NVIC peripheral base address 
 */
#define NVIC_BASE_ADDRESS  (( NVIC_t*) 0XE000E100)
/**
 * @def 	SCB_AIRCR
 * @brief 	NVIC Application Interrupt and Reset Control Register 
 */
#define SCB_AIRCR *((volatile uint_32t*) 0XE000ED0C)

/**
 * @def 	SCB_VTOR
 * @brief 	Vector Table Offset register
 */
#define SCB_VTOR  *((volatile uint_32t*) 0xE000ED08)

/**
 * @def 	PASSWORD_MASK
 * @brief 	Password to make Software reset 
 */
#define PASSWORD_MASK  0X05FA0000

/**
 * @def 	FLASH_BASE_ADDRESS
 * @brief 	Base Address of Flash
 */
#define FLASH_BASE_ADDRESS 0x08000000

/**
 * @def 	OFFSET_POSITION
 * @brief 	used in shifting offest value to be corresponding for offest bits in Regsiter 
 */
#define OFFSET_POSITION 0x08

/**
 * @def 	RESET_MASK
 * @brief 	Base Address of Flash
 */
#define RESET_MASK 0x04
/**
 * @typedef		NVIC_t 
 * @brief		Struct of All Registers in NVIC Driver	
 */
typedef struct
{
	uint_32t ISER[8];
	uint_32t Reserved[24];
	uint_32t ICER[8];
	uint_32t Reserved1[24];
	uint_32t ISPR[8];
	uint_32t Reserved2[24];
	uint_32t ICPR[8];
	uint_32t Reserved3[24];
	uint_32t IABR[8];
	uint_32t Reserved4[56];
	uint_8t IPR[240];
}NVIC_t;



/**
 * @brief NV pointer to struct NVIC_t 
 */
NVIC_t   *NV=NVIC_BASE_ADDRESS;


uint_8t DNVIC_EnableIRQ(uint_8t IRQn)
{
	if( IRQn<240)
	{
		NV->ISER[IRQn/32]=1<<IRQn%32;
	}
	else
	{
		return NOK;
	}
	return OK;
}


uint_8t DNVIC_DisableIRQ(uint_8t IRQn)
{
	if( IRQn<240)
	{
		NV->ICER[IRQn/32]= 1<<IRQn%32;
	}
	else
	{
		return NOK;
	}
	return OK;
}

uint_8t DNVIC_SetPendingIRQ (uint_8t IRQn)
{
	if( IRQn<240)
	{
		NV->ISPR[IRQn/32] = 1<<IRQn%32;
	}
	else
	{
		return NOK;
	}
	return OK;
}

uint_8t DNVIC_ClearPendingIRQ (uint_8t IRQn)
{
	if( IRQn<240)
	{
		NV->ICPR[IRQn/32] = 1<<IRQn%32;
	}
	else
	{
		return NOK;
	}
	return OK;
}

uint_8t DNVIC_GetPendingIRQ (uint_8t IRQn, uint_8t *Val)
{
	if( IRQn<240)
	{
		*Val= (NV->ICPR[IRQn/32] >> IRQn%32) & 1 ;
	}
	else
	{
		return NOK;
	}
	return OK;
}

uint_8t DNVIC_GetActive (uint_8t IRQn, uint_8t *Val)
{
	if( IRQn<240)
	{
		*Val= (NV->IABR[IRQn/32] >> IRQn%32) & 1 ;
	}
	else
	{
		return NOK;
	}
	return OK;
}

uint_8t DNVIC_SetPriorityGrouping(uint_32t priority_grouping)
{
	if(priority_grouping==ALL_PREEMPTION || priority_grouping==THREE_PREEMPTION_ONE_SUBGROUP || priority_grouping==TWO_PREEMPTION_TWO_SUBGROUP || priority_grouping==ONE_PREEMPTION_THREE_SUBGROUP || priority_grouping==ALL_SUBGROUP )
	{
		SCB_AIRCR=priority_grouping|PASSWORD_MASK;
	}
	else
	{
		return NOK;
	}
	return OK;

}

uint_8t DNVIC_SetPriority (uint_8t IRQn, uint_8t priority)
{
	if( IRQn<240)
	{
		if(priority<16)
		{
			NV->IPR[IRQn] = priority<<4 ;
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

uint_8t DNVIC_GetPriority (uint_8t IRQn, uint_8t *priority)
{
	if( IRQn<240)
	{

		*priority=NV->IPR[IRQn]>>4 ;
	}
	else
	{
		return NOK;
	}
	return OK;
}

void DNVIC_voidDisableAllPeripherals(void)
{
	asm("MOV R0, #1");
	asm("MSR PRIMASK, R0");
}


void DNVIC_voidEnableAllPeripherals(void)
{
	asm("MOV R0, #0");
	asm("MSR PRIMASK, R0");
}

void DNVIC_voidDisableAllFaults(void)
{
	asm("MOV R0, #1");
	asm("MSR FAULTMASK, R0");
}


void DNVIC_voidEnableAllFaults(void)
{
	asm("MOV R0, #0");
	asm("MSR FAULTMASK, R0");
}

void DNVIC_voidSetBASEPRI(uint_8t priority)
{

	asm("LSLS R0,R0,#4");
	asm("MSR  BASEPRI, R0");
}
void DNVIC_voidChangeVectorOffset (uint_32t offset)
{
	SCB_VTOR = FLASH_BASE_ADDRESS | (offset<<OFFSET_POSITION);
}

void DNVIC_voidSysReset(void)
{
	SCB_AIRCR= RESET_MASK|PASSWORD_MASK;
}
