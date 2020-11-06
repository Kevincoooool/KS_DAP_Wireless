/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:28:59
 * @FilePath: \Simple_TeenyUSB\USER\wireless_tx.c
 */
/***************************************************************/

#include "wireless_tx.h"
#include "DAP_config.h"
extern int hid_len;
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern UART_HandleTypeDef huart1;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];	// Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer

extern uint8_t In_MYUSB_Response[DAP_PACKET_SIZE + 3]; // Request  Buffer
extern uint8_t Out_MYUSB_Request[DAP_PACKET_SIZE + 3]; // Response Buffer

extern uint8_t dealing_data;
uint8_t state_w_tx = wait_hid_data;

uint8_t usbd_hid_process_wireless_tx(void)
{

	/*
    无线发射端流程
    1、USB收到HID的数据
    2、把HID收到的数据通过SPI发出NRF
    3、等待SPI回复这一包数据的回复
    4、收到SPI回复的数据
    5、将SPI收到的数据通过HID发出
    */
	switch (state_w_tx)
	{
	case wait_hid_data:
		if (dealing_data)
		{

			state_w_tx = dap_tx_send;
			//如需要校验则取消注释
			// Out_MYUSB_Request[0] = 0xAA;
			// Out_MYUSB_Request[65] = SumCheck(MYUSB_Request, 64);
			// Out_MYUSB_Request[66] = 0xFB;
			// for (uint8_t i = 1; i < 65; i++)
			// {
			//     Out_MYUSB_Request[i] = MYUSB_Request[i - 1];
			// }
		}
		else
			state_w_tx = wait_hid_data;
		break;
	case dap_tx_send:
		while (HAL_UART_Transmit(&huart1, MYUSB_Request, DAP_PACKET_SIZE, 1000) != HAL_OK)
			;
		memset(MYUSB_Response, 0, DAP_PACKET_SIZE);
		state_w_tx = wait_dap_rx_reply;
		break;
	case wait_dap_rx_reply:

		if (recv_end_flag == 1)
		{
			memcpy(MYUSB_Response, rx_buffer, BUFFER_SIZE);
			//如需要校验则取消注释
			//tusb_cdc_device_send(&cdc_dev, In_MYUSB_Response, BUFFER_SIZE);
			//             for (uint8_t i = 1; i < 65; i++)
			//             {
			//                 MYUSB_Response[i - 1] = In_MYUSB_Response[i];
			//             }
			//             if (In_MYUSB_Response[0] == 0xAA && In_MYUSB_Response[66] == 0xFB && SumCheck(MYUSB_Response, 64) == In_MYUSB_Response[65])
			//             {
			//                 state_w_tx = seng_hid_data;
			//             }
			//             else
			//             {
			// 				tusb_cdc_device_send(&cdc_dev, "ERR", 3);
			// 				state_w_tx = dap_tx_send;
			// //			Delay20ms();
			//             }
			state_w_tx = seng_hid_data;
			rx_len = 0;		   //清除计数
			recv_end_flag = 0; //清除接收结束标志位
		}
		else
			state_w_tx = wait_dap_rx_reply;
		break;

	case seng_hid_data:
		tusb_hid_device_send(&hid_dev, MYUSB_Response, DAP_PACKET_SIZE);
		state_w_tx = wait_hid_data;
		dealing_data = 0;
		HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
		break;
	default:
		break;
	}

	return 0;
}
uint8_t CalcCheck(uint8_t *buffer, uint8_t len)
{
	int i, result;
	for (result = buffer[0], i = 1; i < len; i++)
	{
		result ^= buffer[i];
	}
	return result;
}
uint8_t SumCheck(uint8_t *buffer, uint8_t len)
{
	int i;
	uint8_t sum;
	for (sum = buffer[0], i = 1; i < len; i++)
	{
		sum += buffer[i];
	}
	return sum;
}
