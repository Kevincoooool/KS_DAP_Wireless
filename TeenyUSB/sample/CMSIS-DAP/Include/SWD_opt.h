#ifndef __SWD_OPT_H__
#define __SWD_OPT_H__

#include <stdint.h>

#include "error.h"

error_t target_opt_init(void);
error_t target_opt_uninit(void);
error_t target_opt_program_page(uint32_t addr, const uint8_t *buf, uint32_t size);
error_t target_opt_erase_sector(uint32_t addr);
error_t target_opt_erase_chip(void);


#endif // __SWD_OPT_H__
