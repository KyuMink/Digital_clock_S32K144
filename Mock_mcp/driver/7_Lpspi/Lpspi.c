#include "Lpspi.h"

char check_LPSPI_parameter(const Lpspi_ConfigType* ConfigPtr )
{
	if((ConfigPtr->Init.F_lpspi <= 0)||(ConfigPtr->Init.spi_speed<= 0))
	{
		return 1;
	}	
	else
	{
		return 0;
	}
		
}

void Lpspi_Init (const Lpspi_ConfigType* ConfigPtr )
{
	unsigned int SCK_diver = 0;
	unsigned int TCR_value = 0;
	/* Step 1. Check parameter */
	if (check_LPSPI_parameter(ConfigPtr))
	{
		return;
	}
	else
	{
		/* Step 2. Set divide ratio of the SCK pin*/
		SCK_diver =(( ConfigPtr->Init.F_lpspi)/ (ConfigPtr->Init.spi_prescaler) /(ConfigPtr->Init.spi_speed))-2;
			
		ConfigPtr->pSPIx->CCR |=  SCK_diver ;
		
		
		/* Step 3. 	Configures Clock Phase and Polarity */
		/*          Set Prescaler Value                */
		/*          Configures Clock Phase and Polarity                */
		/*          Setting Frame data                              */
		/*          Configures the peripheral chip select     */
		
		TCR_value =  (ConfigPtr->Init.spi_cpha << LPSPI_TCR_CPHA_SHIFT)
									|(ConfigPtr->Init.spi_cpol << LPSPI_TCR_CPOL_SHIFT)
									|(ConfigPtr->Init.spi_prescaler << LPSPI_TCR_PRESCALE_SHIFT)
									|(ConfigPtr->Init.spi_frame)
									|(ConfigPtr->Init.spi_type_tran<<LPSPI_TCR_LSBF_SHIFT)
									|(ConfigPtr->Init.spi_pcs<<LPSPI_TCR_PCS_SHIFT);

		ConfigPtr->pSPIx->TCR =TCR_value ;
		
		/* 7. Setting Transmit/Receive FIFO */
		LPSPI1->FCR &=~ (1u<<16u);
		LPSPI1->FCR |= 	3u;	
		LPSPI1->CFGR1 |=(1u<<3);
				
		/* 8. Configures LPSPI mode */ 
				/* Master mode */
				/* Debug mode */
		ConfigPtr->pSPIx->CFGR1 |=1;
		ConfigPtr->pSPIx->CR |= (1u<<3u);
		
		/* 9. Enable LPSPI module */
		ConfigPtr->pSPIx->CR |= 1u;
	
	}
	
}

void Lpspi_Transmit(LPSPI_Type *pLpspi, unsigned char *pTxBuffer, unsigned short Size)
{
	
	while(Size > 0)
	{
		/* Wait for transmit buffer to be empty */
	//	while(!(pLpspi->SR &(1u))){}

		/*2.check frame size */
		if(((pLpspi->TCR)&(0xff) )== LPSPI_FRAME_16)
		{
			/*if frame size is 16 bit*/
			/*1.load data to TDR*/
			pLpspi->TDR = *((unsigned short*)pTxBuffer);
			/*2.increament buffer address*/
			pTxBuffer+=2;
			Size -= 2;
		}
		
		else
		{
			/*if frame size is 8 bit*/
			pLpspi->TDR = *pTxBuffer;
			pTxBuffer++;
			Size--;
		}
	}

}

