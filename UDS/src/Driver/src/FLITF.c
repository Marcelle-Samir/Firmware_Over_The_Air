/**
 * @file FLITF.c
 * @author Amr (Ibrahimamr222@gmail.com)
 * @brief This file is the Implementation for Flash Driver Interface for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"
/**
 * @headerfile FLITF.h
 */
#include "FLITF.h"
/**
 * @typedef		FLITF_t  
 * @brief		Struct of All Registers in Flash Driver
 *				Registers :
 *				 		FLASH_ACR   	-> configuration register    
 * 						FLASH_KEYR	 	-> input data register        
 * 						FLASH_OPTKEYR  	-> output data register       
 *						FLASH_SR 		-> bit set/reset register     
 * 						FLASH_CR 		-> bit reset register         
 * 						FLASH_AR 		-> configuration lock register
 * 						FLASH_RESERVED	->
 * 						FLASH_OPR 		->
 * 						FLASH_WRPR		->
 */
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
/**
 * @def		FPEC 
 * @brief 	Casting Base Address of Flash Driver as Pointer to struct FLITF_t 
 * 
 */
#define FPEC ((FLITF_t *)(0x40022000))
/**
 * @def 	HALF_WORD_LEN 
 * @brief 	HNo of bytes of Half Word 
 */
#define HALF_WORD_LEN  2
/**
 *	@def  	KEY1 
 *  @brief 	KEY1 to unlock Flash to write on it 
 */
#define KEY1 ( 0x45670123 )
/**
 *	@def  	KEY2 
 *  @brief 	KEY2 to unlock Flash to write on it 
 */
#define KEY2 ( 0xcdef89ab )


/* CR Register*/
/**
 * @def 	LOCK 
 * @brief 	used to lock Flash 
 */
#define LOCK 						0x00000080
/**
 * @def 	START 
 * @brief 	used to trigger an ERASE operation when set 
 */
#define START  						0x00000040
/**
 * @def 	MASS_ERASE 
 * @brief 	used to earse all the Flash 
 */
#define MASS_ERASE 					0x00000004
/**
 * @def 	PAGE_ERASE 
 * @brief 	used to earse page  
 */
#define PAGE_ERASE 					0x00000002
/**
 * @def 	PROGRAM_ENABLE  
 * @brief 	used to enable  falsh programming 
 */
#define PROGRAM_ENABLE  			0x00000001
/**
 * @def 	MER_RESET 
 * @brief 	used to reset Mass Erase bit. 
 */
#define MER_RESET					0x00001FFB
/* SR Register */
/**
 * @def 	EOP 
 * @brief 	used to indicate that a Flash operation is completed
 */
#define EOP							0x00000020


void Flash_Lock(void){
	FPEC->FLASH_CR |= LOCK;
}

void Flash_Unlock(void){
	FPEC->FLASH_KEYR = (uint_32t)KEY1;

	FPEC->FLASH_KEYR = (uint_32t)KEY2;

}

/*void Flash_MassErase(void){
	while(FPEC->FLASH_SR & BUSY);
	FPEC->FLASH_CR |= MASS_ERASE;
	FPEC->FLASH_CR |= START;
	FPEC->FLASH_CR &= MER_RESET;
}*/


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
/*
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
*/
