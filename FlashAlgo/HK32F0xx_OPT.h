#ifndef HK32F0XX_OPT_H
#define HK32F0XX_OPT_H

#include <stdint.h>

typedef struct {
    uint32_t breakpoint;
    uint32_t static_base;
    uint32_t stack_pointer;
} program_syscall_t;

typedef struct {
    const uint32_t  init;
    const uint32_t  uninit;
    const uint32_t  erase_chip;
    const uint32_t  erase_sector;
    const uint32_t  program_page;
    const uint32_t  check_blank;
    //const uint32_t  verify;
    
    const program_syscall_t sys_call_s;
    
    const uint32_t  program_buffer;
    const uint32_t  algo_start;
    const uint32_t  algo_size;
    const uint32_t *algo_blob;
    const uint32_t  program_buffer_size;
} program_target_t;

#endif

