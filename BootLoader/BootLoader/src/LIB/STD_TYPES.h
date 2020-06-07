/**
 * @file	STD_TYPES.h
 * @author 	Ahmed Qandeel (Ahmed.qandeel96@gmail.com)
 * @brief 	This file is STD_TYPES.h
 * @version 0.1
 * @date 	2020-06-05
 * @copyright Copyright (c) 2020
 */
#ifndef LIB_STD_TYPES_H
#define LIB_STD_TYPES_H
/**
 * @typedef uint_8t
 * @brief   Defined From unsigned char
 */
typedef unsigned char uint_8t;
/**
 * @typedef uint_16t
 * @brief   Defined From unsigned short int
 */
typedef unsigned short int uint_16t;
/**
 * @typedef uint_32t
 * @brief   Defined From unsigned long int
 */
typedef unsigned long int uint_32t;
/**
 * @typedef uint64_t
 * @brief   Defined From unsigned long long
 */
typedef unsigned long long uint_64t;
/**
 * @typedef int_8t
 * @brief   Defined From signed char
 */
typedef signed char int_8t;
/**
 * @typedef uint_16t
 * @brief   Defined From unsigned short int
 */
typedef signed short int int_16t;
/**
 * @typedef uint_32t
 * @brief   Defined From signed long int
 */
typedef signed long int int_32t;
/**
 * @def     OK
 * @brief   used in Checking No Error
 */
#define OK 		0
/**
 * @def     OK
 * @brief   used in Checking Error
 */
#define NOK  	1
/**
 * @def     BUSY
 * @brief   used in Check Status
 */
#define BUSY	2
/**
 * @def     OK
 * @brief   used in Checking
 */
#define ON 		1
/**
 * @def     OFF
 * @brief   used in Checking
 */
#define OFF  	0
/**
 * @def     NULL
 */
#define NULL 							(void*)0

#endif
