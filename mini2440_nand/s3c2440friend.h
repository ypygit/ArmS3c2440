#ifndef _S3C2440_FRIENDLY_H
#define _S3C2440_FRIENDLY_H

#include <stdint.h>

#define _MMIO8_ADDR(addr) (*(volatile unsigned char *)(addr))
#define _MMIO32_ADDR(addr) (*(volatile unsigned int *)(addr))

// GPIO @{
/** H */
#define GPHCON _MMIO32_ADDR(0x56000070)
#define GPHDAT _MMIO32_ADDR(0x56000074)
#define GPHUP  _MMIO32_ADDR(0x56000078)
//@}

// UART @{
/** 0 */
#define ULCON0      _MMIO32_ADDR(0x50000000)
#define UCON_0      _MMIO32_ADDR(0x50000004)
#define UBRDIV0     _MMIO32_ADDR(0x50000028)
#define UTRSTAT0    _MMIO32_ADDR(0x50000010)
#define UTXH0       _MMIO8_ADDR(0x50000020)
#define URXH0       _MMIO8_ADDR(0x50000024)
// @}

// memory controller @{
/** sdram */
#define BWSCON      _MMIO32_ADDR(0x48000000)
#define BANKCON6    _MMIO32_ADDR(0x4800001C)
#define BANKCON7    _MMIO32_ADDR(0x48000020)
#define SDRAMREFR   _MMIO32_ADDR(0x48000024)
#define BANKSIZE    _MMIO32_ADDR(0x48000028)
#define BKMODSET_6  _MMIO32_ADDR(0x4800002C)
#define BKMODSET_7  _MMIO32_ADDR(0x48000030)
//@}

// NAND FLASH CONTROLLER @{
#define NFCONF _MMIO32_ADDR(0x4E000000)
#define NFCONT _MMIO32_ADDR(0x4E000004)
#define NFCMMD _MMIO8_ADDR(0x4E000008)
#define NFADDR _MMIO8_ADDR(0x4E00000C)
#define NFDATA _MMIO8_ADDR(0x4E000010)
// @}

#endif
