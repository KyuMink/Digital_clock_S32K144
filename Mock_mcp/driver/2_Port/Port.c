#include "Port.h"

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
Port_ret_t Port_Init(const Port_ConfigType* ConfigPtr)
{
	/* ++[Auto variable declaration] */
	Port_mux_t muxing;
	unsigned int regValue;
	Port_ret_t ret;

	 /* ++[Internal variable initialization] */
	ret = PORT_OK;
	regValue = ConfigPtr->base->PCR[ConfigPtr->pinPortIdx];

	/* Check parameter */
	if ( ConfigPtr->pinPortIdx  >31)
	{
		return PORT_ERR_PARA ;
	}
	/*    if error return PORT_ERR_PARA */
	/**/
	
	/* 1. Internal resistor pull feature selection. */
	switch (ConfigPtr->pullConfig)
  	{
		case PORT_NO_PULL_UP_DOWN:
			{
				regValue &=~ (1u<<1u);			

			}
			break;
		case PORT_PULL_DOWN:
			{
				regValue &=~(1u<<0u);
				regValue |= (1u<<1u);
			}
			break;
		case PORT_PULL_UP:
			{
				regValue |= (1u<<0u);
				regValue |= (1u<<1u);
			}
			break;
	}
	/* 2. Configures the drive strength.*/
	if (ConfigPtr->driveSelect == PORT_LOW_DRV_STRENGTH )
	{
		regValue &= ~1u;
	}
	else
	{
  		regValue |= 1u;
	}
	
	/* 3. mux selection. */	
  	muxing = ConfigPtr->mux;
	regValue |= ((unsigned int)muxing<<8u);
	
	/* 4. Interrupt generation condition. */
	regValue |= ((unsigned int)ConfigPtr->intConfig<<16u);
  	ConfigPtr->base->PCR[ConfigPtr->pinPortIdx] = regValue;
	
	return ret;
	
}
