#include "Lpuart.h"

extern Lpuart_ConfigType Lpuart1;

void LPUART1_RxTx_IRQHandler(void);

void LPUART1_RxTx_IRQHandler(void)
{
		Lpuart_IRQHandler(&Lpuart1);
}


