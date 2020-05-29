#include "DRCC.h"
#include "DGPIO.h"
#include "DNVIC.h"
#include "EXT_INT.h"
#include "DSYSTICK.h"
#include "Sched.h"
void blink (void);
void EXTI0_CBF (void);
task_t task1 ={.periodicity=500,.Runnable = blink};

	GPIO_t testPin={
			.Port=PORT_C,
			.Pin =PIN_13,
			.Mode=MODE_PIN13_OP_OD,
			.Speed=SPEED_PIN13_2MHZ
	};
int main (void)
{

	RCC_SetPriephralStatus(GPIO_A_ENABLE,ON);
	RCC_SetPriephralStatus(GPIO_C_ENABLE,ON);
	RCC_SetPriephralStatus(AFIO_ENABLE,ON);
	DEXTI_Init();
	DEXTI_SetCBF(EXTI0_CBF);
	GPIO_Config(&testPin);
	GPIO_Writee(testPin.Port,testPin.Pin,CLEAR);
	Sched_Init();

	Sched_Start();
	while (1);
	return 0;
}
void blink (void)
{
	static uint_8t flag=0;
	if (!flag)
	{
		GPIO_Writee(testPin.Port,testPin.Pin,SET);
		flag =1;
	}
	else
	{
		GPIO_Writee(testPin.Port,testPin.Pin,CLEAR);
		flag =0;
	}
}
void EXTI0_CBF (void)
{
	DNVIC_voidChangeVectorOffset(0);
	DNVIC_EnableIRQ(EXTI0);
	DNVIC_SetPendingIRQ(EXTI0);

}
