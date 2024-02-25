#ifndef GPIO_H
#define GPIO_H

#include "Gpio_Registers.h"

#define INPUT_MODE 		0
#define OUTPUT_MODE 	1

#define LOW						0
#define HIGH 					1

/*typedef enum
{
	GPIO_LEVEL_LOW = 0,
	GPIO_LEVEL_HIGH = 1,
	
} GPIO_PinLevel_t;
*/

typedef struct
{
    GPIO_Type         *      base;                  /*!< Gpio base pointer.  */
    unsigned char            GPIO_PinNumber;        /*!< Pin number.*/
    unsigned char            GPIO_PinMode;          /*!< Pin_mode */
//   GPIO_PinLevel_t          GPIO_PinLevel;         /*!< Pin_level */
	unsigned char           GPIO_PinLevel;         /*!< Pin_level */
} Gpio_ConfigType;

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] ConfigPtr:  The configuration structure
 * @return 
 */
void Gpio_Init(const Gpio_ConfigType* ConfigPtr);
void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value);
void GPIO_SetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);
void GPIO_ResetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);
void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);
unsigned char GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);
char check_GPIO_parameter(unsigned char PinNumber);


#endif
