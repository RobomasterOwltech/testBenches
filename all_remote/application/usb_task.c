/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       usb_task.c/h
  * @brief      usb outputs the error message.usb���������Ϣ
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Nov-11-2019     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */
#include "usb_task.h"

#include "cmsis_os.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"

#include "detect_task.h"
#include "voltage_task.h"
#include "remote_control.h"


static void usb_printf(const char *fmt,...);

static uint8_t usb_buf[256];
static const char status[2][7] = {"OK", "ERROR!"};
const error_t *error_list_usb_local;

void intToBinaryString(int num, char *binaryString) {
    int index = 0;
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {

        binaryString[index++] = ((num >> i) & 1) + '0';
    }
    binaryString[index] = '\0'; // Agrega el carácter nulo al final de la cadena
    // usb_printf("num: %d bin: %s", num, binaryString);

}

void usb_task(void const * argument)
{
    MX_USB_DEVICE_Init();
    error_list_usb_local = get_error_list_point();
   

    char binaryString0[16 + 1]; // Tamaño de la cadena igual al número de bits más 1 para el carácter nulo
    char binaryString1[16 + 1]; // Tamaño de la cadena igual al número de bits más 1 para el carácter nulo
    char binaryString2[16 + 1]; // Tamaño de la cadena igual al número de bits más 1 para el carácter nulo
    char binaryString3[16 + 1]; // Tamaño de la cadena igual al número de bits más 1 para el carácter nulo
    
    
/*
 chassis motor1:%s\r\n\
 chassis motor2:%s\r\n\
 chassis motor3:%s\r\n\
 chassis motor4:%s\r\n\
 yaw motor:%s\r\n\
 pitch motor:%s\r\n\
 trigger motor:%s\r\n\
 gyro sensor:%s\r\n\
 accel sensor:%s\r\n\
 mag sensor:%s\r\n\
 referee usart:%s\r\n\

,
            status[error_list_usb_local[CHASSIS_MOTOR1_TOE].error_exist],
            status[error_list_usb_local[CHASSIS_MOTOR2_TOE].error_exist],
            status[error_list_usb_local[CHASSIS_MOTOR3_TOE].error_exist],
            status[error_list_usb_local[CHASSIS_MOTOR4_TOE].error_exist],
            status[error_list_usb_local[YAW_GIMBAL_MOTOR_TOE].error_exist],
            status[error_list_usb_local[PITCH_GIMBAL_MOTOR_TOE].error_exist],
            status[error_list_usb_local[TRIGGER_MOTOR_TOE].error_exist],
            status[error_list_usb_local[BOARD_GYRO_TOE].error_exist],
            status[error_list_usb_local[BOARD_ACCEL_TOE].error_exist],
            status[error_list_usb_local[BOARD_MAG_TOE].error_exist],
            status[error_list_usb_local[REFEREE_TOE].error_exist]

*/
    while(1)
    {
        // intToBinaryString(get_remote_control_point()->rc.ch[0], binaryString0);
        // intToBinaryString(get_remote_control_point()->rc.ch[1], binaryString1);
        // intToBinaryString(get_remote_control_point()->rc.ch[2], binaryString2);
        // intToBinaryString(get_remote_control_point()->rc.ch[3], binaryString3);


        osDelay(500);
        usb_printf(
"******************************\r\n\
voltage percentage:%d%% \r\n\
DBUS:%s\r\n\
channel 1:%d \r\n\
channel 2:%d \r\n\
channel 3:%d \r\n\
channel 4:%d \r\n\
switch 1:%d\r\n\
switch 2:%d\r\n\
******************************\r\n",
            get_battery_percentage(), 
            status[error_list_usb_local[DBUS_TOE].error_exist],
            get_remote_control_point()->rc.ch[0],
            get_remote_control_point()->rc.ch[1],
            get_remote_control_point()->rc.ch[2],
            get_remote_control_point()->rc.ch[3],
            get_remote_control_point()->rc.s[0],
            get_remote_control_point()->rc.s[1]);

    }

}

static void usb_printf(const char *fmt,...)
{
    static va_list ap;
    uint16_t len = 0;

    va_start(ap, fmt);

    len = vsprintf((char *)usb_buf, fmt, ap);

    va_end(ap);


    CDC_Transmit_FS(usb_buf, len);
}
