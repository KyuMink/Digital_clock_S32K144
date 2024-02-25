#ifndef SYSTICK_REG_H
#define SYSTICK_REG_H

#define SYST_COUNTER_EN_SHIFT                   (0u)
#define SYST_INT_EN_SHIFT                       (1u)
#define SYST_CSR_COUNTFLAG_SHIFT                (16u)

#define ENABLE_SYST_INT                         (1u)
#define DISABLE_SYST_INT                        (0u)

#define FIRC_CLOCK                              (48000000)
#define SIRC_CLOCK                              (8000000)
#define SOSC_CLOCK                              (8000000)
#define LPO_CLOCK                               (128000)

#define SYST_CSR				(*(volatile unsigned int*)(0xE000E010))
#define SYST_RVR				(*(volatile unsigned int*)(0xE000E014))
#define SYST_CVR				(*(volatile unsigned int*)(0xE000E018))			
#define SYST_CALIB			(*(volatile unsigned int*)(0xE000E01C))			

#endif

