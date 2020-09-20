#include "driver/uart.h"
#include "osapi.h"
#include "os_type.h"
#include "ip_addr.h"
#include "eagle_soc.h"
#include "user_config.h"
#include "c_types.h"
#include "ets_sys.h"
#include "mem.h"
#include "gpio.h"
#include "user_interface.h"

#define USE_US_TIMER //要使用函数os_timer_arm_us，需要先定义USE_US_TIMER

os_timer_t os_timer1; //声明一个软件定时器变量
os_timer_t os_timer2; //声明一个软件定时器变量
extern struct espconn user_udp_espconn;
extern struct espconn user_tcp_conn;
uint8 uart_buf[1024] = {0}; //开辟一个串口数据缓存空间

/******************************************************************************
 * 函数名      : UDP发送函数
 * 描述          : 通过UDP通信转发串口接收到的数据
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
extern void send_tcp_server(uint8_t *buf, uint8_t len);
extern void send_tcp_client(uint8_t *buf, uint8_t len);
void ICACHE_FLASH_ATTR
uart_rx()
{

	//------------------------------------------------------------------------------------
	//声明一个变量用来存放接收到的数据长度
	uint32 len = 0;
	//------------------------------------------------------------------------------------
	//计算接收到的数据长度
	len = rx_buff_deq(uart_buf, 1024); //要调用该函数，需要打开串口buff使能宏（driver/uart.h文件第35行）

	//------------------------------------------------------------------------------------
	//判断接收到的数据长度，如果长度不为零，说明接收到了数据，然后进行UDP转发
	if (len != 0)
	{

		GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 0);
		//------------------------------------------------------------------------------------
		//UDP转发
		//    	espconn_sendto(&user_udp_espconn, uart_buf, len);
		//		espconn_send(&user_udp_espconn, uart_buf, len);
		
		//作为TCP CLIENT时调用send_tcp_client
//		send_tcp_client(uart_buf, len);
		//作为TCP SERVER时调用send_tcp_server
		 send_tcp_server(uart_buf, len);
		//------------------------------------------------------------------------------------
		//UDP转发之后清空接收区
		os_memset(uart_buf, 0, 1024);

		//------------------------------------------------------------------------------------
		//每次定时器时间到了之后，给灯的状态取反

		//------------------------------------------------------------------------------------
		//灯的状态取反后，赋值给灯的io口

		GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 1);
	}
}
/******************************************************************************
 * 函数名      : 软件定时器初始化函数
 * 描述          : 初始化软件定时器
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
os_timer1_init(void)
{

	//------------------------------------------------------------------------------------
	//步骤1：关闭定时器
	os_timer_disarm(&os_timer1);

	//------------------------------------------------------------------------------------
	//设置定时器,定时时间到会触发回调函数uart_rx工作
	os_timer_setfn(&os_timer1, (os_timer_func_t *)uart_rx, NULL);

	//------------------------------------------------------------------------------------
	//启动定时器，设置定时间隔为100us
	os_timer_arm_us(&os_timer1, 100, 1);
}
/******************************************************************************
 * 函数名      : 用户指示灯初始化函数
 * 描述          : 初始化用户指示灯
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
user_led_init(void)
{

	//------------------------------------------------------------------------------------
	//管脚功能选择函数
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); //选择管脚2作为GPIO2的功能，led管脚

	//------------------------------------------------------------------------------------
	//管脚输出高低电平
	GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 1); //led管脚默认输出高，灯不亮
}

void user_init() //初始化
{
	//重新初始化定时器
	system_timer_reinit(); //当需要使用微秒定时器时调用
	uart_init(2000000, 2000000);

	// 8266作为UDP服务器，本地和目标端口为8266，IP地址见串口打印
	//	udp_services_init();
	//
	// 8266作为UDP客户端，本地端口为8266，目标端口为8266，IP地址见串口打印
	//	udp_client_init();

	// 8266作为TCP服务器，本地和目标端口为8266，IP地址见串口打印
		tcp_service_init();

	// 8266作为TCP客户端，目标端口为8266，IP地址见串口打印，此要先获取Tcp服务端的ip地址
//	tcp_client_init();

	user_led_init();
	os_timer1_init();
}

void user_rf_pre_init()
{
}
