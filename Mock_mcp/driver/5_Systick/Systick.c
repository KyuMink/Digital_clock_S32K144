#include "Systick.h"

void Systick_Init(const Systick_ConfigType* ConfigPtr)
{
	unsigned int RVR;
	/* Step 1. Check parameter */
	if ((ConfigPtr->fSystick== 0)||((ConfigPtr->isInterruptEnabled != 0)&&(ConfigPtr->isInterruptEnabled != 1 )))
	{
		return;
	}
	else
	{
		/* Step 2. Configuration for SysTick timer*/
		/* Step 2. 1. Disable the SysTick timer */
		SYST_CSR = 0;
		
		/* Step 2.2. Setting the reload value */
		/* Calculate RVR */
		RVR = ((ConfigPtr->fSystick)/1000) *(ConfigPtr->period) -1;
		
		if(ConfigPtr->period != 0 )
		{
			SYST_RVR = RVR;
		} 
		else 
		{
			SYST_RVR = 0xFFFFFFu;
		}
		
		/* Step 2.3. Clear the current value */
		SYST_CVR = 0;

		/* Step 2.4. Check whether timeout interrupt is set ?*/
		if(ConfigPtr->isInterruptEnabled != 0 )
		{
			SYST_CSR |= (1<<SYST_INT_EN_SHIFT );
		}
	}
		
}

void Systick_Start(void)
{
	/* Step 1. Enables the counter */
	SYST_CSR |= (1u<<SYST_COUNTER_EN_SHIFT) ;

}

void Systick_Stop(void)
{
	/* Step 1. Disable the counter */
	SYST_CSR &=~ (1u<<SYST_COUNTER_EN_SHIFT) ;
}

unsigned int Systick_GetCounter(void)
{
	unsigned int counter;
	counter = SYST_CVR;
	return counter;
}


void Delay(unsigned int ms)
{
	unsigned int count = ms/100;
	
	SYST_CSR =0;
	SYST_RVR = ((FIRC_CLOCK)/1000 *100 ) - 1;

	SYST_CVR = 0;

	Systick_Start();
	while (count>0)
	{
		while ((SYST_CSR &(1<<16)) == 0){}
		count--;
	}
 	
	Systick_Stop();

}
