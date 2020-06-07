/**
 * @file 	EXT_INT_cfg.h
 * @author 	Amr (Ibrahimamr222@gmail.com)
 * @brief 	This file is the Implementation for Flash Driver Interface for STM32F103
 * @version 0.1
 * @date 2020-06-05
 * @copyright Copyright (c) 2020
 */

#ifndef EXT_INT_CFG_H_
#define EXT_INT_CFG_H_

/**
 * @def 	NUMOFEXTI
 * @brief 	Number of External Interrupts 
 */
#define NUMOFEXTI			1

/**
 * @def		RISING_EDGE
 * @brief 	Interrupt happens at rising edge 
 */
#define RISING_EDGE			0

/**
 * @def		FALLING_EDGE
 * @brief 	Interrupt happens at falling edge 
 */
#define FALLING_EDGE		1

/**
 * @def		RISING_FALLING_EDGE
 * @brief 	Interrupt happens at rising and falling edge 
 */
#define RISING_FALLING_EDGE	2


/**
 * @def 	EXTICR1
 * @brief 	Configuration for Pins from 0 - 3 at any port 
 */
#define EXTICR1 		1

/**
 * @def 	EXTICR2
 * @brief 	Configuration for Pins from 4 - 7 at any port 
 */
#define EXTICR2 		2

/**
 * @def 	EXTICR3
 * @brief 	Configuration for Pins from 8 - 11 at any port 
 */
#define EXTICR3 		3

/**
 * @def 	EXTICR4
 * @brief 	Configuration for Pins from 12 - 15 at any port 
 */
#define EXTICR4 		4
/**
 * @typedef EXTI_CFG_t
 * @brief	Struct of configuration of External Interrupt 
 */
typedef struct {
	GPIO_t GPIO_PIN;
	uint_32t Edge;
	uint_32t EXTICR_Channel ;
	uint_32t EXTI_Port;
	uint_32t EXTI_Pin;
}EXTI_CFG_t;




#endif /* EXT_INT_CFG_H_ */
