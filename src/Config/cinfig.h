#ifndef _CONFIG_H_
#define _CONFIG_H_

#define SERIAL_BAUD_RATE                                            500000
#define LED_PIN_RED                                                 13
#define LED_PIN_GREEN                                               12
#define LED_PIN_BLUE                                                14

#define DOOR_RELAY_IN                                               33
#define DOOR_RELAY_OUT                                              25

#define BUZZER_PIN                                                  27
#define BUZZER_PIN_2                                                26

#define W5500_CHIP_SELECT_PIN                                       5
#define ETHERNET_CONNECT_TIMEOUT                                    5000
#define ETHERNET_RESPONSE_TIMEOUT                                   5000
#define MAX_COM_MESSAGE_SIZE                                        64
#define DEFAULT_HTTP_RESPONSE_TIMEOUT                               3000
#define DEFAULT_WS_RESPONSE_TIMEOUT                                 3000
#define WS_RECOONECT_INTERVAL                                       100
#define MAX_WS_RECCONNECT_TIMES                                     10
#define MAX_WS_DATA_SIZE                                            46
#define MAX_WIFI_SSID_SIZE                                          46
#define MAX_WIFI_PASS_SIZE                                          46
#define MAX_ERROR_SERVER_SIZE                                       44
#define PING_PONG_DEFAULT_DURATION                                  5000
#define PING_PONG_TIMEOUT                                           2500
#define PING_PONG_DURATION_MULTIPLIER                               1000
#define MAX_WS_MSG_SIZE                                             256

// RDM and Serial Module Settings
#define RDM_BAUDRATE                                                9600
#define RDM_RX_PIN_1                                                4 
#define RDM_TX_PIN_1                                                2
#define RDM_RX_PIN_2                                                16
#define RDM_TX_PIN_2                                                17

#endif