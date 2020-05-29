/*
 * EXT_INT.h
 *
 *  Created on: May 28, 2020
 *      Author: Amr Ibrahim
 */

#ifndef EXT_INT_H_
#define EXT_INT_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

typedef void (*CBF_t)(void);

#define OK 		0
#define NOT_OK 	1

#define EXTI_PIN0         0
#define EXTI_PIN1         1
#define EXTI_PIN2         2
#define EXTI_PIN3         3
#define EXTI_PIN4         0
#define EXTI_PIN5         1
#define EXTI_PIN6         2
#define EXTI_PIN7         3
#define EXTI_PIN8         0
#define EXTI_PIN9         1
#define EXTI_PIN10        2
#define EXTI_PIN11        3
#define EXTI_PIN12        0
#define EXTI_PIN13        1
#define EXTI_PIN14        2
#define EXTI_PIN15        3


#define EXTI_PORTA         0X0
#define EXTI_PORTB         0X1
#define EXTI_PORTC         0X10
#define EXTI_PORTD         0X11
#define EXTI_PORTE         0X100
#define EXTI_PORTF         0X101
#define EXTI_PORTG         0X110

uint_8t DEXTI_Init(void);
uint_8t DEXTI_SetCBF(CBF_t Call_Back);

#endif /* EXT_INT_H_ */
