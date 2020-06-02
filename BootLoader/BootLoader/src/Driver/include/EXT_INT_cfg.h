/*
 * EXT_INT_cfg.h
 *
 *  Created on: May 28, 2020
 *      Author: Amr Ibrahim
 */

#ifndef EXT_INT_CFG_H_
#define EXT_INT_CFG_H_

#define NUMOFEXTI			1
#define RISING_EDGE			0
#define FALLING_EDGE		1
#define RISING_FALLING_EDGE	2


/* Pin 0 - 3 */
#define EXTICR1 		1
/* Pin 4 - 7 */
#define EXTICR2 		2
/* Pin 8 - 11 */
#define EXTICR3 		3
/* Pin 12 - 15 */
#define EXTICR4 		4

typedef struct {
	GPIO_t GPIO_PIN;
	uint_32t Edge;
	uint_32t EXTICR_Channel ;
	uint_32t EXTI_Port;
	uint_32t EXTI_Pin;
}EXTI_CFG_t;




#endif /* EXT_INT_CFG_H_ */
