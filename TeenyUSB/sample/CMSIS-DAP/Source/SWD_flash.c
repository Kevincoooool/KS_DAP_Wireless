/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-22 21:35:49
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 19:21:23
 * @FilePath     : \Simple_TeenyUSB_TX\CMSIS-DAP\Source\SWD_flash.c
 */
/**
 * @file    SWD_flash.c
 * @brief   通过SWD协议对MCU的FLASH编程
 */
#include "swd_host.h"
#include "SWD_flash.h"
//#include "../algo/STM32F10x_OPT.c"
uint32_t Flash_Page_Size = 1024;
extern uint8_t Select_algo;
error_t target_flash_init(uint32_t flash_start)
{
    if (0 == swd_set_target_state_hw(RESET_PROGRAM))
    {
        return ERROR_RESET;
    }

    // 下载编程算法到目标MCU的SRAM，并初始化
    if (0 == swd_write_memory(STM32_ALGO[Select_algo].algo.algo_start, (uint8_t *)STM32_ALGO[Select_algo].algo.algo_blob, STM32_ALGO[Select_algo].algo.algo_size))
    {
        return ERROR_ALGO_DL;
    }

    if (0 == swd_flash_syscall_exec(&STM32_ALGO[Select_algo].algo.sys_call_s, STM32_ALGO[Select_algo].algo.init, flash_start, 0, 0, 0))
    {
        return ERROR_INIT;
    }

    return ERROR_SUCCESS;
}

error_t target_flash_uninit(void)
{
    swd_set_target_state_hw(RESET_RUN);

    swd_off();
    return ERROR_SUCCESS;
}

error_t target_flash_program_page(uint32_t addr, const uint8_t *buf, uint32_t size)
{
    while (size > 0)
    {
        uint32_t write_size = size > STM32_ALGO[Select_algo].algo.program_buffer_size ? STM32_ALGO[Select_algo].algo.program_buffer_size : size;

        // Write page to buffer
        if (!swd_write_memory(STM32_ALGO[Select_algo].algo.program_buffer, (uint8_t *)buf, write_size))
        {
            return ERROR_ALGO_DATA_SEQ;
        }

        // Run flash programming
        if (!swd_flash_syscall_exec(&STM32_ALGO[Select_algo].algo.sys_call_s,
                                    STM32_ALGO[Select_algo].algo.program_page,
                                    addr,
                                    STM32_ALGO[Select_algo].algo.program_buffer_size,
                                    STM32_ALGO[Select_algo].algo.program_buffer,
                                    0))
        {
            return ERROR_WRITE;
        }

        addr += write_size;
        buf += write_size;
        size -= write_size;
    }

    return ERROR_SUCCESS;
}

error_t target_flash_erase_sector(uint32_t addr)
{
    if (0 == swd_flash_syscall_exec(&STM32_ALGO[Select_algo].algo.sys_call_s, STM32_ALGO[Select_algo].algo.erase_sector, addr, 0, 0, 0))
    {
        return ERROR_ERASE_SECTOR;
    }

    return ERROR_SUCCESS;
}

error_t target_flash_erase_chip(void)
{
    error_t status = ERROR_SUCCESS;

    if (0 == swd_flash_syscall_exec(&STM32_ALGO[Select_algo].algo.sys_call_s, STM32_ALGO[Select_algo].algo.erase_chip, 0, 0, 0, 0))
    {
        return ERROR_ERASE_ALL;
    }
	
    return status;
}
