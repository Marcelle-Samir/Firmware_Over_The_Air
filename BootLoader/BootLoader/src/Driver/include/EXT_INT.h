/**
 * @file    EXT_INT.h
 * @author  Amr (Ibrahimamr222@gmail.com)
 * @brief   This file is the Implementation for Flash Driver Interface for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef EXT_INT_H_
#define EXT_INT_H_
/**
 * @typedef CBF_t
 * @brief	Pointer to function 
 */
typedef void (*CBF_t)(void);
/**
 * @def     EXTI_PINX
 * @brief   used to choose Pin
 *          X : 0 up to 15 
 */
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
/**
 * @def     EXTI_PORTX
 * @brief   used to choose Port
 *          X : A up to G 
 */
#define EXTI_PORTA         0X0
#define EXTI_PORTB         0X1
#define EXTI_PORTC         0X10
#define EXTI_PORTD         0X11
#define EXTI_PORTE         0X100
#define EXTI_PORTF         0X101
#define EXTI_PORTG         0X110
/**
 * @brief Function to intialize External Interrupt 
 * @param void 
 * @return uint_8t : OK | NOK
 */
uint_8t DEXTI_Init(void);
/**
 * @brief Function to Set Call Back Function
 * @param Call_Back 
 * @return uint_8t 
 */
uint_8t DEXTI_SetCBF(CBF_t Call_Back);

#endif /* EXT_INT_H_ */
