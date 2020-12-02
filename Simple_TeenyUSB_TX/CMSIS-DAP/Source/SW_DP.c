/******************************************************************************
 * @file     SW_DP.c
 * @brief    CMSIS-DAP SW DP I/O
 * @version  V1.10
 * @date     20. May 2015
 *
 * @note
 * Copyright (C) 2012-2015 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include "DAP_config.h"
#include "DAP.h"
extern SPI_HandleTypeDef hspi1;

// SW Macros

#define PIN_SWCLK_SET PIN_SWCLK_TCK_SET
#define PIN_SWCLK_CLR PIN_SWCLK_TCK_CLR

#define SW_CLOCK_CYCLE() \
	PIN_SWCLK_CLR();     \
	PIN_SWCLK_SET();

//#define SW_WRITE_BIT(bit) \
//	PIN_SWDIO_OUT(bit);   \
//	PIN_SWCLK_CLR();      \
//	PIN_SWCLK_SET();
#define SW_WRITE_BIT(bit)               \
	if (bit & 1)                \
            {                           \
                GPIOB->BSRR = GPIO_PIN_9 + (GPIO_PIN_10 << 16U); \
                PIN_SWCLK_SET();     \
            } \
            else \
            { \
                GPIOB->BSRR = (GPIO_PIN_9 + GPIO_PIN_10) << 16U; \
                PIN_SWCLK_SET(); \
            }

#define SW_READ_BIT(bit)  \
	PIN_SWCLK_CLR();      \
	bit = PIN_SWDIO_IN(); \
	PIN_SWCLK_SET();

// #define PIN_DELAY() PIN_DELAY_SLOW(DAP_Data.clock_delay)
#define PIN_DELAY() PIN_DELAY_FAST()
// Generate SWJ Sequence
//   count:  sequence bit count
//   data:   pointer to sequence bit data
//   return: none
#if SWD_SPI
unsigned int reverse(register unsigned int x)
{
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	return ((x >> 16) | (x << 16));
}

const uint8_t BitReverseTable256[] =
	{
		0X00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
		0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
		0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
		0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
		0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
		0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
		0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
		0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
		0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
		0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
		0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
		0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
		0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
		0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
		0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
		0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF};

static const uint8_t ParityTable256[256] =
	{
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n), P2(n ^ 1), P2(n ^ 1), P2(n)
#define P6(n) P4(n), P4(n ^ 1), P4(n ^ 1), P4(n)
		P6(0), P6(1), P6(1), P6(0)};

void uint16_t_to_uint8_t(uint16_t Buff, uint8_t *Data)
{
	Data[0] = (Buff >> 8) & 0xFF;
	Data[1] = Buff & 0xFF;
}

#define RST_CLOCK_CYCLE() \
	PIN_SWCLK_CLR();      \
	PIN_SWCLK_SET();

#define RST_WRITE_BIT(bit) \
	PIN_SWDIO_OUT(bit);    \
	PIN_SWCLK_CLR();       \
	PIN_SWCLK_SET();

#define RST_READ_BIT(bit) \
	PIN_SWCLK_CLR();      \
	bit = PIN_SWDIO_IN(); \
	PIN_SWCLK_SET();

uint8_t RST_Transfer(uint32_t request, uint32_t data)
{
	uint32_t ack;
	uint32_t bit;
	uint32_t val;
	uint32_t parity;
	uint32_t n;

	/* Packet Request */
	parity = 0U;
	RST_WRITE_BIT(1U); /* Start Bit */
	bit = request >> 0;
	RST_WRITE_BIT(bit); /* APnDP Bit */
	parity += bit;
	bit = request >> 1;
	RST_WRITE_BIT(bit); /* RnW Bit */
	parity += bit;
	bit = request >> 2;
	RST_WRITE_BIT(bit); /* A2 Bit */
	parity += bit;
	bit = request >> 3;
	RST_WRITE_BIT(bit); /* A3 Bit */
	parity += bit;
	RST_WRITE_BIT(parity); /* Parity Bit */
	RST_WRITE_BIT(0U);	   /* Stop Bit */
	RST_WRITE_BIT(1U);	   /* Park Bit */

	/* Turnaround */
	PIN_SWDIO_OUT_DISABLE();
	for (n = DAP_Data.swd_conf.turnaround; n; n--)
	{
		RST_CLOCK_CYCLE();
	}

	/* Acknowledge response */
	RST_READ_BIT(bit);
	ack = bit << 0;
	RST_READ_BIT(bit);
	ack |= bit << 1;
	RST_READ_BIT(bit);
	ack |= bit << 2;

	/* Data transfer */ /* Turnaround */
	for (n = DAP_Data.swd_conf.turnaround; n; n--)
	{
		RST_CLOCK_CYCLE();
	}

	/* Write data */
	val = data;
	parity = 0U;
	for (n = 32U; n; n--)
	{
		RST_WRITE_BIT(val); /* Write WDATA[0:31] */
		parity += val;
		val >>= 1;
	}
	RST_WRITE_BIT(parity); /* Write Parity Bit */

	PIN_SWDIO_OUT(1U);
	return ((uint8_t)ack);
}

void vResetTarget(uint8_t bit)
{
	uint32_t i;
	//soft-reset for Cortex-M
	RST_Transfer(0x00000CC5, 0xE000ED0C); //set AIRCR address
	for (i = 0; i < 100; i++)
		;
	RST_Transfer(0x00000CDD, 0x05FA0007); //set RESET data
	for (i = 0; i < 100; i++)
		;
	RST_Transfer(0x00000CC5, 0xE000ED0C); //repeat
	for (i = 0; i < 100; i++)
		;
	RST_Transfer(0x00000CDD, 0x05FA0007);

	if (bit & 1)
		PIN_nRESET_HIGH();
	else
		PIN_nRESET_LOW();
}
#endif
// Generate SWJ Sequence
//   count:  sequence bit count
//   data:   pointer to sequence bit data
//   return: none
#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
void SWJ_Sequence(uint32_t count, const uint8_t *data)
{
#if !SWD_SPI
	uint32_t val;
	uint32_t n;

	val = 0U;
	n = 0U;
	while (count--)
	{
		if (n == 0U)
		{
			val = *data++;
			n = 8U;
		}
		if (val & 1U)
		{
			PIN_SWDIO_TMS_SET();
		}
		else
		{
			PIN_SWDIO_TMS_CLR();
		}
		SW_CLOCK_CYCLE();
		val >>= 1;
		n--;
	}
#else
	uint8_t Data_Buff[2] = {0x00, 0x00};

	if (count >= 8)
		Data_Buff[0] = data[0];
	if (count == 16)
		Data_Buff[1] = data[1];

	if (count == 8)
		SPI_RW_1(Data_Buff[0]);
	else if (count == 16)
		SPI_TX2(Data_Buff);
	else
	{
	}
	//printf("SWJ_Sequence Fault SPI\r\n");
#endif
}
#endif

// Generate SWD Sequence
//   info:   sequence information
//   swdo:   pointer to SWDIO generated data
//   swdi:   pointer to SWDIO captured data
//   return: none
#if (DAP_SWD != 0)
void SWD_Sequence(uint32_t info, const uint8_t *swdo, uint8_t *swdi)
{
	uint32_t val;
	uint32_t bit;
	uint32_t n, k;

	n = info & SWD_SEQUENCE_CLK;
	if (n == 0U)
	{
		n = 64U;
	}

	if (info & SWD_SEQUENCE_DIN)
	{
		while (n)
		{
			val = 0U;
			for (k = 8U; k && n; k--, n--)
			{
				SW_READ_BIT(bit);
				val >>= 1;
				val |= bit << 7;
			}
			val >>= k;
			*swdi++ = (uint8_t)val;
		}
	}
	else
	{
		while (n)
		{
			val = *swdo++;
			for (k = 8U; k && n; k--, n--)
			{
				SW_WRITE_BIT(val);
				val >>= 1;
			}
		}
	}
}
#endif
#if (DAP_SWD != 0)

#if SWD_SPI
uint8_t SWD_Transfer_Buff(uint32_t request, uint32_t *data)
{
	uint8_t ack = 0;
	uint32_t bit;
	uint32_t val;
	uint32_t parity = 0U;
	uint8_t req_buf = 0U;
	uint8_t Start[8];
	uint32_t n;
	uint8_t vall[5];
	uint8_t val_TX[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	uint32_t val_buf;
	/* Packet Request */

	SPI_Switch(1);
	parity = 0U;
	Start[0] = 1U;
	bit = request >> 0;
	Start[1] = bit & 0x01;
	parity += bit;
	bit = request >> 1;
	Start[2] = bit & 0x01;
	parity += bit;
	bit = request >> 2;
	Start[3] = bit & 0x01;
	parity += bit;
	bit = request >> 3;
	Start[4] = bit & 0x01;
	parity += bit;
	Start[5] = parity & 0x01;
	Start[6] = 0U;
	Start[7] = 1U;

	req_buf = (Start[0] << 0) | (Start[1] << 1) | (Start[2] << 2) | (Start[3] << 3) | (Start[4] << 4) | (Start[5] << 5) | (Start[6] << 6) | (Start[7] << 7);
	SPI_RW_1(req_buf);
	SPI_Switch(0);

	/* Turnaround */
	for (n = DAP_Data.swd_conf.turnaround; n; n--)
	{
		SW_CLOCK_CYCLE();
	}

	/* Acknowledge response */
	SW_READ_BIT(bit);
	ack = bit << 0;
	SW_READ_BIT(bit);
	ack |= bit << 1;
	SW_READ_BIT(bit);
	ack |= bit << 2;

	if (ack == DAP_TRANSFER_OK)
	{ /* OK response */
		/* Data transfer */
		if (request & DAP_TRANSFER_RnW)
		{
			SPI_Switch(1);
			/* Read data */
			val = 0U;
			parity = 0U;

			SPI_TXRX(val_TX, vall, 4);
			val = vall[0] << 0 | vall[1] << 8 | vall[2] << 16 | vall[3] << 24;
			val_buf ^= val_buf >> 16;
			val_buf ^= val_buf >> 8;
			parity = ParityTable256[val_buf & 0xff] & 0x01;

			SPI_Switch(0);
			SW_READ_BIT(bit);
			//      if ((parity ^ bit) & 1U)
			//			{
			//        ack = DAP_TRANSFER_ERROR;
			//      }
			if (data)
			{
				*data = (val);
			}
			/* Turnaround */

			val = 0U;
			parity = 0U;
			for (n = DAP_Data.swd_conf.turnaround; n; n--)
			{
				SW_CLOCK_CYCLE();
			}
		}
		else
		{
			/* Turnaround */
			for (n = DAP_Data.swd_conf.turnaround; n; n--)
			{
				SW_CLOCK_CYCLE();
			}
			SPI_Switch(1);
			/* Write data */
			val = *data;
			parity = 0U;

			vall[0] = val & 0xFF;
			vall[1] = val >> 8 & 0xFF;
			vall[2] = val >> 16 & 0xFF;
			vall[3] = val >> 24 & 0xFF;

			val_buf = vall[0] << 0 | vall[1] << 8 | vall[2] << 16 | vall[3] << 24;
			val_buf ^= val_buf >> 16;
			val_buf ^= val_buf >> 8;
			parity = ParityTable256[val_buf & 0xff];

			SPI_TX4(vall); /* Write WDATA[0:31] */
			SPI_Switch(0);
			SW_WRITE_BIT(parity); /* Write Parity Bit */
		}

		/* Idle cycles */
		n = DAP_Data.transfer.idle_cycles;
		if (n)
		{
			PIN_SWDIO_OUT(0U);
			for (; n; n--)
			{
				SW_CLOCK_CYCLE();
			}
		}
		PIN_SWDIO_OUT(1U);
		return ack;
	}

	if ((ack == DAP_TRANSFER_WAIT) || (ack == DAP_TRANSFER_FAULT))
	{
		SPI_Switch(0);
		/* WAIT or FAULT response */
		if (DAP_Data.swd_conf.data_phase && ((request & DAP_TRANSFER_RnW) != 0U))
		{
			for (n = 32U + 1U; n; n--)
			{
				SW_CLOCK_CYCLE(); /* Dummy Read RDATA[0:31] + Parity */
			}
		}
		/* Turnaround */
		for (n = DAP_Data.swd_conf.turnaround; n; n--)
		{
			SW_CLOCK_CYCLE();
		}

		if (DAP_Data.swd_conf.data_phase && ((request & DAP_TRANSFER_RnW) == 0U))
		{
			//printf("(DAP_Data.swd_conf.data_phase && ((request & DAP_TRANSFER_RnW) == 0U))\r\n");
			PIN_SWDIO_OUT(0U);
			for (n = 32U + 1U; n; n--)
			{
				SW_CLOCK_CYCLE(); /* Dummy Write WDATA[0:31] + Parity */
			}
		}
		PIN_SWDIO_OUT(1U);
		return ack;
	}

	/* Protocol error */
	for (n = DAP_Data.swd_conf.turnaround + 32U + 1U; n; n--)
	{
		SW_CLOCK_CYCLE(); /* Back off data phase */
	}

	PIN_SWDIO_OUT(1U);

	return ack;
}

// SWD Transfer I/O
//   request: A[3:2] RnW APnDP
//   data:    DATA[31:0]
//   return:  ACK[2:0]
#define SWD_TransferFunction(speed) /**/                                 \
	static uint8_t SWD_Transfer##speed(uint32_t request, uint32_t *data) \
	{                                                                    \
		SWD_Transfer_Buff(request, data);                                \
		return 1;                                                        \
	}

#undef PIN_DELAY
#define PIN_DELAY() PIN_DELAY_FAST()
SWD_TransferFunction(Fast)

#undef PIN_DELAY
#define PIN_DELAY() PIN_DELAY_SLOW(DAP_Data.clock_delay)
	SWD_TransferFunction(Slow)

	// SWD Transfer I/O
	//   request: A[3:2] RnW APnDP
	//   data:    DATA[31:0]
	//   return:  ACK[2:0]
	uint8_t SWD_Transfer(uint32_t request, uint32_t *data)
{
	return SWD_Transfer_Buff(request, data);
	//	DAP_Data.fast_clock=1;
	//  if (DAP_Data.fast_clock)
	//	{
	//    return SWD_TransferFast(request, data);
	//  }
	//	else
	//	{
	//    return SWD_TransferSlow(request, data);
	//  }
}

#else
#define SEND_32BIT_ONCE_FAST()                           \
	if (val & 1)                                         \
	{                                                    \
		GPIOB->BSRR = GPIO_PIN_9 + (GPIO_PIN_10 << 16U); \
		val >>= 1;                                       \
		PIN_SWCLK_SET();                                 \
	}                                                    \
	else                                                 \
	{                                                    \
		GPIOB->BSRR = (GPIO_PIN_9 + GPIO_PIN_10) << 16U; \
		val >>= 1;                                       \
		PIN_SWCLK_SET();                                 \
	}

static const uint8_t ParityTable256[256] =
	{
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n), P2(n ^ 1), P2(n ^ 1), P2(n)
#define P6(n) P4(n), P4(n ^ 1), P4(n ^ 1), P4(n)
		P6(0), P6(1), P6(1), P6(0)};

uint8_t GetParity(uint32_t data)
{
	uint8_t parity;

	data ^= data >> 16;
	data ^= data >> 8;

	parity = ParityTable256[data & 0xff];

	return parity;
}
// SWD Transfer I/O
//   request: A[3:2] RnW APnDP
//   data:    DATA[31:0]
//   return:  ACK[2:0]
#define SWD_TransferFunction(speed) /**/                                              \
	uint8_t SWD_Transfer##speed(uint32_t request, uint32_t *data)                     \
	{                                                                                 \
		uint32_t ack;                                                                 \
		uint32_t bit;                                                                 \
		uint32_t val;                                                                 \
		uint32_t parity;                                                              \
                                                                                      \
		uint32_t n;                                                                   \
                                                                                      \
		/* Packet Request */                                                          \
		parity = 0U;                                                                  \
		SW_WRITE_BIT(1U); /* Start Bit */                                             \
		bit = request >> 0;                                                           \
		SW_WRITE_BIT(bit); /* APnDP Bit */                                            \
		parity += bit;                                                                \
		bit = request >> 1;                                                           \
		SW_WRITE_BIT(bit); /* RnW Bit */                                              \
		parity += bit;                                                                \
		bit = request >> 2;                                                           \
		SW_WRITE_BIT(bit); /* A2 Bit */                                               \
		parity += bit;                                                                \
		bit = request >> 3;                                                           \
		SW_WRITE_BIT(bit); /* A3 Bit */                                               \
		parity += bit;                                                                \
		SW_WRITE_BIT(parity); /* Parity Bit */                                        \
		SW_WRITE_BIT(0U);	  /* Stop Bit */                                          \
		SW_WRITE_BIT(1U);	  /* Park Bit */                                          \
                                                                                      \
		/* Turnaround */                                                              \
		PIN_SWDIO_OUT_DISABLE();                                                      \
		for (n = DAP_Data.swd_conf.turnaround; n; n--)                                \
		{                                                                             \
			SW_CLOCK_CYCLE();                                                         \
		}                                                                             \
                                                                                      \
		/* Acknowledge response */                                                    \
		SW_READ_BIT(bit);                                                             \
		ack = bit << 0;                                                               \
		SW_READ_BIT(bit);                                                             \
		ack |= bit << 1;                                                              \
		SW_READ_BIT(bit);                                                             \
		ack |= bit << 2;                                                              \
                                                                                      \
		if (ack == DAP_TRANSFER_OK)                                                   \
		{ /* OK response */                                                           \
			/* Data transfer */                                                       \
			if (request & DAP_TRANSFER_RnW)                                           \
			{                                                                         \
				/* Read data */                                                       \
				val = 0U;                                                             \
				parity = 0U;                                                          \
				for (n = 32U; n; n--)                                                 \
				{                                                                     \
					SW_READ_BIT(bit); /* Read RDATA[0:31] */	\
					val >>= 1;                                                        \
					val |= bit << 31;                                                 \
				}                                                                     \
				parity = GetParity(val);\
				SW_READ_BIT(bit); /* Read Parity */                                   \
				if ((parity ^ bit) & 1U)                                              \
				{                                                                     \
					ack = DAP_TRANSFER_ERROR;                                         \
				}                                                                     \
				if (data)                                                             \
				{                                                                     \
					*data = val;                                                      \
				}                                                                     \
				/* Turnaround */                                                      \
				for (n = DAP_Data.swd_conf.turnaround; n; n--)                        \
				{                                                                     \
					SW_CLOCK_CYCLE();                                                 \
				}                                                                     \
				PIN_SWDIO_OUT_ENABLE();                                               \
			}                                                                         \
			else                                                                      \
			{                                                                         \
				/* Turnaround */                                                      \
				for (n = DAP_Data.swd_conf.turnaround; n; n--)                        \
				{                                                                     \
					SW_CLOCK_CYCLE();                                                 \
				}                                                                     \
				PIN_SWDIO_OUT_ENABLE();                                               \
				val = *data;                                                          \
				parity = GetParity(val);                                              \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SEND_32BIT_ONCE_FAST();                                               \
				SW_WRITE_BIT(parity); /* Write Parity Bit */                          \
			}                                                                         \
			/* Idle cycles */                                                         \
			n = DAP_Data.transfer.idle_cycles;                                        \
			if (n)                                                                    \
			{                                                                         \
				PIN_SWDIO_OUT(0U);                                                    \
				for (; n; n--)                                                        \
				{                                                                     \
					SW_CLOCK_CYCLE();                                                 \
				}                                                                     \
			}                                                                         \
			PIN_SWDIO_OUT(1U);                                                        \
			return ((uint8_t)ack);                                                    \
		}                                                                             \
                                                                                      \
		if ((ack == DAP_TRANSFER_WAIT) || (ack == DAP_TRANSFER_FAULT))                \
		{                                                                             \
			/* WAIT or FAULT response */                                              \
			if (DAP_Data.swd_conf.data_phase && ((request & DAP_TRANSFER_RnW) != 0U)) \
			{                                                                         \
				for (n = 32U + 1U; n; n--)                                            \
				{                                                                     \
					SW_CLOCK_CYCLE(); /* Dummy Read RDATA[0:31] + Parity */           \
				}                                                                     \
			}                                                                         \
			/* Turnaround */                                                          \
			for (n = DAP_Data.swd_conf.turnaround; n; n--)                            \
			{                                                                         \
				SW_CLOCK_CYCLE();                                                     \
			}                                                                         \
			PIN_SWDIO_OUT_ENABLE();                                                   \
			if (DAP_Data.swd_conf.data_phase && ((request & DAP_TRANSFER_RnW) == 0U)) \
			{                                                                         \
				PIN_SWDIO_OUT(0U);                                                    \
				for (n = 32U + 1U; n; n--)                                            \
				{                                                                     \
					SW_CLOCK_CYCLE(); /* Dummy Write WDATA[0:31] + Parity */          \
				}                                                                     \
			}                                                                         \
			PIN_SWDIO_OUT(1U);                                                        \
			return ((uint8_t)ack);                                                    \
		}                                                                             \
                                                                                      \
		/* Protocol error */                                                          \
		for (n = DAP_Data.swd_conf.turnaround + 32U + 1U; n; n--)                     \
		{                                                                             \
			SW_CLOCK_CYCLE(); /* Back off data phase */                               \
		}                                                                             \
		PIN_SWDIO_OUT_ENABLE();                                                       \
		PIN_SWDIO_OUT(1U);                                                            \
		return ((uint8_t)ack);                                                        \
	}

#undef PIN_DELAY
#define PIN_DELAY() PIN_DELAY_FAST()
SWD_TransferFunction(Fast);

#undef PIN_DELAY
#define PIN_DELAY() PIN_DELAY_SLOW(DAP_Data.clock_delay)
SWD_TransferFunction(Slow);

// SWD Transfer I/O
//   request: A[3:2] RnW APnDP
//   data:    DATA[31:0]
//   return:  ACK[2:0]
uint8_t SWD_Transfer(uint32_t request, uint32_t *data)
{
	if (DAP_Data.fast_clock)
	{
		return SWD_TransferFast(request, data);
	}
	else
	{
		return SWD_TransferSlow(request, data);
	}
}
#endif

#endif /* (DAP_SWD != 0) */
