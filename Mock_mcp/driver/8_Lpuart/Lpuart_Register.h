#ifndef LPUART_REG_H
#define LPUART_REG_H

#define LPUART_BAUD_OSR_SHIFT                    (24u)
#define LPUART_CTRL_RE_SHIFT                     (18u)
#define LPUART_CTRL_M_SHIFT                      (4u)
#define LPUART_CTRL_PE_SHIFT                     (1u)

#define LPUART_CTRL_RIE_SHIFT                    (21u)
#define LPUART_BAUD_SBNS_SHIFT                   (13u)
#define LPUART_STAT_TDRE_SHIFT                   (23u) 
#define LPUART_STAT_RDRF_SHIFT                   (21u) 

/** LPUART - Register Layout Typedef */
typedef struct {
  volatile const  unsigned int VERID;                      /**< Version ID Register, offset: 0x0 */
  volatile const  unsigned int PARAM;                      /**< Parameter Register, offset: 0x4 */
  volatile unsigned int GLOBAL;                            /**< LPUART Global Register, offset: 0x8 */
  volatile unsigned int PINCFG;                            /**< LPUART Pin Configuration Register, offset: 0xC */
  volatile unsigned int BAUD;                              /**< LPUART Baud Rate Register, offset: 0x10 */
  volatile unsigned int STAT;                              /**< LPUART Status Register, offset: 0x14 */
  volatile unsigned int CTRL;                              /**< LPUART Control Register, offset: 0x18 */
  volatile unsigned int DATA;                              /**< LPUART Data Register, offset: 0x1C */
  volatile unsigned int MATCH;                             /**< LPUART Match Address Register, offset: 0x20 */
  volatile unsigned int MODIR;                             /**< LPUART Modem IrDA Register, offset: 0x24 */
  volatile unsigned int FIFO;                              /**< LPUART FIFO Register, offset: 0x28 */
  volatile unsigned int WATER;                             /**< LPUART Watermark Register, offset: 0x2C */
} LPUART_Type;

/** Peripheral LPUART1 base address */
#define LPUART0_BASE                             (0x4006A000u)
#define LPUART1_BASE                             (0x4006B000u)
#define LPUART2_BASE                             (0x4006C000u)
/** Peripheral LPUART1 base pointer */
#define LPUART0                                  ((LPUART_Type *)LPUART0_BASE)
#define LPUART1                                  ((LPUART_Type *)LPUART1_BASE)
#define LPUART2                                  ((LPUART_Type *)LPUART2_BASE)

#endif

