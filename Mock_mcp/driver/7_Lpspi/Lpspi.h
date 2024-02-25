#include "Lpspi_Register.h"

typedef enum
{
	SPI_CPOL_0 = 0U,
	SPI_CPOL_1 = 1U,
} spi_clock_polarity_t;

typedef enum
{
	SPI_CPHA_0 = 0U,
	SPI_CPHA_1 = 1U
} spi_clock_phase_t;

typedef enum
{
	LPSPI_PCS_0 = 0U,
	LPSPI_PCS_1 = 1U,
	LPSPI_PCS_2 = 2U,
	LPSPI_PCS_3 = 3U
} spi_peripheral_chip_select_t;

typedef enum
{
	LPSPI_FRAME_8 = 7U,
	LPSPI_FRAME_16 = 15U,
	LPSPI_FRAME_32 = 31U,
} spi_frame_size_t;

typedef enum
{
	LPSPI_MSB_FIRST = 0U,
	LPSPI_LSB_FIRST = 1U
} spi_type_transfer_t;

typedef enum
{
	LPSPI_PRE_DIV_BY_1 = 0U,
	LPSPI_PRE_DIV_BY_2 = 1U,
	LPSPI_PRE_DIV_BY_4 = 2U,
	LPSPI_PRE_DIV_BY_8 = 3U,
	LPSPI_PRE_DIV_BY_16 = 4U,
	LPSPI_PRE_DIV_BY_32 = 5U,
	LPSPI_PRE_DIV_BY_64 = 6U,
	LPSPI_PRE_DIV_BY_128 = 7U
} spi_prescaler_t;

typedef struct
{
	unsigned int 						  F_lpspi; /* Clock supply for LPSPI */
	unsigned int 						spi_speed;
	spi_prescaler_t 				spi_prescaler;
	spi_type_transfer_t 			spi_type_tran;
	spi_frame_size_t 					spi_frame;
	spi_clock_polarity_t 				 spi_cpol;
	spi_clock_phase_t 				     spi_cpha;
	spi_peripheral_chip_select_t		  spi_pcs;
} Lpspi_InitType;

typedef struct
{
	LPSPI_Type 							*pSPIx;
	Lpspi_InitType 					  	Init;
	unsigned char 					*pTxBuffer;
	unsigned char 					*pRxBuffer;
	unsigned short 						 TxLen;
	unsigned short 						 RxLen;
} Lpspi_ConfigType;

void Lpspi_Init(const Lpspi_ConfigType *ConfigPtr);

void Lpspi_Transmit(LPSPI_Type *pLpspi, unsigned char *pTxBuffer, unsigned short Size);
char check_LPSPI_parameter(const Lpspi_ConfigType* ConfigPtr );
