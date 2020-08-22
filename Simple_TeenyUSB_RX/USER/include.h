/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-20 11:51:46
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:42:28
 * @FilePath: \Simple_TeenyUSB\USER\include.h
 */
#ifndef _INCLUDE_H
#define _INCLUDE_H

#define ONLINE          0
#define WIRELESS_TX     0
#define WIRELESS_RX     1
#define OFFLINE         0
#include "bsp_nrf2401.h"
#include "bsp_spi.h"
#include "wireless_rx.h"
#include "wireless_tx.h"
#include "online.h"
#include "offline.h"

void Delay20ms(void);
#endif


