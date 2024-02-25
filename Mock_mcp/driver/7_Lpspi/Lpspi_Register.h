#ifndef LPSPI_REG_H
#define LPSPI_REG_H

#define LPSPI_TCR_CPOL_SHIFT (31u)
#define LPSPI_TCR_CPHA_SHIFT (30u)
#define LPSPI_TCR_PRESCALE_SHIFT (27u)
#define LPSPI_TCR_LSBF_SHIFT (23u)
#define LPSPI_TCR_PCS_SHIFT (24u)
/** LPSPI - Register Layout Typedef */
typedef struct
{
     volatile const unsigned int VERID;                /**< Version ID Register, offset: 0x0 */
     volatile const unsigned int PARAM;                /**< Parameter Register, offset: 0x4 */
     unsigned char RESERVED_0[8];  
     volatile unsigned int CR;                         /**< Control Register, offset: 0x10 */
     volatile unsigned int SR;                         /**< Status Register, offset: 0x14 */
     volatile unsigned int IER;                        /**< Interrupt Enable Register, offset: 0x18 */
     volatile unsigned int DER;                        /**< DMA Enable Register, offset: 0x1C */
     volatile unsigned int CFGR0;                      /**< Configuration Register 0, offset: 0x20 */
     volatile unsigned int CFGR1;                      /**< Configuration Register 1, offset: 0x24 */
     unsigned char RESERVED_1[8];
     volatile unsigned int DMR0;                       /**< Data Match Register 0, offset: 0x30 */
     volatile unsigned int DMR1;                       /**< Data Match Register 1, offset: 0x34 */
     unsigned char RESERVED_2[8];
     volatile unsigned int CCR;                        /**< Clock Configuration Register, offset: 0x40 */
     unsigned char RESERVED_3[20];
     volatile unsigned int FCR;                        /**< FIFO Control Register, offset: 0x58 */
     volatile const unsigned int FSR;                  /**< FIFO Status Register, offset: 0x5C */
     volatile unsigned int TCR;                        /**< Transmit Command Register, offset: 0x60 */
     volatile unsigned int TDR;                        /**< Transmit Data Register, offset: 0x64 */
     unsigned char RESERVED_4[8];
     volatile const unsigned int RSR;                  /**< Receive Status Register, offset: 0x70 */
     volatile const unsigned int RDR;                  /**< Receive Data Register, offset: 0x74 */
} LPSPI_Type;
/** Peripheral LPSPI base address */

#define LPSPI0_base_address (0x4002C000u)
#define LPSPI1_base_address (0x4002D000u)
#define LPSPI2_base_address (0x4002E000u)


#define LPSPI0 ((LPSPI_Type *) LPSPI0_base_address)
#define LPSPI1 ((LPSPI_Type *) LPSPI1_base_address)
#define LPSPI2 ((LPSPI_Type *) LPSPI2_base_address)

#endif
