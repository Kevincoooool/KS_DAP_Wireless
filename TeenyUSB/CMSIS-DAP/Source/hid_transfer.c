/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-07-22 20:45:48
 * @FilePath: \TeenyUSB\CMSIS-DAP\Source\hid_transfer.c
 */
/***************************************************************/
#include "DAP_Config.h"
#include "DAP_Common.h"
#include "DAP.h"
#include "hid_transfer.h"

#include "teeny_usb.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"

extern tusb_hid_device_t hid_dev;
uint16_t USB_RequestIndexI;      // Request  Index In
uint16_t USB_RequestIndexO;      // Request  Index Out

uint16_t USB_ResponseIndexI;     // Response Index In
uint16_t USB_ResponseIndexO;     // Response Index Out

uint8_t  USB_Request [DAP_PACKET_COUNT][DAP_PACKET_SIZE + 1];  // Request  Buffer
uint8_t  USB_Response[DAP_PACKET_COUNT][DAP_PACKET_SIZE + 1];  // Response Buffer

static volatile uint8_t  USB_RequestFlag;       // Request  Buffer Usage Flag

static volatile uint8_t  USB_ResponseIdle = 1;  // Response Buffer Idle  Flag
static volatile uint8_t  USB_ResponseFlag;      // Response Buffer Usage Flag

uint8_t usbd_hid_process(void)
{
	uint32_t n;

	// Process pending requests
	if((USB_RequestIndexO != USB_RequestIndexI) || USB_RequestFlag)
	{
		DAP_ProcessCommand(USB_Request[USB_RequestIndexO], USB_Response[USB_ResponseIndexI]);

		// Update request index and flag
		n = USB_RequestIndexO + 1;
		if(n == DAP_PACKET_COUNT)
			n = 0;
		USB_RequestIndexO = n;

		if(USB_RequestIndexO == USB_RequestIndexI)
			USB_RequestFlag = 0;

		if(USB_ResponseIdle)
		{	// Request that data is send back to host
			USB_ResponseIdle = 0;
			
			//USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,USB_Response[USB_ResponseIndexI],DAP_PACKET_SIZE);
			tusb_hid_device_send(&hid_dev, USB_Response[USB_ResponseIndexI], DAP_PACKET_SIZE);
		}
		else
		{	// Update response index and flag
			n = USB_ResponseIndexI + 1;
			if (n == DAP_PACKET_COUNT)
				n = 0;
			USB_ResponseIndexI = n;

			if (USB_ResponseIndexI == USB_ResponseIndexO)
				USB_ResponseFlag = 1;
		}
		return 1;
	}
	return 0;
}


void HID_GetOutReport(uint8_t *EpBuf, uint32_t len)
{
    if(EpBuf[0] == ID_DAP_TransferAbort)
	{
		DAP_TransferAbort = 1;
		return;
	}
	
	if(USB_RequestFlag && (USB_RequestIndexI == USB_RequestIndexO))
		return;  // Discard packet when buffer is full

	// Store data into request packet buffer
	memcpy(USB_Request[USB_RequestIndexI], EpBuf, len);

	USB_RequestIndexI++;
	if(USB_RequestIndexI == DAP_PACKET_COUNT)
		USB_RequestIndexI = 0;
	if(USB_RequestIndexI == USB_RequestIndexO)
		USB_RequestFlag = 1;
}


void HID_SetInReport(void)
{
	if((USB_ResponseIndexO != USB_ResponseIndexI) || USB_ResponseFlag)
	{

		//USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,USB_Response[USB_ResponseIndexI],DAP_PACKET_SIZE);
		USB_ResponseIndexO++;
		if (USB_ResponseIndexO == DAP_PACKET_COUNT)
			USB_ResponseIndexO = 0;
		if (USB_ResponseIndexO == USB_ResponseIndexI)
			USB_ResponseFlag = 0;
	}
	else
	{
		USB_ResponseIdle = 1;
	}
}

