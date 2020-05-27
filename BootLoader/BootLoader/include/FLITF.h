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
typedef signed short int int_32t;

#define OK 		0
#define NOT_OK 	1


/************************************************************************
 * Function name: Flash_Lock
 *
 * parameters:  Input: NA
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Lock The Flash
 ***************************************************************************/

void Flash_Lock(void);

/************************************************************************
 * Function name: Flash_Unlock
 *
 * parameters:  Input: NA     
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Unlock The Flash
 ***************************************************************************/

void Flash_Unlock(void);

/************************************************************************
 * Function name: Flash_MassErase
 *
 * parameters:  Input: NA
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to Erase all The Flash
 ***************************************************************************/

void Flash_MassErase(void);

/************************************************************************
 * Function name: Flash_ErasePage
 *
 * parameters:  Input:
 *                 PageAddress
 *                     type: uint_32t
                        Description: Start Address Of Page to be erased

 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to erase page from flash
 ***************************************************************************/

void Flash_ErasePage(uint_32t PageAddress);

/************************************************************************
 * Function name: Flash_ProgramWrite
 *
 * parameters:  Input:
 *                 StartAddress
 *                     type: Pointer To Void
 *                     Description: Start Address to write
 *
 *                 DataAddress
 *                     type: Pointer To Void
 *                     Description: Address of buffer of data
 *
 *                 DataLength
 *                     type: uint_32t
 *                     Description: Length Of Data to be written
 *
 *              Output: NA
 *              In/out: NA
 *
 * return: OK, NOT_OK
 * Description: a function to write Full Data
 ***************************************************************************/

void Flash_ProgramWrite(void * StartAddress,void * DataAddress,uint_32t DataLength);

/************************************************************************
 * Function name: Flash_HalfWord
 *
 * parameters:  Input:
 *                 StartAddress
 *                     type: Pointer To uint_16t
 *                     Description: Start Address to write
 *
 *                 Data
 *                     type: uint_16t
 *                     Description: Data to be written
 *
 *              Output: NA
 *              In/out: NA
 *
 * return: OK, NOT_OK
 * Description: a function to write Half Word Data
 ***************************************************************************/

void Flash_HalfWord(uint_16t * StartAddress,uint_16t Data);


/************************************************************************
 * Function name: Flash_FullWord
 *
 * parameters:  Input:
 *                 StartAddress
 *                     type: Pointer To uint_32t
 *                     Description: Start Address to write
 *
 *                 Data
 *                     type: uint_32t
 *                     Description: Data to be written
 *
 *              Output: NA
 *              In/out: NA
 *
 * return: OK, NOT_OK
 * Description: a function to write Full Word Data
 ***************************************************************************/

void Flash_FullWord(uint_32t * StartAddress,uint_32t Data);

#endif /* FLITF_H_ */
