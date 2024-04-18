/*
 * Motor GM6020.h
 *
 *  Created on: Apr 12, 2024
 *      Author: @JorgePerC
 *
 * To know more about the motor, check:
 * https://github.com/Telpochcalli/wiki/blob/main/PDFs/RM_MTR_GM6020-Brushless_User-Guide.pdf
 */
#ifndef MotorGM6020_HPP
#define MotorGM6020_HPP

#include "BaseMotor.hpp"

class Motor_GM6020 : BaseMotor {
   private:
    // ===== Operational ranges =====
    /*
     * speed value unit: rpm
     * send frequency: 1 KHz
     */
    // Resolution for position control:
    static const uint8_t maxAngle = 8191;
    // Resolution for velocity control:
    static const int16_t maxVoltage = 30000;
    static const int16_t minVoltage = -30000;
    // Resolution for torque control:
    static const float maxCurrent = 0.90;
    static const float minCurrent = 2.45;
    // Operational temperature (Celsius):
    static const int16_t maxTemp = 55;
    static const int16_t minTemp = 0;

    static const uint8_t cntrlId = CONTROL_ID_A;

   public:
    Motor_GM6020(TIM_HandleTypeDef htimer, OperationModes mode, uint8_t motorId);
    Motor_GM6020(CAN_HandleTypeDef hcan, OperationModes mode, uint8_t motorId);

    void setReference(float w);
    void setControlType(OperationModes mode);

    ~Motor_GM6020();
};

#endif