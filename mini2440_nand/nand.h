#ifndef NAND_K9F2G08U0C_H
#define NAND_K9F2G08U0C_H

#if defined(__cplusplus)
extern "C" {
#endif

void s3c2440_nand_controller_init(void);

void nand_flash_read_id(void);

#if defined(__cplusplus)
}
#endif

#endif // NAND_K9F2G08U0C_H
