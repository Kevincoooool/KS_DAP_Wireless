/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-02-01 16:22:59
 * @FilePath     : \Simple_TeenyUSB_TX\USER\online.c
 */
/***************************************************************/
#include "DAP_Config.h"
#include "DAP.h"
#include "online.h"

extern tusb_hid_device_t hid_dev;

#if 0
extern tusb_cdc_device_t cdc_dev;
extern uint8_t cdc_buf[32];
static volatile uint8_t USB_RequestFlag; // Request  Buffer Usage Flag

static volatile uint8_t USB_ResponseIdle = 1; // Response Buffer Idle  Flag
static volatile uint8_t USB_ResponseFlag;	  // Response Buffer Usage Flag
uint16_t USB_In_queue_in;					  // Request  Index In
uint16_t USB_In_queue_out;					  // Request  Index Out

uint16_t USB_Out_queue_in;									 // Response Index In
uint16_t USB_Out_queue_out;									 // Response Index Out
uint8_t USB_Request[DAP_PACKET_COUNT][DAP_PACKET_SIZE + 1];	 // Request  Buffer
uint8_t USB_Response[DAP_PACKET_COUNT][DAP_PACKET_SIZE + 1]; // Response Buffer
uint8_t usbd_hid_process(void)
{
	uint32_t n;

	// Process pending requests
	//如果收到的数据包页数不等于
	if ((USB_In_queue_out != USB_In_queue_in) || USB_RequestFlag)
	{
		DAP_ProcessCommand(USB_Request[USB_In_queue_out], USB_Response[USB_Out_queue_in]);

		// Update request index and flag
		// 处理完一帧数据就加一 如果等于最大帧数  置0重新开启下一帧的处理
		n = USB_In_queue_out + 1;
		if (n == DAP_PACKET_COUNT)
			n = 0;
		USB_In_queue_out = n;
		//如果已经处理完了所有页收到的数据  就不需要再进行处理了
		if (USB_In_queue_out == USB_In_queue_in)
			USB_RequestFlag = 0;

		//如果需要回复消息  就把处理完的数据 USB_Response[USB_Out_queue_in] 回复给PC
		if (USB_ResponseIdle)
		{ // Request that data is send back to host
			USB_ResponseIdle = 0;

			//USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,USB_Response[USB_Out_queue_in],DAP_PACKET_SIZE);
			tusb_hid_device_send(&hid_dev, USB_Response[USB_Out_queue_out], DAP_PACKET_SIZE);
		}
		//不需要回复 因为接收数据包USB_Out_queue_in 页数没有用完
		else
		{ // 更新输入数据的页数USB_Out_queue_in
			n = USB_Out_queue_in + 1;
			if (n == DAP_PACKET_COUNT)
				n = 0;
			USB_Out_queue_in = n;
			//如果当前处理完的数据包的页数等于
			if (USB_Out_queue_in == USB_Out_queue_out)
				USB_ResponseFlag = 1;
		}
		cdc_buf[0] = USB_In_queue_in;
		cdc_buf[1] = USB_In_queue_out;
		cdc_buf[2] = USB_Out_queue_in;
		cdc_buf[3] = USB_Out_queue_out;
		cdc_buf[4] = 0x22;
		tusb_cdc_device_send(&cdc_dev, cdc_buf, 5);
		return 1;
	}
	return 0;
}

void HID_GetOutReport(uint8_t *EpBuf, uint32_t len)
{
	//如果收到的数据包的第一个数据等于传输终止标志   就直接退出
	if (EpBuf[0] == ID_DAP_TransferAbort)
	{
		DAP_TransferAbort = 1;
		return;
	}
	//如果当前正在回复数据并且接收数据包装满了   直接退出  不再接收数据
	if (USB_RequestFlag && (USB_In_queue_in == USB_In_queue_out))
		return; // Discard packet when buffer is full

	// 把USB HID获取到的数据放入接收数据包中
	memcpy(USB_Request[USB_In_queue_in], EpBuf, len);
	// 更新接收到的数据包页数  等于最大或等于
	USB_In_queue_in++;
	if (USB_In_queue_in == DAP_PACKET_COUNT)
		USB_In_queue_in = 0;
	if (USB_In_queue_in == USB_In_queue_out)
		USB_RequestFlag = 1;
	cdc_buf[0] = USB_In_queue_in;
	cdc_buf[1] = USB_In_queue_out;
	cdc_buf[2] = USB_Out_queue_in;
	cdc_buf[3] = USB_Out_queue_out;
	cdc_buf[4] = 0x11;
	tusb_cdc_device_send(&cdc_dev, cdc_buf, 5);
}

/*
发送完成进入



*/
void HID_SetInReport(void)
{
	//如果当前回复的数据包的页数不等于处理完的数据包的页数  或者需要回复 就更新回复页数
	if ((USB_Out_queue_out != USB_Out_queue_in) || USB_ResponseFlag)
	{

		//更新当前回复的数据包的页数  如果等于最大或者等于处理完的  就重置
		USB_Out_queue_out++;
		if (USB_Out_queue_out == DAP_PACKET_COUNT)
			USB_Out_queue_out = 0;
		if (USB_Out_queue_out == USB_Out_queue_in)
			USB_ResponseFlag = 0;
		cdc_buf[0] = USB_In_queue_in;
		cdc_buf[1] = USB_In_queue_out;
		cdc_buf[2] = USB_Out_queue_in;
		cdc_buf[3] = USB_Out_queue_out;
		cdc_buf[4] = 0x55;
		tusb_cdc_device_send(&cdc_dev, cdc_buf, 5);
	}
	else //如果等于就需要回复
	{
		USB_ResponseIdle = 1;
		cdc_buf[0] = USB_In_queue_in;
		cdc_buf[1] = USB_In_queue_out;
		cdc_buf[2] = USB_Out_queue_in;
		cdc_buf[3] = USB_Out_queue_out;
		cdc_buf[4] = 0x33;
		tusb_cdc_device_send(&cdc_dev, cdc_buf, 5);
	}
}

#else
uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];	 // Request  Buffer
uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer
uint8_t dealing_data = 0;
extern int hid_len;
uint8_t usbd_hid_process_online(void)
{

	//如果需要收数据
	if (dealing_data)
	{
		DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
		tusb_hid_device_send(&hid_dev, MYUSB_Response, DAP_PACKET_SIZE);
		dealing_data = 0;
		return 1;
	}

	return 0;
}
/****************************************************************
 * 获取USB HID数据
 ***************************************************************/

void HID_GetOutReport(uint8_t *EpBuf, uint32_t len)
{
	//如果收到的数据包的第一个数据等于传输终止标志   就直接退出
	if (EpBuf[0] == ID_DAP_TransferAbort)
	{
		DAP_TransferAbort = 1;
		return;
	}
	//没有在处理数据过程中才会接收 不然直接退出
	if (dealing_data)
		return; // Discard packet when buffer is full
	memcpy(MYUSB_Request, EpBuf, 64);
	dealing_data = 1;
	hid_len = 64;
}

/*
USB HID发送完成
发送完成进入
*/
void HID_SetInReport(void)
{
}

#endif
