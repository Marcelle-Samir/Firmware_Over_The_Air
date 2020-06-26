/**
 * @file DRCC.c
 * @author Mostafa (mnader96@gmail.com)
 * @brief This file is the Implementation for RCC Driver for STM32F103 
 * @version 0.1
 * @date 2020-06-05
 *
 * @copyright Copyright (c) 2020
 * 
 */
 
/**
 * @headerfile STD_TYPES.h
 */
#include "STD_TYPES.h"

/**
 * @headerfile DRCC.h
 */
#include "DRCC.h"

/**
 * @def  	DRCC_BASE_ADDRESS  
 * @brief	Base Address of RCC Peripheral					
 */
#define DRCC_BASE_ADDRESS 0X40021000
/**
 * @def  	RCC_Register 
 * @brief	Base Address of RCC Registers	
 * 			Register : CR | CFGR | CIR | APB2RSTR | RCC_APB1RSTR | RCC_AHBENR | RCC_APB2ENR | RCC_APB1ENR |	RCC_BDCR |	RCC_CSR 
 */
#define RCC_CR          *((uint_32t *)(DRCC_BASE_ADDRESS + 0X00))
#define RCC_CFGR        *((uint_32t *)(DRCC_BASE_ADDRESS + 0X04))
#define RCC_CIR         *((uint_32t *)(DRCC_BASE_ADDRESS + 0X08))
#define RCC_APB2RSTR    *((uint_32t *)(DRCC_BASE_ADDRESS + 0X0C))
#define RCC_APB1RSTR    *((uint_32t *)(DRCC_BASE_ADDRESS + 0X10))
#define RCC_AHBENR      *((uint_32t *)(DRCC_BASE_ADDRESS + 0X14))
#define RCC_APB2ENR     *((uint_32t *)(DRCC_BASE_ADDRESS + 0X18))
#define RCC_APB1ENR     *((uint_32t *)(DRCC_BASE_ADDRESS + 0X1C))
#define RCC_BDCR        *((uint_32t *)(DRCC_BASE_ADDRESS + 0X20))
#define RCC_CSR         *((uint_32t *)(DRCC_BASE_ADDRESS + 0X24))


/**
 * @def  	PLLRDY_MASK  
 * @brief	PLL Ready Mask 		
 */
#define PLLRDY_MASK 	0x02000000
/**
 * @def  	HSERDY_MASK  
 * @brief	HSE Ready Mask 		
 */
#define HSERDY_MASK 	0x00020000
/**
 * @def  	HSIRDY_MASK  
 * @brief	HSI Ready Mask 		
 */
#define HSIRDY_MASK 	0x00000002
/**
 * @def  	HSI_SRC_MASK  
 * @brief	HSI Source Mask  		
 */
#define HSI_SRC_MASK 	0x00000000
/**
 * @def  	HSE_SRC_MASK  
 * @brief	HSE Source Mask  		
 */
#define HSE_SRC_MASK 	0x00000004
/**
 * @def  	PLL_SRC_MASK  
 * @brief	HSE_PLLSRC_MASK Mask  		
 */
#define PLL_SRC_MASK 	0x00000008
/**
 * @def  	HSE_PLLSRC_MASK  
 * @brief	HSE_PLL Source Mask 		
 */
#define HSE_PLLSRC_MASK				0x00010000
/**
 * @def  	HSE_PLLSRC_DIV_TWO_MASK  
 * @brief	HSE_PLL Source Mask divided by Two		
 */
#define HSE_PLLSRC_DIV_TWO_MASK		0x00030000

/**
 * @def  	HSI_PLLSRC_DIV_TWO_MASK  
 * @brief	HSI_PLL Source Mask divided by Two		
 */
#define HSI_PLLSRC_DIV_TWO_MASK		0x00000000

/**
 * @def  	PLLMULL_NUM  
 * @brief	Prescaler of PLL 
 *          NUM Range: 2 up to 16 
 * 					
 */
#define PLLMUL_2  0x00000000
#define PLLMUL_3  0x00040000
#define PLLMUL_4  0x00080000
#define PLLMUL_5  0x000C0000
#define PLLMUL_6  0x00100000
#define PLLMUL_7  0x00140000
#define PLLMUL_8  0x00180000
#define PLLMUL_9  0x001C0000
#define PLLMUL_10 0x00200000
#define PLLMUL_11 0x00240000
#define PLLMUL_12 0x00280000
#define PLLMUL_13 0x002C0000
#define PLLMUL_14 0x00300000
#define PLLMUL_15 0x00340000
#define PLLMUL_16 0x00380000
/**
 * @def  	AHB_PRESCALE_CLR  
 * @brief	AHB Prescale Clear Mask 		
 */
#define AHB_PRESCALE_CLR  0xFFFFFF0F
/**
 * @def  	APB1_PRESCALE_CLR  
 * @brief	APB1 Prescale Clear Mask 		
 */
#define APB1_PRESCALE_CLR 0xFFFFF8FF
/**
 * @def  	APB2_PRESCALE_CLR  
 * @brief	APB2 Prescale Clear Mask 		
 */
#define APB2_PRESCALE_CLR 0xFFFFC7FF

/**
 * @def  	PLL_CONFIG_CLR  
 * @brief	PLL Clear Mask  		
 */
#define PLL_CONFIG_CLR 0xFFC0FFFF
/**
 * @def  	SYS_CLK_CLR  
 * @brief	System Clock Clear Mask  		
 */
#define SYS_CLK_CLR 0xfffffffc
/**
 * @def      SW_MASK
 * @brief    System Clock Switch Mask
 */
#define SW_MASK				0x0000000C
/**
 * @def      PLL_SOURCE_MASK	
 * @brief    PLL Clock Source Switch Mask
 */
#define PLL_SOURCE_MASK		0x00030000
/**
 * @def      PLL_MUL_MASK	
 * @brief    PLL Multiplayer Mask 
 */
#define PLL_MUL_MASK		(uint_32t)0x003C0000
/**
 * @def      APB2_MASK	
 */
#define APB2_MASK			0x00003800
/**
 * @def      APB1_MASK	
 */
#define APB1_MASK			0x00000700
/**
 * @def      AHB_MASK	
 */
#define AHB_MASK			0x000000F0
/**
 * @def      APB2_PRESCALER_x_MASK
 * @brief    APB2 Prescaler MASK
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16 
 */
#define APB2_PRESCALER_NOT_DIVIDED_MASK     0x00000000
#define APB2_PRESCALER_DIV_2_MASK           0x00002000
#define APB2_PRESCALER_DIV_4_MASK           0x00002800
#define APB2_PRESCALER_DIV_8_MASK           0x00003000
#define APB2_PRESCALER_DIV_16_MASK          0x00003800

/**
 * @def      APB1_PRESCALER_x_MASK
 * @brief    APB1 Prescaler MASK
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16 
 */
#define APB1_PRESCALER_NOT_DIVIDED_MASK     0x00000000
#define APB1_PRESCALER_DIV_2_MASK           0x00000400
#define APB1_PRESCALER_DIV_4_MASK           0x00000500
#define APB1_PRESCALER_DIV_8_MASK           0x00000600
#define APB1_PRESCALER_DIV_16_MASK          0x00000700
/**
 * @def      AHB_PRESCALER_x_MASK
 * @brief    AHB Prescaler MASK
 *           x : NOT_DIVIDED or 2 or 4 or 8 or 16 or 64 or 128 or 256 or 512  
 */
#define AHB_PRESCALER_NOT_DIVIDED_MASK     0x00000000
#define AHB_PRESCALER_DIV_2_MASK           0x00000080
#define AHB_PRESCALER_DIV_4_MASK           0x00000090
#define AHB_PRESCALER_DIV_8_MASK 	       0x000000A0
#define AHB_PRESCALER_DIV_16_MASK          0x000000B0
#define AHB_PRESCALER_DIV_64_MASK          0x000000C0
#define AHB_PRESCALER_DIV_128_MASK         0x000000D0
#define AHB_PRESCALER_DIV_256_MASK         0x000000E0
#define AHB_PRESCALER_DIV_512_MASK         0x000000F0


uint_8t DRCC_SetClkStatus (uint_32t clk,uint_8t status)
{
	if ((clk>>28)==1)
	{
		switch (status)
		{
		case ON:
			RCC_CR|=clk;
			break;
		case OFF:
			RCC_CR&=~clk;
			break;
		}
		return OK;
	}
	else
	{
		return NOK;
	}
}

uint_8t DRCC_SetSystemClk (uint_32t clk)
{
	if ((clk>>29)==1)
	{
		uint_32t local_temp =RCC_CFGR;
		if (clk==HSI_SYS)
		{
			if (!(RCC_CR&HSIRDY_MASK))
			{
				return NOK;
			}
		}
		else if (clk==HSE_SYS)
		{
			if (!(RCC_CR&HSERDY_MASK))
			{
				return NOK;
			}

		}
		else if (clk==PLL_SYS)
		{
			if (!(RCC_CR&PLLRDY_MASK))
			{
				return NOK;
			}

		}
		else
		{
			return NOK;
		}
		local_temp&= SYS_CLK_CLR;
		local_temp|=clk;
		RCC_CFGR=local_temp;

		return OK;
	}
	else
	{
		return NOK;
	}
}

uint_8t DRCC_SetPLLConfig (uint_32t src, uint_8t MULL)
{

	if((src>>30)==1)
	{
		uint_32t local_temp=RCC_CFGR;
		local_temp&=PLL_CONFIG_CLR;
		local_temp|=src;
		local_temp|=MULL<<18;
		RCC_CFGR=local_temp;
		return OK;
	}
	else
		return NOK;
}

uint_8t DRCC_SetPriephralStatus (uint_32t priephral,uint_8t Status)
{
	if ((priephral>>31)==1) /*AHB shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_AHBENR|=priephral;
			break;
		case OFF :
			RCC_AHBENR&=~priephral;
			break;
		}
		return OK;
	}
	else if ((priephral>>30)==1) /*APB1 shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_APB1ENR|=priephral;
			break;
		case OFF :
			RCC_APB1ENR&=~priephral;
			break;
		}
		return OK;
	}
	else if ((priephral>>29)==1) /*APB2 shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_APB2ENR|=priephral;
			break;
		case OFF :
			RCC_APB2ENR&=~priephral;
			break;
		}
		return OK;
	}
	else
	{
		return NOK;
	}

}
uint_8t DRCC_SetBusPrescale (uint_32t Bus,uint_8t Prescale)
{
	uint_32t local_temp=RCC_CFGR;
	if ((Bus>>27)==1)
	{
		switch (Bus)
		{
		case AHB_PRESCALER:
			local_temp&=AHB_PRESCALE_CLR;
			local_temp|=Prescale<<4;
			RCC_CFGR=local_temp;
			break;
		case APB1_PRESCALER:
			local_temp&=APB1_PRESCALE_CLR;
			local_temp|=Prescale<<8;
			RCC_CFGR=local_temp;
			break;
		case APB2_PRESCALER:
			local_temp&=APB2_PRESCALE_CLR;
			local_temp|=Prescale<<11;
			RCC_CFGR=local_temp;
			break;
		}
		return OK;
	}
	else
	{
		return NOK;
	}
}


static uint_8t DRCC_GetSystemClk (uint_32t *CLK)
{


	if((RCC_CFGR&SW_MASK)==HSI_SRC_MASK)
	{
		*CLK=HSI_FREQ;
	}
	else if((RCC_CFGR&SW_MASK)==HSE_SRC_MASK)
	{
		*CLK=HSE_FREQ;
	}
	else if((RCC_CFGR&SW_MASK)==PLL_SRC_MASK)
	{
		if((RCC_CFGR&PLL_SOURCE_MASK)==HSI_PLLSRC_DIV_TWO_MASK)
			*CLK=HSI_FREQ/2;
		else if((RCC_CFGR&PLL_SOURCE_MASK)==HSE_PLLSRC_DIV_TWO_MASK)
			*CLK=HSE_FREQ/2;
		else if((RCC_CFGR&PLL_SOURCE_MASK)==HSE_PLLSRC_MASK)
			*CLK=HSE_FREQ;
		else
			return NOK;


		*CLK*=(((RCC_CFGR&PLL_MUL_MASK)>>18)+2);


	}
	else
	{
		return NOK;
	}

	return OK;


}


uint_8t DRCC_GetBusClock (uint_32t Bus,uint_32t *CLK)
{
	uint_32t LocalTemp=0;
	uint_8t LocalTempError;

	LocalTempError=DRCC_GetSystemClk(&LocalTemp);
	if(!LocalTempError)
	{
		*CLK=LocalTemp;
		if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_NOT_DIVIDED_MASK)
		{
			*CLK/=1;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_2_MASK)
		{
			*CLK/=2;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_4_MASK)
		{
			*CLK/=4;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_8_MASK)
		{
			*CLK/=8;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_16_MASK)
		{
			*CLK/=16;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_64_MASK)
		{
			*CLK/=64;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_128_MASK)
		{
			*CLK/=128;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_256_MASK)
		{
			*CLK/=256;
		}
		else if((RCC_CFGR&AHB_MASK)==AHB_PRESCALER_DIV_512_MASK)
		{
			*CLK/=512;
		}
		else
		{
			return NOK;
		}
		if(Bus==AHB_BUS)
		{
			asm ("NOP");
		}
		else if(Bus==APB1_BUS)
		{
			if((RCC_CFGR&APB1_MASK)==APB1_PRESCALER_NOT_DIVIDED_MASK)
			{
				*CLK/=1;
			}
			else if((RCC_CFGR&APB1_MASK)==APB1_PRESCALER_DIV_2_MASK)
			{
				*CLK/=2;
			}
			else if((RCC_CFGR&APB1_MASK)==APB1_PRESCALER_DIV_4_MASK)
			{
				*CLK/=4;
			}
			else if((RCC_CFGR&APB1_MASK)==APB1_PRESCALER_DIV_8_MASK)
			{
				*CLK/=8;
			}
			else if((RCC_CFGR&APB1_MASK)==APB1_PRESCALER_DIV_16_MASK)
			{
				*CLK/=16;
			}
			else
			{
				return NOK;
			}
		}
		else if(Bus==APB2_BUS)
		{
			if((RCC_CFGR&APB2_MASK)==APB2_PRESCALER_NOT_DIVIDED_MASK)
			{
				*CLK/=1;
			}
			else if((RCC_CFGR&APB2_MASK)==APB2_PRESCALER_DIV_2_MASK)
			{
				*CLK/=2;
			}
			else if((RCC_CFGR&APB2_MASK)==APB2_PRESCALER_DIV_4_MASK)
			{
				*CLK/=4;
			}
			else if((RCC_CFGR&APB2_MASK)==APB2_PRESCALER_DIV_8_MASK)
			{
				*CLK/=8;
			}
			else if((RCC_CFGR&APB2_MASK)==APB2_PRESCALER_DIV_16_MASK)
			{
				*CLK/=16;
			}
			else
			{
				return NOK;
			}
		}
		else
		{
			return NOK;
		}
	}
	else
	{
		return NOK;
	}
	return OK;
}


