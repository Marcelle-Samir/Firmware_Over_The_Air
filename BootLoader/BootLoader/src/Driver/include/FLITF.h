/**
 * @file FLITF.c
 * @author Amr (Ibrahimamr222@gmail.com)
 * @brief This file is a user interface for Flash Driver Interface for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef FLITF_H_
#define FLITF_H_


/**
 * @brief   Function to Lock The Flash
 * @param   NA
 * @return  NA
 */
void Flash_Lock(void);

/**
 * @brief   Function to Unlock The Flash
 * @param   NA
 * @return  NA
 */
void Flash_Unlock(void);

/**
 * @brief   Function to erase all The Flash
 * @param   NA
 * @return  NA
 */
void Flash_MassErase(void);

/**
 * @brief   Function to erase page from flash
 * @param   NA
 * @return  NA
 */
void Flash_ErasePage(uint_32t PageAddress);

/**
 * @brief   Function to write Full Data
 * @param   StartAddress  pointer to void , Start address to write 
 * @param   DataAddress   pointer to void , Address of buffer of data 
 * @param   DataLength    variabe of uint_32t , Length of Data to be written 
 * @return  NA
 */
void Flash_ProgramWrite(void * StartAddress,void * DataAddress,uint_32t DataLength);

/**
 * @brief   Function to write Half Word Data
 * @param   StartAddress  pointer to uint_16t , Start address to write 
 * @param   Data          variabe of uint_16t , Data to be written 
 * @return  NA
 */
void Flash_HalfWord(uint_16t * StartAddress,uint_16t Data);

/**
 * @brief   Function to  write Full Word Data
 * @param   StartAddress  pointer to uint_32t , Start address to write 
 * @param   Data          variabe of uint_32t , Data to be written 
 * @return  NA
 */
void Flash_FullWord(uint_32t * StartAddress,uint_32t Data);

#endif /* FLITF_H_ */
