/*
 * EXT_IXNT.c
 *
 *  Created on: May 28, 2020
 *      Author: Amr Ibrahim
 */
#include "DRCC.h"
#include "DGPIO.h"
#include "DNVIC.h"
#include "EXT_INT.h"
#include "EXT_INT_cfg.h"

typedef struct {
	uint_32t EXTI_IMR ;
	uint_32t EXTI_EMR ;
	uint_32t EXTI_RTSR;
	uint_32t EXTI_FTSR;
	uint_32t EXTI_SWIER;
	uint_32t EXTI_PR;
}EXTI_t;


typedef struct {
	uint_32t  AFIO_EVCR        		;
	uint_32t  AFIO_MAPR           	;
	uint_32t  AFIO_EXTICR[4]        ;
 	uint_32t  AFIO_MAPR2           	;

}AFIO_t;

#define EXTI ((EXTI_t*) 0x40010400)
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
		Local_Error = NOT_OK;
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


