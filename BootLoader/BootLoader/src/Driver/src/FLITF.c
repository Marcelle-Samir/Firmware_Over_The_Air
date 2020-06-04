/*
 * FLITF.c
 *
 *  Created on: May 17, 2020
 *      Author: Amr Ibrahim
 */
#include "FLITF.h"

typedef struct{
	volatile uint_32t FLASH_ACR          ;
	volatile uint_32t FLASH_KEYR         ;
	volatile uint_32t FLASH_OPTKEYR      ;
	volatile uint_32t FLASH_SR           ;
	volatile uint_32t FLASH_CR           ;
	volatile uint_32t FLASH_AR           ;
	volatile uint_32t FLASH_RESERVED    ;
	volatile uint_32t FLASH_OPR          ;
	volatile uint_32t FLASH_WRPR         ;
}FLITF_t;

#define FPEC ((FLITF_t *)(0x40022000))

#define HALF_WORD_LEN  2

#define KEY1 ( 0x45670123 )
#define KEY2 ( 0xcdef89ab )
/* CR Register*/
#define LOCK 						0x00000080
#define START  						0x00000040
#define MASS_ERASE 					0x00000004
#define PAGE_ERASE 					0x00000002
#define PROGRAM_ENABLE  			0x00000001
#define MER_RESET					0x00001FFB
/* SR Register */
#define EOP							0x00000020
#define BUSY 						0x00000001

void Flash_Lock(void){
	FPEC->FLASH_CR |= LOCK;
}


/*static void one(void)
{

}*/

void Flash_Unlock(void){
	FPEC->FLASH_KEYR = (uint_32t)KEY1;

	FPEC->FLASH_KEYR = (uint_32t)KEY2;

}

void Flash_MassErase(void){
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= MASS_ERASE;
	FPEC->FLASH_CR |= START;
	FPEC->FLASH_CR &= MER_RESET;
}


void Flash_ErasePage(uint_32t PageAddress){
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= PAGE_ERASE;
	FPEC->FLASH_AR  = PageAddress;
	FPEC->FLASH_CR |= START;
	while(FPEC->FLASH_SR & BUSY);
	//FPEC->FLASH_SR |= EOP;
	FPEC->FLASH_CR &= ~PAGE_ERASE;
}

void Flash_ProgramWrite(void * StartAddress,void * DataAddress,uint_32t DataLength){
	uint_32t Iterator=0;
	uint_16t temp;
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= PROGRAM_ENABLE;
	while((DataLength - 2*Iterator) >= HALF_WORD_LEN ){
		( ( uint_16t *) StartAddress )[Iterator]  = ( ( uint_16t *) DataAddress )[Iterator];
		Iterator ++;
	}
	if((DataLength - 2*Iterator)){
		temp =(( (uint_8t *) DataAddress )[2*Iterator])  | 0xff00;
		( (uint_16t *) StartAddress )[Iterator] =temp ;
	}
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_SR |= EOP;
	FPEC->FLASH_CR &= ~PROGRAM_ENABLE;

}
void Flash_HalfWord(uint_16t * StartAddress,uint_16t Data){
	FPEC->FLASH_KEYR = (uint_32t)KEY2;
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= PROGRAM_ENABLE;
	*StartAddress = Data;
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_SR |= EOP;
	FPEC->FLASH_CR &= ~PROGRAM_ENABLE;
}

void Flash_FullWord(uint_32t * StartAddress,uint_32t Data){
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= PROGRAM_ENABLE;
	*StartAddress = Data;
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_SR |= EOP;
	FPEC->FLASH_CR &= ~PROGRAM_ENABLE;
}
