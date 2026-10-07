#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_ARM920T      1   /* This is an ARM920T core  */
#define CONFIG_S3C2400      1   /* in a SAMSUNG S3C2400 SoC */
// [TODO] #define CONFIG_SMDK2400     1   /* on an SAMSUNG SMDK2400 Board */

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ 12000000 /* SMDK2400 has 12 MHz input clock */

#endif
