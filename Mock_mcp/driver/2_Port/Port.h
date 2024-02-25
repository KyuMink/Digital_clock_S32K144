#ifndef PORT_H
#define PORT_H

#include "Port_Registers.h"

typedef enum
{
    PORT_OK        = 0U,  
    PORT_ERR_PARA  = 1U,  /*!< internal pull-down resistor is enabled. */
} Port_ret_t;

typedef enum
{
    PORT_NO_PULL_UP_DOWN         = 0U,  /*!< internal pull-down or pull-up resistor is not enabled.  */
    PORT_PULL_DOWN  			 = 1U,  /*!< internal pull-down resistor is enabled. */
    PORT_PULL_UP    			 = 2U   /*!< internal pull-up resistor is enabled.     */
} Port_pull_config_t;

/* Configures the drive strength.*/
typedef enum
{
    PORT_LOW_DRV_STRENGTH  = 0U,    /*!< low drive strength is configured. */
    PORT_HIGH_DRV_STRENGTH = 1U     /*!< high drive strength is configured. */
} Port_drive_strength_t;

/* Configures the Pin mux selection */
typedef enum
{
    PORT_PIN_DISABLED      = 0U,  /*!< corresponding pin is disabled, but is used as an analog pin       */
    PORT_MUX_AS_GPIO       = 1U,  /*!< corresponding pin is configured as GPIO                           */
    PORT_MUX_ALT2          = 2U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT3          = 3U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT4          = 4U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT5          = 5U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT6          = 6U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT7          = 7U   /*!< chip-specific                                                     */
} Port_mux_t;


/* @brief Configures the interrupt generation condition. */
typedef enum
{
    PORT_DMA_INT_DISABLED  = 0x0U,  /*!< Interrupt/DMA request is disabled.                   */
    PORT_DMA_RISING_EDGE   = 0x1U,  /*!< DMA request on rising edge.                          */
    PORT_DMA_FALLING_EDGE  = 0x2U,  /*!< DMA request on falling edge.                         */
    PORT_DMA_EITHER_EDGE   = 0x3U,  /*!< DMA request on either edge.                          */
    PORT_INT_LOGIC_ZERO    = 0x8U,  /*!< Interrupt when logic 0.                              */
    PORT_INT_RISING_EDGE   = 0x9U,  /*!< Interrupt on rising edge.                            */
    PORT_INT_FALLING_EDGE  = 0xAU,  /*!< Interrupt on falling edge.                           */
    PORT_INT_EITHER_EDGE   = 0xBU,  /*!< Interrupt on either edge.                            */
    PORT_INT_LOGIC_ONE     = 0xCU   /*!< Interrupt when logic 1.                              */
} Port_interrupt_config_t;

typedef struct
{
    PORT_Type         *      base;          /*!< Port base pointer.                           */
    unsigned int             pinPortIdx;    /*!< Port pin number.                             */
    Port_pull_config_t       pullConfig;    /*!< 1. Internal resistor pull feature selection. */
    Port_drive_strength_t    driveSelect;   /*!< 2. Configures the drive strength.     			  */
    Port_mux_t               mux;           /*!< 3. mux selection.      											*/
    Port_interrupt_config_t  intConfig;     /*!< 4. Interrupt generation condition.           */
} Port_ConfigType;

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
Port_ret_t Port_Init(const Port_ConfigType* ConfigPtr);

#endif 
