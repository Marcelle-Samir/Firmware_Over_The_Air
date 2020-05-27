typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK 		0
#define NOT_OK 	1

#define ON 		1
#define OFF 	0

/*************************************
 *********CLOCK_STATUS_TYPES**********
 *************************************/

#define HSI_ENABLE 0x10000001
#define HSE_ENABLE 0x10010000
#define PLL_ENABLE 0x11000000

/************************************************************************
 * Function name: DRCC_SetClkStatus
 *
 * parameters:  Input:
 *                 clk
 *                     type: uint_32t
                       Description: Clock Type (HSI_ENABLE,HSE_ENABLE,PLL_ENABLE)
 *                status
 *                     type: uint_8t
 *                     Description: Clock Status Parameters(ON,OFF)
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to set the Clock state
 ***************************************************************************/

uint_8t DRCC_SetClkStatus (uint_32t clk,uint_8t status);

/*******************************************************************************************************************/

/*************************************
 *********CLOCK_SYSTEM_TYPES**********
 *************************************/

#define HSI_SYS    0x20000000
#define HSE_SYS    0x20000001
#define PLL_SYS    0x20000002

/************************************************************************
 * Function name: DRCC_SetSystemClk
 *
 * parameters:  Input:
 *                 clk
 *                     type: uint_32t
                        Description: Clock types to be assigned as system clock(HSI_SYS,HSE_SYS,PLL_SYS)

 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function Set the system Clock
 ***************************************************************************/

uint_8t DRCC_SetSystemClk (uint_32t clk);

/*****************************************************************************************************************/

/*************************************
 *********PLL_CLOCK_SOURCE************
 *************************************/
#define HSE_SRC				0x40010000
#define HSE_SRC_DIV_TWO		0x40030000
#define HSI_SRC_DIV_TWO		0x40000000

/*************************************
 *****PLL_MULTIPLICATION_FACTORS******
 *************************************/
#define PLL_input_clock_x_2    0
#define PLL_input_clock_x_3    1
#define PLL_input_clock_x_4    2
#define PLL_input_clock_x_5    3
#define PLL_input_clock_x_6    4
#define PLL_input_clock_x_7    5
#define PLL_input_clock_x_8    6
#define PLL_input_clock_x_9    7
#define PLL_input_clock_x_10   8
#define PLL_input_clock_x_11   9
#define PLL_input_clock_x_12   10
#define PLL_input_clock_x_13   11
#define PLL_input_clock_x_14   12
#define PLL_input_clock_x_15   13
#define PLL_input_clock_x_16   14

/************************************************************************
 * Function name: DRCC_SetPLLConfig
 *
 * parameters:  Input:
 *                 src
 *                     type: uint_32t
                        Description: Type of Clock source to PLL (HSE_SRC,HSE_SRC_DIV_TWO,HSI_SRC_DIV_TWO)
 *                 Pin
 *                     type: u8
 *                     Description: Multiplication Factor (PLL_input_clock_x_2  ,  PLL_input_clock_x_3 ,
 *                                                         PLL_input_clock_x_5  ,  PLL_input_clock_x_4 ,
 *                                                         PLL_input_clock_x_6  ,  PLL_input_clock_x_7 ,
 *                                                         PLL_input_clock_x_8  ,  PLL_input_clock_x_9 ,
 *                                                         PLL_input_clock_x_10 , PLL_input_clock_x_11 ,
 *                                                         PLL_input_clock_x_12 , PLL_input_clock_x_13 ,
 *                                                         PLL_input_clock_x_14 , PLL_input_clock_x_15 ,
 *                                                         PLL_input_clock_x_16)
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to Configure Clock source of PLL and it's multiplication Factor
 ***************************************************************************/

uint_8t DRCC_SetPLLConfig (uint_32t src, uint_8t MULL);

/*****************************************************************************************************************/

/*************************************
 ************PERIPHERALS**************
 *************************************/
#define GPIO_A_ENABLE 	0x20000004
#define GPIO_B_ENABLE 	0x20000008
#define GPIO_C_ENABLE 	0x20000010
#define GPIO_D_ENABLE 	0x20000020
#define GPIO_E_ENABLE 	0x20000040
#define GPIO_F_ENABLE 	0x20000080
#define GPIO_G_ENABLE 	0x20000100
#define USART_1_ENABLE	0x20004000
#define DMA_1_ENABLE	0x80000001

/************************************************************************
 * Function name: DRCC_SetPriephralStatus
 *
 * parameters:  Input:
 *                 priephral
 *                     type: uint_32t
 *                       Description: Peripherals Numbers (GPIO_A_ENABLE, GPIO_B_ENABLE,
 *                                                         GPIO_C_ENABLE, GPIO_D_ENABLE,
 *                                                         GPIO_E_ENABLE, GPIO_F_ENABLE,
 *                                                         GPIO_G_ENABLE, USART_1_ENABLE
 *                                                         DMA_1_ENABLE                )
 *                 Status
 *                     type: uint_8t
 *                     Description: Clock Status Parameters(ON,OFF)
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to Enable/Disable Clock to peripheral
 ***************************************************************************/

uint_8t DRCC_SetPriephralStatus (uint_32t priephral,uint_8t Status);

/*****************************************************************************************************************/

/*************************************
 ************BUSES********************
 *************************************/
#define AHB_PRESCALER  0x08000000
#define APB1_PRESCALER 0x08000001
#define APB2_PRESCALER 0x08000002

/*************************************
 ************APB2_PRESCALER***********
 *************************************/
#define APB2_PRESCALER_NOT_DIVIDED 0
#define APB2_PRESCALER_DIV_2       4
#define APB2_PRESCALER_DIV_4       5
#define APB2_PRESCALER_DIV_8       6
#define APB2_PRESCALER_DIV_16      7

/*************************************
 ************APB1_PRESCALER***********
 *************************************/
#define APB1_PRESCALER_NOT_DIVIDED 0
#define APB1_PRESCALER_DIV_2       4
#define APB1_PRESCALER_DIV_4       5
#define APB1_PRESCALER_DIV_8       6
#define APB1_PRESCALER_DIV_16      7

/*************************************
 ************AHB_PRESCALER*************
 *************************************/
#define AHB_PRESCALER_NOT_DIVIDED 0
#define AHB_PRESCALER_DIV_2       8
#define AHB_PRESCALER_DIV_4       9
#define AHB_PRESCALER_DIV_8   	 10
#define AHB_PRESCALER_DIV_16     11
#define AHB_PRESCALER_DIV_64     12
#define AHB_PRESCALER_DIV_128    13
#define AHB_PRESCALER_DIV_256    14
#define AHB_PRESCALER_DIV_512    15

/************************************************************************
 * Function name: DRCC_SetBusPrescale
 *
 * parameters:  Input:
 *                 Bus
 *                     type: uint_32t
 *                       Description: Bus Number (AHB_PRESCALER, APB1_PRESCALER, APB2_PRESCALER)
 *                 Prescale
 *                     type: uint_8t
 *                     Description: Bus Prescaler (APB2_PRESCALER_NOT_DIVIDED , APB2_PRESCALER_DIV_2
 *												   APB2_PRESCALER_DIV_4       , APB2_PRESCALER_DIV_8
 *                                                 APB2_PRESCALER_DIV_16      ,
 *
 *                                                 APB1_PRESCALER_NOT_DIVIDED , APB1_PRESCALER_DIV_2
 *                                                 APB1_PRESCALER_DIV_4       , APB1_PRESCALER_DIV_8
 *                                                 APB1_PRESCALER_DIV_16      ,
 *
 *                                                 AHB_PRESCALER_NOT_DIVIDED  , AHB_PRESCALER_DIV_2
 *                                                 AHB_PRESCALER_DIV_4        , AHB_PRESCALER_DIV_8
 *                                                 AHB_PRESCALER_DIV_16       , AHB_PRESCALER_DIV_64
 *                                                 AHB_PRESCALER_DIV_128      , AHB_PRESCALER_DIV_256
 *                                                 AHB_PRESCALER_DIV_512                            )
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: E_OK, E_NOK
 * Description: a function to set Bus Prescaler
 ***************************************************************************/

uint_8t DRCC_SetBusPrescale (uint_32t Bus,uint_8t Prescale);

/*****************************************************************************************************************/

/*************************************
 ************Bus_FREQUENCY*************
 *************************************/
#define HSI_FREQ	8000000
#define HSE_FREQ	8000000

/*************************************
 ************BUS**********************
 *************************************/
#define AHB_BUS  77
#define APB1_BUS 78
#define APB2_BUS 79

/************************************************************************
 * Function name: DRCC_GetBusClock
 *
 * parameters:  Input:
 *                 Bus
 *                     type: uint_32t
 *                     Description: Bus Number (AHB_BUS APB1_BUS APB2_BUS)
 *
 *              Output: NA
 *              In/out: CLK
 *                     type: pointer to uint_32t
 *                     Description: Clock which to be read
 * return: E_OK, E_NOK
 * Description: a function to get bus Clock
 ***************************************************************************/
uint_8t DRCC_GetBusClock (uint_32t Bus,uint_32t *CLK);


