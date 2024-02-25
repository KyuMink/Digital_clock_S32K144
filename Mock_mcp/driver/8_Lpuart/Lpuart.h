#include "Lpuart_Register.h"


typedef enum
{
    LPUART_BIT_MODE_8  = 0U,  
    LPUART_BIT_MODE_9  = 1U,   
} lpuart_bit_mode_t;

typedef enum
{
    LPUART_MODE_RX  = 1U,  
    LPUART_MODE_TX  = 2U,
		LPUART_MODE_TX_RX  = 3U,	
} lpuart_mode_t;


typedef enum
{
    LPUART_PARITY_NONE  = 0U,  
    LPUART_PARITY_EVEN  = 1U, 
    LPUART_PARITY_ODD  	= 2U,   
} lpuart_parity_t;

typedef enum
{
    LPUART_STOP_BIT_1  = 0U,  
    LPUART_STOP_BIT_2  = 1U,  
} lpuart_stop_bit_t;

/** 
  * @brief UART Init Structure definition
  */ 
typedef struct
{
	unsigned int F_lpuart;
	
  unsigned int BaudRate;     

  unsigned int OverSampling;	
                                           
  lpuart_bit_mode_t BitMode;                /*!< Specifies the number of data bits transmitted or received in a frame. */

	lpuart_stop_bit_t StopBits;                  /*!< Specifies the number of stop bits transmitted. */
                                          
  lpuart_parity_t Parity;                    /*!< Specifies the parity mode. */

  lpuart_mode_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled. */
             
}LPUART_InitType;

typedef struct
{
  LPUART_Type                 	 *Instance;        	/*!< LPUART registers base address        */

  LPUART_InitType             	 Init;             /*!< UART communication parameters      */

  unsigned char                  *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */

  unsigned short                 TxXferSize;       /*!< UART Tx Transfer size              */

  unsigned short                 TxXferCount;      /*!< UART Tx Transfer Counter           */

  unsigned char                  *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */

  unsigned short                 RxXferSize;       /*!< UART Rx Transfer size              */

  unsigned short                 RxXferCount;      /*!< UART Rx Transfer Counter           */

}Lpuart_ConfigType;

void Lpuart_Init (const Lpuart_ConfigType* ConfigPtr );

void Lpuart_Transmit(LPUART_Type *pLpuart, unsigned char *pTxBuffer, unsigned short Size);

void Lpuart_Receive(LPUART_Type *pLpuart, unsigned char *pRxBuffer, unsigned short Size);

void Lpuart_ReceiveDataIT(Lpuart_ConfigType *ConfigPtr, unsigned char *pRxBuffer, unsigned short Size);

void Lpuart_IRQHandler(Lpuart_ConfigType* ConfigPtr);

void Lpuart_RxCpltCallback(Lpuart_ConfigType* ConfigPtr);

