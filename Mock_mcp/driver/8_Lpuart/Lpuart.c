#include "Lpuart.h"

void Lpuart_Init (const Lpuart_ConfigType* ConfigPtr )
{
	unsigned int BRS_Divisor = 0; 
	/* Step 1. check parameter */
	if((ConfigPtr->Init.BaudRate <=0)||(ConfigPtr->Init.F_lpuart <=0)||(ConfigPtr->Init.OverSampling<=0))
	{
		return;
	}
	if((ConfigPtr->Init.F_lpuart <=ConfigPtr->Init.BaudRate)||(ConfigPtr->Init.BaudRate<=ConfigPtr->Init.OverSampling))
	{
		return;
	}
	/* Step 2. Setting baudrate */
	/* Step 2.1. Set Oversampling Ratio */
	ConfigPtr->Instance->BAUD &=~ 0u;     /* Clear oversampling field */
	BRS_Divisor |= (((ConfigPtr->Init.OverSampling) - 1)<<LPUART_BAUD_OSR_SHIFT);   /* Set Oversampling Ratio */

	/* Step 2.2. Set Baud Rate Modulo Divisor */
	BRS_Divisor |= (ConfigPtr->Init.F_lpuart )/(ConfigPtr->Init.BaudRate)/(ConfigPtr->Init.OverSampling);  /* Calculate Baud Rate Modulo Divisor. */
	ConfigPtr->Instance->BAUD = BRS_Divisor ;
	
	/* Step 3. Setting Frame */
	/* Step 3.1. Set parity bit */
	if( LPUART_PARITY_NONE != ConfigPtr->Init.Parity  )
	{
		if(ConfigPtr->Init.Parity == LPUART_PARITY_EVEN )
		{
			/* Set parity bit */
			ConfigPtr->Instance->CTRL &=~(1u<<0u);
		}
		else
		{
			/* Set parity bit */
			ConfigPtr->Instance->CTRL |= (1<<0);
		}
	}
	
	/* Step 3.2. Select Stop Bit Number */
	ConfigPtr->Instance->BAUD |= (unsigned int)((ConfigPtr->Init.StopBits) << LPUART_BAUD_SBNS_SHIFT);

	/* Step 3.3. Set data characters number */
	ConfigPtr->Instance->CTRL |= (unsigned int)((ConfigPtr->Init.BitMode) << LPUART_CTRL_M_SHIFT);

	/* 4. Enable transmitter & receiver */
	ConfigPtr->Instance->CTRL |= (unsigned int)((ConfigPtr->Init.Mode) << LPUART_CTRL_RE_SHIFT);	
}

void Lpuart_Transmit(LPUART_Type *pLpuart, unsigned char *pTxBuffer, unsigned short Size)
{
	
  /* Loop over until "Len" number of bytes are transferred */
	for(unsigned int i = 0 ; i < Size; i++)
	{
		/* Wait for transmit buffer to be empty  */		
		while(!((LPUART1->STAT >> LPUART_STAT_TDRE_SHIFT) & 0x1));

		 /* Check whether 9-Bit or 8-Bit Mode Select */
		if(pLpuart->CTRL & (1u<< LPUART_CTRL_M_SHIFT))
		{
			/* Handle for 9-Bit mode */
			//unsigned int data = DATA_uart;	
			// 9bit -> 8bit  - - data&0xff -> pTxBuffer[0]
			// data >> 8 & 0x01 -> pTxBuffer[1]
			unsigned int data = *(unsigned int *) pTxBuffer;			
			pLpuart->DATA = data & 0xFF;     
			pLpuart->DATA = (data >> 8) & 0x01;   		

			pTxBuffer+= 2;
		}
		else
		{
			/* This is 8bit data transfer */
			pLpuart->DATA = (*pTxBuffer & 0xFF);

			/* Implement the code to increment the buffer address */
			pTxBuffer++;
		}

	}
	
}

void Lpuart_Receive(LPUART_Type *pLpuart, unsigned char *pRxBuffer, unsigned short Size)
{
	/* Loop over until "Len" number of bytes are transferred */
	for(unsigned int i = 0 ; i < Size; i++)
	{
		/* Wait for received buffer to be full */		
		while(!((LPUART1->STAT >> LPUART_STAT_RDRF_SHIFT )&0x1)){}

		/* Check whether 9-Bit or 8-Bit Mode Select */
		if(pLpuart->CTRL & (1u << LPUART_CTRL_M_SHIFT))
		{
			/* Handle for 9-Bit mode */
			
				unsigned int data = 0;
				// Receive the 8 bits
				data |= pLpuart->DATA & 0xFF;
				// Receive the bit 9
				data |= (pLpuart->DATA & 0x100) << 8;
				// Store the received 9-bit data in the buffer
				*(unsigned int*)pRxBuffer = data;
		
				pRxBuffer += 2;
		}
		else
		{
			/* Receive 8bit data in a frame */
			*pRxBuffer  = (pLpuart-> DATA) & 0xFF ;
			/* Implement the code to increment the buffer address */
			pRxBuffer++;
		}
	}
}

void Lpuart_ReceiveDataIT(Lpuart_ConfigType *ConfigPtr, unsigned char *pRxBuffer, unsigned short Size)
{
	/* 1. Prepare Rx buffer */
    ConfigPtr->pRxBuffPtr = pRxBuffer;
    ConfigPtr->RxXferSize = Size;
    ConfigPtr->RxXferCount = Size;

	/* 2. Enable Receiver Interrupt */	
	ConfigPtr->Instance->CTRL |= (1u << LPUART_CTRL_RIE_SHIFT);
}

/* This function handles UART interrupt request */
void Lpuart_IRQHandler(Lpuart_ConfigType* ConfigPtr)
{
		/*1. Check whether 9-Bit or 8-Bit Mode Select */
		if(ConfigPtr->Instance->CTRL & (1u<< LPUART_CTRL_M_SHIFT))
		{
			/*Check whether parity setting is not ?*/
			if(ConfigPtr->Instance->CTRL & (1u<< LPUART_CTRL_PE_SHIFT))
			{
				/*1.1. Handle for 9-Bit mode */		 
				char parityError = (ConfigPtr->Instance->DATA >> 9) & 0x1;
				if (!parityError)
				{
					/* data from LPUART Data Register */
					ConfigPtr->pRxBuffPtr[0] = (ConfigPtr->Instance->DATA & (unsigned char)0xFF); 
					ConfigPtr->pRxBuffPtr[1] = ((ConfigPtr->Instance->DATA >> 8) & (unsigned char)0x01); 
					/* increment the buffer address */
					ConfigPtr->pRxBuffPtr += 2;
				}
				else
				{
					return;
				}
			}

			else
			{
				/* Get data from LPUART Data Register */
				ConfigPtr->pRxBuffPtr[0] = (ConfigPtr->Instance->DATA & (unsigned char)0xFF); 
				ConfigPtr->pRxBuffPtr[1] = ((ConfigPtr->Instance->DATA >> 8) & (unsigned char)0x01); 
				/* increment the buffer address */
				ConfigPtr->pRxBuffPtr += 2;	
			}				
					
		}
		else  /* 1.2. Receive 8bit data in a frame */
		{
			/*Check whether parity setting is not ?*/
			if(ConfigPtr->Instance->CTRL & (1u<< LPUART_CTRL_PE_SHIFT))
			{
				/*1.2.1. Use parity */
				char parityError = (ConfigPtr->Instance->DATA >>8) & 0x1;

				if (!parityError)
				{
					// Get the received data without parity bit
					ConfigPtr->pRxBuffPtr[0] = (ConfigPtr->Instance->DATA & (unsigned char)0xFF); 				

					/* increment the buffer address */
					ConfigPtr->pRxBuffPtr +=1;	
				}
				else
				{
					return;
				}
		
			}
			else /*1.2.2. No use parity */
			{
				/* Get data from LPUART Data Register */
				ConfigPtr->pRxBuffPtr[0] = (ConfigPtr->Instance->DATA & (unsigned char)0xFF); 				
				/* increment the buffer address */
				ConfigPtr->pRxBuffPtr++;
			}

		}
		
		/*2. Check whether the received data is enough ?*/
		if(--ConfigPtr->RxXferCount == 0)
		{
			/* 2.1. Disable Receiver Interrupt */
			ConfigPtr->Instance->CTRL &=~ (1u << LPUART_CTRL_RIE_SHIFT);

			/* 2.2. Invoke Call back function  */
			Lpuart_RxCpltCallback(ConfigPtr);
		} 		
}

__attribute__((weak)) void Lpuart_RxCpltCallback(Lpuart_ConfigType *ConfigPtr)
{
  /* Prevent unused argument(s) compilation warning */
  (void)ConfigPtr;

}

