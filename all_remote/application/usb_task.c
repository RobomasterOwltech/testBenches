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
#include "remote_control.h"

#include "detect_task.h"
#include "voltage_task.h"
#include "CAN_receive.h"

#include "shoot.h"
#include "chassis_behaviour.h"
#include "gimbal_behaviour.h"

extern shoot_control_t shoot_control;
extern chassis_behaviour_e chassis_behaviour_mode;

extern gimbal_behaviour_e gimbal_behaviour;

const int debugTextSize = 40;

char shootModeText [debugTextSize];
char chassisModeText [debugTextSize];
char gimbalModeText [debugTextSize];

static void usb_printf(const char *fmt,...);

static uint8_t usb_buf[256];
static const char status[2][7] = {"OK", "ERROR!"};
const error_t *error_list_usb_local;

void usb_task(void const * argument)
{
    MX_USB_DEVICE_Init();
    error_list_usb_local = get_error_list_point();
   
    
/*

*/
    while(1)
    {
                // ===================================
        // ==== This is for debugging robot modes ====
        // ===================================
        
        switch (shoot_control.shoot_mode)
        {
        case SHOOT_STOP:
            snprintf(shootModeText, debugTextSize, "SHOOT_STOP");
            break;
        case SHOOT_READY_FRIC:
            snprintf(shootModeText, debugTextSize, "SHOOT_READY_FRIC");
            break;
        case SHOOT_READY_BULLET:
            snprintf(shootModeText, debugTextSize, "SHOOT_READY_BULLET");
            break;
        case SHOOT_READY:
            snprintf(shootModeText, debugTextSize, "SHOOT_READY");
            break;
        case SHOOT_BULLET:
            snprintf(shootModeText, debugTextSize, "SHOOT_BULLET");
            break;
        case SHOOT_CONTINUE_BULLET:
            snprintf(shootModeText, debugTextSize, "SHOOT_CONTINUE_BULLET");
            break;
        case SHOOT_DONE:
            snprintf(shootModeText, debugTextSize, "SHOOT_DONE");
            break;
        
        default:
            snprintf(shootModeText, debugTextSize, "SHOOT_ERROR");
            break;
        }
        // ===================================
        switch (chassis_behaviour_mode)
        {
        case CHASSIS_ZERO_FORCE:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_ZERO_FORCE");
            break;
        case CHASSIS_NO_MOVE:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_NO_MOVE");
            break;
        case CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW");
            break;
        case CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW");
            break;
        case CHASSIS_NO_FOLLOW_YAW:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_NO_FOLLOW_YAW");
            break;
        case CHASSIS_OPEN:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_OPEN");
            break;
        
        default:
            snprintf(chassisModeText, debugTextSize, "CHASSIS_ERROR");
            break;
        }
        // ===================================
        switch (chassis_behaviour_mode)
        {
        case GIMBAL_ZERO_FORCE:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_ZERO_FORCE");
            break;
        case GIMBAL_INIT:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_INIT");
            break;           
        case GIMBAL_CALI:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_CALI");
            break;           
        case GIMBAL_ABSOLUTE_ANGLE:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_ABSOLUTE_ANGLE");
            break; 
        case GIMBAL_RELATIVE_ANGLE:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_RELATIVE_ANGLE");
            break; 
        case GIMBAL_MOTIONLESS:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_MOTIONLESS");
            break;  
        default:
            snprintf (gimbalModeText, debugTextSize, "GIMBAL_ERROR_MODE");
            break;
        }

        osDelay(500);
        usb_printf(
            /*"******************************\r\n\
            voltage percentage:%d%% \r\n\
            DBUS:%s\r\n\
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
            referee usart:%s\r\n",
            get_battery_percentage(), 
            status[error_list_usb_local[DBUS_TOE].error_exist],
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
            status[error_list_usb_local[REFEREE_TOE].error_exist]);
        
            // ======================= */   
            //  "******************************\r\n\
            // voltage percentage:%d%% \r\n\
            // DBUS:%s\r\n\
            // speed 0: %d \r\n\
            // speed 1: %d \r\n\
            // speed 2: %d \r\n\
            // speed 3: %d \r\n\
            // switch 1:%d\r\n\
            // switch 2:%d\r\n\
            // // ******************************\r\n",
            //      get_battery_percentage(), 
            //      status[error_list_usb_local[DBUS_TOE].error_exist],
            //      motor_chassis[0].speed_rpm,
            //      motor_chassis[1].speed_rpm,
            //      motor_chassis[2].speed_rpm,
            //      motor_chassis[3].speed_rpm,
            //      get_remote_control_point()->rc.s[0],
            //      get_remote_control_point()->rc.s[1]); 
            
            // ==============================
            // "******************************\r\n\
            // voltage percentage:%d%% \r\n\
            // DBUS:%s\r\n\
            // channel 0: %d \r\n\
            // channel 1: %d \r\n\
            // channel 2: %d \r\n\
            // channel 3: %d \r\n\
            // channel 4: %d \r\n\
            // channel 5: %d \r\n\
            // switch 1:%x\r\n\
            // switch 2:%x\r\n\
            // switch 3:%x\r\n\
            // switch 4:%x\r\n\
            // ******************************\r\n",
            //             get_battery_percentage(), 
            //             status[error_list_usb_local[DBUS_TOE].error_exist],
            //             get_remote_control_point()->rc.ch[0], // motor_chassis.speed_rpm
            //             get_remote_control_point()->rc.ch[1], // 
            //             get_remote_control_point()->rc.ch[2], // 
            //             get_remote_control_point()->rc.ch[3], // 
            //             get_remote_control_point()->rc.ch[4], // 
            //             get_remote_control_point()->rc.ch[5], // 
            //             get_remote_control_point()->rc.s[0],
            //             get_remote_control_point()->rc.s[1],
            //             get_remote_control_point()->rc.s[2],
            //             get_remote_control_point()->rc.s[3]); 
            // ==============================

            "******************************\r\n\
            chassis mode: %s \r\n\
            gimbal mode: %s \r\n\
            shoot mode: %s \r\n\
            ******************************\r\n",
                        shootModeText, 
                        chassisModeText,
                        gimbalModeText); 

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
