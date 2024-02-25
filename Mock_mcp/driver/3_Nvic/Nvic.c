#include "Nvic.h"

char check_IRQn(unsigned int IRQ_number)
{
	if (IRQ_number >155)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

char check_priority(unsigned int priority)
{
	if ( (priority > 255))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void NVIC_EnableInterrupt(IRQn_Type IRQ_number)
{
	unsigned char value = IRQ_number;
	if (check_IRQn(value ))
	{
		return;
	}	
	NVIC->ISER[IRQ_number/32] |= (1<<(IRQ_number%32));
}

void NVIC_DisableInterrupt(IRQn_Type IRQ_number)
{
	unsigned char value = IRQ_number;
	if (check_IRQn(value ))
	{
		return;
	}	
	NVIC->ICER[IRQ_number/32]|=(1<<(IRQ_number%32));
}


void NVIC_ClearPendingFlag(IRQn_Type IRQ_number)
{
	unsigned char value = IRQ_number;
	if (check_IRQn(value ))
	{
		return;
	}	
	NVIC->ICPR[IRQ_number/32]|=(1<<(IRQ_number%32));
}


void NVIC_SetPriority(IRQn_Type IRQ_number, unsigned int priority)
{
	unsigned char value = IRQ_number;
	if (check_IRQn(value ))
	{
		return;
	}	
	if (check_priority(priority))
	{
		return;
	}	

	NVIC->IPR[IRQ_number/4]|=(unsigned int)(priority <<(4+((IRQ_number % 4) * 8 )));   
   
}
