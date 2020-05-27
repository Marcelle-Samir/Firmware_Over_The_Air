/*******************************************************************************************************************************************************/

/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.1*/
/*NAME: standard types */
/*******************************************************************************************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H
typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

typedef enum{
	OK,
	NOK,
	NULLPOINTER
}StdError;
/*********************************************************************************************************************/

//#define NULL ( (void *) 0)

#endif
