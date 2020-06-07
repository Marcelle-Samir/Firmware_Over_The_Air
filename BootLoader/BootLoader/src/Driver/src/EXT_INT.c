/**
 * @file 	EXT_INT.c
 * @author 	Amr (Ibrahimamr222@gmail.com)
 * @brief 	This file is the Implementation for Flash Driver Interface for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */
/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"
/**
 * @headerfile DRCC.h
 */
#include "DRCC.h"
/**
 * @headerfile DGPIO.h
 */
#include "DGPIO.h"
/**
 * @headerfile DNVIC.h
 */
#include "DNVIC.h"
/**
 * @headerfile EXT_INT.h
 */
#include "EXT_INT.h"
/**
 * @headerfile EXT_INT_cfg.h
 */
#include "EXT_INT_cfg.h"
/**
 * @typedef 	EXTI_t
 * @brief 		External Interrupt Registers 
 */
typedef struct {
	uint_32t EXTI_IMR ;
	uint_32t EXTI_EMR ;
	uint_32t EXTI_RTSR;
	uint_32t EXTI_FTSR;
	uint_32t EXTI_SWIER;
	uint_32t EXTI_PR;
}EXTI_t;

/**
 * @typedef 	AFIO_t
 * @brief 		Alternative Function Input Output Registers 
 */
typedef struct {
	uint_32t  AFIO_EVCR        		;
	uint_32t  AFIO_MAPR           	;
	uint_32t  AFIO_EXTICR[4]        ;
 	uint_32t  AFIO_MAPR2           	;

}AFIO_t;
/**
 * @def		EXTI 
 * @brief 	Base address of External Interrupt
 */
#define EXTI ((EXTI_t*) 0x40010400)
/**
 * @def		AFIO
 * @brief 	Base address of Alternative Function Input Output 
 */
#define AFIO ((AFIO_t*) 0x40010000)

extern EXTI_CFG_t EXTI_CFG[NUMOFEXTI];


CBF_t CBF;

uint_8t DEXTI_Init(void){


	uint_8t Counter, Local_error =OK ;

	for(Counter = 0; Counter < NUMOFEXTI ;Counter++){

		Local_error |= GPIO_Config(&(EXTI_CFG[Counter].GPIO_PIN));
		switch(EXTI_CFG[Counter].EXTICR_Channel){
		case EXTICR1:
			AFIO->AFIO_EXTICR[0] = EXTI_CFG[Counter].EXTI_Port<<(EXTI_CFG[Counter].EXTI_Pin * 4);
			break;
		case EXTICR2:
			AFIO->AFIO_EXTICR[1] = EXTI_CFG[Counter].EXTI_Port<<(EXTI_CFG[Counter].EXTI_Pin * 4);
			break;
		case EXTICR3:
			AFIO->AFIO_EXTICR[2] = EXTI_CFG[Counter].EXTI_Port<<(EXTI_CFG[Counter].EXTI_Pin * 4);
			break;

		case EXTICR4:
			AFIO->AFIO_EXTICR[3] = EXTI_CFG[Counter].EXTI_Port<<(EXTI_CFG[Counter].EXTI_Pin * 4);
			break;
		}
		switch (EXTI_CFG[Counter].Edge) {
			case RISING_EDGE:
				EXTI->EXTI_RTSR |= EXTI_CFG[Counter].GPIO_PIN.Pin;
				break;
			case FALLING_EDGE:
				EXTI->EXTI_FTSR |= EXTI_CFG[Counter].GPIO_PIN.Pin;
				break;
			case RISING_FALLING_EDGE:
				EXTI->EXTI_RTSR |= EXTI_CFG[Counter].GPIO_PIN.Pin;
				EXTI->EXTI_FTSR |= EXTI_CFG[Counter].GPIO_PIN.Pin;
				break;
		}
		EXTI->EXTI_IMR |= EXTI_CFG[Counter].GPIO_PIN.Pin;
		DNVIC_EnableIRQ(EXTI0);
	}
	return Local_error;
}

uint_8t DEXTI_SetCBF(CBF_t Call_Back){
	uint_8t Local_Error = OK;
	if(Call_Back){
		CBF = Call_Back;
	}else {
		Local_Error = NOK;
	}
return Local_Error;
}



void EXTI0_IRQHandler(void){
	EXTI->EXTI_PR |= 1;
	if(CBF){
		CBF();
	}else{
		/* MISRA */
	}
}


