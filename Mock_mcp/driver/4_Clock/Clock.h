#ifndef CLOCK_H
#define CLOCK_H

#include "Clock_Registers.h"

typedef enum {
	SOSC_CLK                     = 1u,       /*!< SOSC clock                     */
	SIRC_CLK                     = 2u,       /*!< SIRC clock                     */
    FIRC_CLK                     = 3u,       /*!< FIRC clock                     */  
    SPLL_CLK                     = 6u,       /*!< SPLL clock                     */
}system_clock_source_t;

typedef enum {
	CORE_CLK_DIV_BY_1     = 0,
	CORE_CLK_DIV_BY_2     = 1,
	CORE_CLK_DIV_BY_3     = 2,
	CORE_CLK_DIV_BY_4     = 3,
	CORE_CLK_DIV_BY_5     = 4,
	CORE_CLK_DIV_BY_6     = 5,
	CORE_CLK_DIV_BY_7     = 6,
	CORE_CLK_DIV_BY_8     = 7,
	CORE_CLK_DIV_BY_9     = 8,
	CORE_CLK_DIV_BY_10    = 9,
	CORE_CLK_DIV_BY_11    = 10,
	CORE_CLK_DIV_BY_12    = 11,
	CORE_CLK_DIV_BY_13    = 12,
	CORE_CLK_DIV_BY_14    = 13,
	CORE_CLK_DIV_BY_15    = 14,
	CORE_CLK_DIV_BY_16    = 15,
}core_clock_divide_ratio_t;

typedef enum {
	BUS_CLK_DIV_BY_1     = 0,
	BUS_CLK_DIV_BY_2     = 1,
	BUS_CLK_DIV_BY_3     = 2,
	BUS_CLK_DIV_BY_4     = 3,
	BUS_CLK_DIV_BY_5     = 4,
	BUS_CLK_DIV_BY_6     = 5,
	BUS_CLK_DIV_BY_7     = 6,
	BUS_CLK_DIV_BY_8     = 7,
	BUS_CLK_DIV_BY_9     = 8,
	BUS_CLK_DIV_BY_10    = 9,
	BUS_CLK_DIV_BY_11    = 10,
	BUS_CLK_DIV_BY_12    = 11,
	BUS_CLK_DIV_BY_13    = 12,
	BUS_CLK_DIV_BY_14    = 13,
	BUS_CLK_DIV_BY_15    = 14,
	BUS_CLK_DIV_BY_16    = 15,
}bus_clock_divide_ratio_t;

typedef enum {
	SLOW_CLK_DIV_BY_1     = 0,
	SLOW_CLK_DIV_BY_2     = 1,
	SLOW_CLK_DIV_BY_3     = 2,
	SLOW_CLK_DIV_BY_4     = 3,
	SLOW_CLK_DIV_BY_5     = 4,
	SLOW_CLK_DIV_BY_6     = 5,
	SLOW_CLK_DIV_BY_7     = 6,
	SLOW_CLK_DIV_BY_8     = 7,
}slow_clock_divide_ratio_t;

typedef enum {

    /* PCC clocks */
		LPIT0_CLK                    = 55u,      /*!< LPIT0 clock source             */
    PORTA_CLK                    = 73u,      /*!< PORTA clock source             */
    PORTB_CLK                    = 74u,      /*!< PORTB clock source             */
    PORTC_CLK                    = 75u,      /*!< PORTC clock source             */
    PORTD_CLK                    = 76u,      /*!< PORTD clock source             */
    PORTE_CLK                    = 77u,      /*!< PORTE clock source             */
    LPSPI0_CLK                   = 44u,      /*!< LPSPI0 clock source            */
    LPSPI1_CLK                   = 45u,      /*!< LPSPI1 clock source            */
    LPSPI2_CLK                   = 46u,      /*!< LPSPI2 clock source            */
    LPUART0_CLK                  = 106u,      /*!< LPUART0 clock source           */
    LPUART1_CLK                  = 107u,      /*!< LPUART1 clock source           */
    LPUART2_CLK                  = 108u,      /*!< LPUART2 clock source           */
} clock_names_t;


typedef enum {
    CLK_SRC_OFF                  = 0u,      /*!< Clock is off             */
    CLK_SRC_OP_1                 = 1u,      /*!< Clock option 1           */
    CLK_SRC_OP_2                 = 2u,      /*!< Clock option 2           */
    CLK_SRC_OP_3                 = 3u,      /*!< Clock option 3           */
    CLK_SRC_OP_4                 = 4u,      /*!< Clock option 4           */
    CLK_SRC_OP_5                 = 5u,      /*!< Clock option 5             */
    CLK_SRC_OP_6                 = 6u,      /*!< Clock option 6            */
    CLK_SRC_OP_7                 = 7u       /*!< Clock option 7            */
} peripheral_clock_source_t;

typedef enum {
	CLK_GATE_DISABLE  = 0u,
	CLK_GATE_ENABLE   = 1u
} clock_gate_t;
	
typedef struct
{
    clock_names_t clockName;               /* The name of the peripheral clock */
    clock_gate_t clkGate;                  /*!< Peripheral clock gate.                     */
    peripheral_clock_source_t clkSrc;      /*!< Peripheral clock source.                   */
} Pcc_ConfigType;


typedef enum
{
    SCG_CLOCK_DISABLE   = 0U,        /*!< Clock output is disabled.  */
    SCG_CLOCK_DIV_BY_1  = 1U,        /*!< Divided by 1.              */
    SCG_CLOCK_DIV_BY_2  = 2U,        /*!< Divided by 2.              */
    SCG_CLOCK_DIV_BY_4  = 3U,        /*!< Divided by 4.              */
    SCG_CLOCK_DIV_BY_8  = 4U,        /*!< Divided by 8.              */
    SCG_CLOCK_DIV_BY_16 = 5U,        /*!< Divided by 16.             */
    SCG_CLOCK_DIV_BY_32 = 6U,        /*!< Divided by 32.             */
    SCG_CLOCK_DIV_BY_64 = 7U         /*!< Divided by 64.             */
} scg_async_clock_div_t;

typedef struct
{
    scg_async_clock_div_t div1;        /*!<  Clock Divide 1           */
    scg_async_clock_div_t div2;        /*!<  Clock Divide 2           */

} Scg_Firc_ConfigType;

typedef struct
{
    scg_async_clock_div_t div1;       /*!<  Clock Divide 1           */
    scg_async_clock_div_t div2;       /*!<  Clock Divide 2           */
} Scg_Sirc_ConfigType;

typedef struct
{
    scg_async_clock_div_t div1;       /*!<  Clock Divide 1           */
    scg_async_clock_div_t div2;       /*!<  Clock Divide 2           */
} Scg_Sosc_ConfigType;

typedef struct
{
    unsigned char  prediv;               /*!< PLL reference clock divider.     */
    unsigned char  mult;                 /*!< System PLL multiplier.           */
    unsigned char  src;                  /*!< System PLL source.               */
    scg_async_clock_div_t div1;          /*!<  Clock Divide 1                  */
    scg_async_clock_div_t div2;          /*!<  Clock Divide 2                  */

} Scg_Spll_ConfigType;

typedef struct
{
    system_clock_source_t      sys_clk_src;
    core_clock_divide_ratio_t  core_div;
	bus_clock_divide_ratio_t   bus_div;
	slow_clock_divide_ratio_t  slow_div;
    scg_async_clock_div_t div1;          /*!<  Clock Divide 1                  */
    scg_async_clock_div_t div2;          /*!<  Clock Divide 2                  */

} Scg_RunMode_ConfigType;

void Clock_SetPccConfig(const Pcc_ConfigType* ConfigPtr);

void Clock_SetScgFircConfig(const Scg_Firc_ConfigType * ConfigPtr);

void Clock_SetScgSircConfig(const Scg_Sirc_ConfigType * ConfigPtr);

void Clock_SetScgSoscConfig(const Scg_Sosc_ConfigType * ConfigPtr);

void Clock_SetScgSpllConfig(const Scg_Spll_ConfigType * ConfigPtr);

void Clock_SetScgRunModeConfig(const Scg_RunMode_ConfigType * ConfigPtr);

#endif
