/*
 * Bootloader_types.h
 *
 *  Created on: May 21, 2020
 *      Author: Ahmed Qandeel
 */

#ifndef BOOTLOADER_TYPES_H_
#define BOOTLOADER_TYPES_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define MAX_DATA_SIZE                 1024

#define RECEIVED_OK                   1
#define RECEIVED_NOK                  2

#define APP_FOUND                     0xAABBCCDD
#define NO_APP                        0xFFFFFFFF

#define COMMAND_FLASH_NEW_APP         0xAB
#define COMMAND_FLASH_WRITE_SECTOR    0xBC
#define COMMAND_RESPOND_FRAME         0xCD
#define COMMAND_END_FLASH             0xDE

#define FLASH_NEW_APP_KEY             0xAA
#define START_OF_FRAME_KEY            0xBB
#define END_FLASH_KEY                 0xCC

#define FLASH_NEW_APP_SIZE            0X10
#define FLASH_WRITE_SECTOR_SIZE       0X0C+(MAX_DATA_SIZE)
#define RESPOND_FRAME_SIZE            0x04
#define END_FLASH_SIZE                0x04

#define WAITING_NEW_APP_CMD           0
#define NEW_APP_CMD_RECEIVED          1
#define FLASH_WRITE_FINISHED          2
#define WAITING_STATE				  3

typedef struct
{
	uint_8t Start_Of_Frame       ;
	uint_8t Req_Num              ;
	uint_8t command_Num          ;
}Header_t;

typedef struct
{
	Header_t Header              ;
	uint_8t key                 ;
	uint_32t Address             ;
	uint_32t Size                ;
	uint_32t EntryPoint          ;
}FlashNewAppCmd_t;

typedef struct
{
	Header_t Header              ;
	uint_32t Address             ;
	uint_32t Size                ;
	uint_8t Data[MAX_DATA_SIZE] ;
}FlashWriteSector_t;

typedef struct
{
	Header_t Header              ;
	uint_8t  ACK_Key             ;
}RespondFrame_t;

typedef struct
{
	Header_t Header              ;
	uint_8t  End_Flashing_Key    ;
}EndFlashing_t;

#endif /* BOOTLOADER_TYPES_H_ */
