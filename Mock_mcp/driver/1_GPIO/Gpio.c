#include "Gpio.h"

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return 
 */

char check_GPIO_parameter(unsigned char PinNumber) // miss check port E 17 pin
{		
	if ((PinNumber >18)||(PinNumber ==0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Gpio_Init(const Gpio_ConfigType* ConfigPtr)
{
    /* Check parameter */ 
	if (check_GPIO_parameter(ConfigPtr->GPIO_PinNumber))
	{
		return;
	}
	
	else
	{
		if (ConfigPtr->GPIO_PinMode == INPUT_MODE)
		{
			ConfigPtr->base->PDDR &=~ (1U << ConfigPtr->GPIO_PinNumber); // intput
		}
		else
		{
			ConfigPtr->base->PDOR |= (1U << ConfigPtr->GPIO_PinNumber); //output
			if(ConfigPtr->GPIO_PinLevel == HIGH )
			{
				ConfigPtr->base->PDOR |= (1U << ConfigPtr->GPIO_PinNumber); // set output high
			}
			else
			{
				ConfigPtr->base->PDOR &=~ (1U << ConfigPtr->GPIO_PinNumber); // set output lows
			}
		}
	}
}

void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value)
{
    /* Check parameter */
	if (check_GPIO_parameter(PinNumber))
	{
		return;
	}
	else
	{
		if(value == 0)
		{
			 pGPIOx ->PDOR &=~ (1u << PinNumber);
		}
		else if(value ==1)
		{
			pGPIOx ->PDOR |= (1u << PinNumber);
		}
	}
}


void GPIO_SetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    /* Check parameter */
	if (check_GPIO_parameter(PinNumber))
	{
		return;
	}
	else
	{
		pGPIOx->PDOR |= (1U << PinNumber);
	}
  
}

void GPIO_ResetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    /* Check parameter */
	if (check_GPIO_parameter(PinNumber))
	{
		return;
	}
	else
	{
		pGPIOx->PCOR |= (1U << PinNumber);
	}
}

void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    /* Check parameter */
	if (check_GPIO_parameter(PinNumber))
	{
		return;
	}
	else
	{
    pGPIOx ->PDOR ^= (1u << PinNumber);
	}
}


unsigned char GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, unsigned char PinNumber){
    /* Check parameter */
	if (check_GPIO_parameter(PinNumber))
	{
		return 0;
	}
	else
	{		
		unsigned char value;
		value = (unsigned char)((pGPIOx->PDIR >> PinNumber)& 0x01);
		return value;	
	}
}
