
// For more information about the motor:
// https://github.com/RobomasterOwltech/wiki/blob/main/PDFs/RM_MTR_GM6020-Brushless_User-Guide.pdf
#include "Motor_GM6020.hpp"

Motor_GM6020::Motor_GM6020(CAN_HandleTypeDef hcan, OperationModes mode, uint8_t motorId) {
    // Calling the base class constructor
    // super(name, profession);

    // Setting the properties
    this->attr->maxPosition = maxAngle;
    this->attr->minPosition = 0;

    this->attr->maxVelocity = maxVoltage;
    this->attr->minVelocity = minVoltage;

    this->attr->minTemp = minTemp;
    this->attr->maxTemp = maxTemp;

    this->attr->maxTorque = maxCurrent;
    this->attr->minTorque = minCurrent;

    this->contr.can = new ControllerCAN(hcan, uint8_t motorId);
}

Motor_GM6020::Motor_GM6020(TIM_HandleTypeDef htimer) {}

Motor_GM6020::