/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2017,2018  Sean Nelson <audiohacked@gmail.com>

 * OpenCorsairLink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.

 * OpenCorsairLink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OpenCorsairLink.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _PROTOCOL_COMMANDERPRO_H
#define _PROTOCOL_COMMANDERPRO_H

/*

Modes are listed in this order (shown with default values)

"Default" (graph configuration request 0x25)
20 degC, 600 rpm
 25 degC, 600 rpm ;
 29 degC, 750 rpm ;
 33 degC, 1000 rpm ;
 37 degC, 1250 rpm ;
 40 degC, 1500 rpm

"Quiet" (graph configuration request 0x25) (same points as in "Default" mode above)
"Balanced" (graph configuration request 0x25)
 20 degC, 750 rpm ;
 25 degC, 1000 rpm ;
 29 degC, 1250 rpm ;
 33 degC, 1500 rpm ;
 37 degC, 1750 rpm ;
 40 degC, 2000 rpm

"Performance" (graph configuration request 0x25)
 20 degC, 1000 rpm ;
 25 degC, 1250 rpm ;
 29 degC, 1500 rpm ;
 33 degC, 1750 rpm ;
 37 degC, 2000 rpm ;
 40 degC, 2500 rpm

"Custom" (graph configuration request 0x25)
 20 degC, 600 rpm ;
 30 degC, 600 rpm ;
 40 degC, 750 rpm ;
 50 degC, 1000 rpm ;
 60 degC, 1250 rpm ;
 70 degC, 1500 rpm

"Fixed %" (percent configuration request 0x23) 40%

"Fixed rpm" (rpm configuration request 0x24) 500

"Max" (percent configuration request) (100%)

*/

enum CorsairLightingNodePro_LED_Mode
{
    LNP_StaticColor = 0,
    LNP_Temperature = 3,
    LNP_RainbowCycle = 4,
    LNP_RainbowWave = 5,
    LNP_ColourShift = 6,
    LNP_ColourPulse = 7,
    LNP_ColourWave = 8,
    LNP_Visor = 9,
    LNP_Marquee = 10,
    LNP_Strobing = 11,
    LNP_Sequential = 12,

};

enum CorsairLightingNodePro_LED_Rate
{
    LNP_ZeroRate = 0,
    LNP_HalfRate = 1,
    LNP_FullRate = 2,
};

enum CorsairLightingNodePro_LED_Type
{
    LNP_LED_Strip = 0x0A,
    LNP_LED_HD_FAN = 0x0C,
    LNP_LED_SP_FAN = 0x0C,
    LNP_LED_LL_FAN = 0x00,
    LNP_Dominator = 0x1C,
};

enum COMMANDERPRO_Fan_Modes
{
    COMMANDERPRO_FixedPWM = 0x23,
    COMMANDERPRO_FixedRPM = 0x24,
    COMMANDERPRO_Curve = 0x25
};

#define COMMANDER_PRO_FAN_TABLE_DEFAULT( x ) \
    x[0].temperature = 0x14;                 \
    x[1].temperature = 0x19;                 \
    x[2].temperature = 0x1d;                 \
    x[3].temperature = 0x21;                 \
    x[4].temperature = 0x25;                 \
    x[5].temperature = 0x28;                 \
    x[0].speed = 0x258;                      \
    x[1].speed = 0x258;                      \
    x[2].speed = 0x2EE;                      \
    x[3].speed = 0x3E8;                      \
    x[4].speed = 0x4E2;                      \
    x[5].speed = 0x5DC;

#define COMMANDER_PRO_FAN_TABLE_QUIET( x ) \
    x[0].temperature = 0x14;               \
    x[1].temperature = 0x19;               \
    x[2].temperature = 0x1d;               \
    x[3].temperature = 0x21;               \
    x[4].temperature = 0x25;               \
    x[5].temperature = 0x28;               \
    x[0].speed = 0x258;                    \
    x[1].speed = 0x258;                    \
    x[2].speed = 0x2EE;                    \
    x[3].speed = 0x3E8;                    \
    x[4].speed = 0x4E2;                    \
    x[5].speed = 0x5DC;

#define COMMANDER_PRO_FAN_TABLE_BALANCED( x ) \
    x[0].temperature = 0x14;                  \
    x[1].temperature = 0x19;                  \
    x[2].temperature = 0x1d;                  \
    x[3].temperature = 0x21;                  \
    x[4].temperature = 0x25;                  \
    x[5].temperature = 0x28;                  \
    x[0].speed = 0x2EE;                       \
    x[1].speed = 0x3E8;                       \
    x[2].speed = 0x4E2;                       \
    x[3].speed = 0x5DC;                       \
    x[4].speed = 0x6A4;                       \
    x[5].speed = 0x7D0;

#define COMMANDER_PRO_FAN_TABLE_PERFORMANCE( x ) \
    x[0].temperature = 0x14;                     \
    x[1].temperature = 0x19;                     \
    x[2].temperature = 0x1d;                     \
    x[3].temperature = 0x21;                     \
    x[4].temperature = 0x25;                     \
    x[5].temperature = 0x28;                     \
    x[0].speed = 0x3E8;                          \
    x[1].speed = 0x4E2;                          \
    x[2].speed = 0x5DC;                          \
    x[3].speed = 0x6A4;                          \
    x[4].speed = 0x7D0;                          \
    x[5].speed = 0x9C4;

int
corsairlink_commanderpro_device_id(
    struct corsair_device_info* dev, struct libusb_device_handle* handle, uint8_t* device_id );

int
corsairlink_commanderpro_name(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* name,
    uint8_t name_str_len );

int
corsairlink_commanderpro_vendor(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* name,
    uint8_t name_str_len );

int
corsairlink_commanderpro_product(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* name,
    uint8_t name_str_len );

int
corsairlink_commanderpro_firmware_id(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* firmware,
    uint8_t firmware_str_len );

int
corsairlink_commanderpro_software_id(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* firmware,
    uint8_t firmware_str_len );

int
corsairlink_commanderpro_bootloader_id(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    char* firmware,
    uint8_t firmware_str_len );

/* Fans */
int
corsairlink_commanderpro_fan_print_mode(
    uint8_t mode, uint16_t data, char* modestr, uint8_t modestr_size );

int
corsairlink_commanderpro_fan_count(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl);

int
corsairlink_commanderpro_get_fan_speed_rpm(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_get_fan_speed_pwm(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_get_fan_detect_type(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_set_fan_curve(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_set_fan_speed_pwm(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_set_fan_speed_rpm(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_fan_mode_default(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_fan_mode_quiet(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_fan_mode_balanced(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

int
corsairlink_commanderpro_fan_mode_performance(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct fan_control* ctrl );

/* Temperature */
int
corsairlink_commanderpro_tempsensorscount(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    uint8_t* temperature_sensors_count );

int
corsairlink_commanderpro_temperature(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    uint8_t sensor_index,
    double* temperature );

int
corsairlink_commanderpro_voltage(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    uint8_t sensor_index,
    double* voltage );

/* LEDs */
int
corsairlink_commanderpro_led_rainbow(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct led_control* ctrl );

int
corsairlink_commanderpro_led_static_color(
    struct corsair_device_info* dev,
    struct libusb_device_handle* handle,
    struct led_control* ctrl );

#endif // _PROTOCOL_COMMANDERPRO_H
