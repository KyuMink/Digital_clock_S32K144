#ifndef NVIC_REG_H
#define NVIC_REG_H

typedef struct {
    volatile unsigned int ISER[8];
    volatile unsigned int REV0[24];
    volatile unsigned int ICER[8];
    volatile unsigned int REV1[24];
    volatile unsigned int ISPR[8];
    volatile unsigned int REV2[24];
    volatile unsigned int ICPR[8];
    volatile unsigned int REV3[24];
    volatile unsigned int IABR[8];
    volatile unsigned int REV4[56];
    volatile unsigned int IPR[60]; 
} NVIC_Type;

/** Peripheral S32_NVIC base address */
#define NVIC_BASE_ADDRESS                    (0xE000E100u)

/** Peripheral S32_NVIC base pointer */
#define NVIC                                 ((NVIC_Type *)NVIC_BASE_ADDRESS)

#endif
