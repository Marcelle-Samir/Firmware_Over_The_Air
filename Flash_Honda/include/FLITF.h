/*
 * FLITF.h
 *
 *  Created on: May 17, 2020
 *      Author: Amr Ibrahim
 */

#ifndef FLITF_H_
#define FLITF_H_


typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed long int int_32t;

#define OK 		0
#define NOT_OK 	1

/*lock
unlock
write
erase
mass erase
write page
write word
*/

void Flash_Lock(void);
void Flash_Unlock(void);
void Flash_MassErase(void);
void Flash_ErasePage(uint_32t PageAddress);
void Flash_ProgramWrite(void * StartAddress,void * DataAddress,uint_32t DataLength);
void Flash_HalfWord(uint_16t * StartAddress,uint_16t Data);
void Flash_FullWord(uint_32t * StartAddress,uint_32t Data);
#endif /* FLITF_H_ */
