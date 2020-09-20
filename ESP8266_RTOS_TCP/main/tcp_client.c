/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/api.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_wifi.h"

/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_WIFI_SSID CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS CONFIG_WIFI_PASSWORD

#ifdef CONFIG_EXAMPLE_IPV4
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR
#else
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV6_ADDR
#endif

#define PORT CONFIG_EXAMPLE_PORT

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0;
const int IPV4_GOTIP_BIT = BIT0;

static const char *TAG = "DAP_TCP_CLIENT";

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    /* Invoke Provisioning event handler first */
    system_event_info_t *info = &event->event_info;

    switch (event->event_id)
    {
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "SoftAP started");
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "SoftAP stopped");
        break;
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, IPV4_GOTIP_BIT);
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR "leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGE(TAG, "Disconnect reason : %d", info->disconnected.reason);
        if (info->disconnected.reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT)
        {
            /*Switch to 802.11 bgn mode */
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCAL_11B | WIFI_PROTOCAL_11G | WIFI_PROTOCAL_11N);
        }
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, IPV4_GOTIP_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}
static void wait_for_ip()
{
    uint32_t bits = IPV4_GOTIP_BIT;
    ESP_LOGI(TAG, "Waiting for AP connection...");
    xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");
}
/*作为客户端 需要连服务器的WIFI*/
static void initialise_wifi_sta(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_WIFI_SSID,
            .password = EXAMPLE_WIFI_PASS,
        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    wait_for_ip();
}
/*作为服务器 需要设置一个热点来让客户端连接*/
static void initialise_wifi_ap(void)
{

    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_WIFI_SSID),
            .password = EXAMPLE_WIFI_PASS,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK},
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.ap.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s",
             wifi_config.ap.ssid, wifi_config.ap.password);
}

#define BUF_SIZE 1024
/*搞个全局变量来作为串口发送的接口*/
static int newconn;
static void tcp_client_task(void *pvParameters)
{
    char rx_buffer[1024];
    char addr_str[128];
    int addr_family;
    int ip_protocol;

    while (1)
    {

        struct sockaddr_in destAddr;
        destAddr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        destAddr.sin_family = AF_INET;
        destAddr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
        inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);
        while (1)
        {
            /*先创建一个socket*/
            int sock = socket(addr_family, SOCK_STREAM, ip_protocol);
            if (sock < 0)
            {
                ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
                break;
            }
            ESP_LOGI(TAG, "Socket created");
            /*连接到服务器的地址和端口*/
            int err = connect(sock, (struct sockaddr *)&destAddr, sizeof(destAddr));
            if (err != 0)
            {
                ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
            }
            ESP_LOGI(TAG, "Successfully connected");
            newconn = sock;
            while (1)
            {
                /*阻塞接收服务器传来的数据*/
                int len = recv(newconn, rx_buffer, sizeof(rx_buffer) - 1, 0);
                // Error occured during receiving
                if (len < 0)
                {
                    ESP_LOGE(TAG, "recv failed: errno %d", errno);
                    break;
                }
                // Data received
                else
                {
                    /*收到数据后串口转发*/
                    gpio_set_level(GPIO_NUM_2, 0);
                    rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                    //ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
                    //ESP_LOGI(TAG, "%s", rx_buffer);
                    uart_write_bytes(UART_NUM_0, rx_buffer, len);
                    gpio_set_level(GPIO_NUM_2, 1);
                }

                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            if (newconn != -1)
            {
                ESP_LOGE(TAG, "Shutting down socket and restarting...");
                shutdown(sock, 0);
                close(sock);
            }
        }
    }
    vTaskDelete(NULL);
}
static void tcp_server_task(void *pvParameters)
{
    char rx_buffer[1024]={0};
    char addr_str[128];
    int addr_family;
    int ip_protocol;
    struct sockaddr_in destAddr;
    destAddr.sin_addr.s_addr = htonl(IPADDR_ANY);
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);

    while (1)
    {
        int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        if (listen_sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created");

        int err = bind(listen_sock, (struct sockaddr *)&destAddr, sizeof(destAddr));
        if (err != 0)
        {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket binded");

        err = listen(listen_sock, 1);
        if (err != 0)
        {
            ESP_LOGE(TAG, "Error occured during listen: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket listening");
        struct sockaddr_in sourceAddr;
        uint addrLen = sizeof(sourceAddr);
        int sock = accept(listen_sock, (struct sockaddr *)&sourceAddr, &addrLen);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket accepted");
        gpio_set_level(GPIO_NUM_2, 0);
        newconn = sock;
        while (1)
        {
            int len = recv(newconn, rx_buffer, sizeof(rx_buffer) - 1, 0);
            // Error occured during receiving
            if (len < 0)
            {
                // ESP_LOGE(TAG, "recv failed: errno %d", errno);
                break;
            }
            // Connection closed
            else if (len == 0)
            {
                // ESP_LOGI(TAG, "Connection closed");
                break;
            }
            // Data received
            else
            {
                gpio_set_level(GPIO_NUM_2, 0);
                inet_ntoa_r(((struct sockaddr_in *)&sourceAddr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                // ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
                // ESP_LOGI(TAG, "%s", rx_buffer);
                uart_write_bytes(UART_NUM_0, rx_buffer, len);
                gpio_set_level(GPIO_NUM_2, 1);
            }
            vTaskDelay(2 / portTICK_PERIOD_MS);
        }
        if (newconn != -1)
        {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }

    vTaskDelete(NULL);
}

static void echo_task()
{
    // Configure parameters of an UART driver,
    // communication pins and install the driver
    uart_config_t uart_config = {
        .baud_rate = 2000000,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, BUF_SIZE, 0, 0, NULL);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);

    while (1)
    {
        //从串口接收67个字节
        int len = uart_read_bytes(UART_NUM_0, data, 64, 20 / portTICK_RATE_MS);
        // Write data back to the UART
        gpio_set_level(GPIO_NUM_2, 0);
        int err = send(newconn, data, len, 0);
        if (err < 0)
        {
            ESP_LOGE(TAG, "Error uart sending: err %d", errno);
            break;
        }
        gpio_set_level(GPIO_NUM_2, 1);

        // vTaskDelay(2 / portTICK_PERIOD_MS);
        //uart_write_bytes(UART_NUM_0, (const char *) data, len);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    // initialise_wifi_sta();
    initialise_wifi_ap();
    // xTaskCreate(tcp_client_task, "tcp_client", 4096, NULL, 5, NULL);
    xTaskCreate(tcp_server_task, "tcp_server", 4096, NULL, 5, NULL);
    xTaskCreate(echo_task, "uart_echo_task", 4096, NULL, 6, NULL);
}
