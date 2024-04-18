#include "ControllerPWM.hpp"

ControllerPWM::ControllerPWM(TIM_HandleTypeDef* _timer, uint16_t _channel) {
	htim = _timer;
    channel = _channel;

    /*
    _timer->Init.Prescaler = _prescaler - 1;
    prescaler = _timer->Init.Prescaler;
    clock_frequency = 1 / (_timer->Init.Period * _timer->Init.Prescaler);*/
}

ControllerPWM::~ControllerPWM() {}

void ControllerPWM::set_clock_frequency(uint32_t _clock_frequency) {
    //timer_frequency = (uint32_t) 1 / timer->Init.Period;
	htim->Init.Prescaler = (uint32_t)  HAL_RCC_GetSysClockFreq() / _clock_frequency;
    // TO DO:
    // Buscar clock source frequency
}
void ControllerPWM::set_signal_frequency(uint16_t pwm_frequency) {
    //arr = clock_frequency / pwm_frequency;

	htim->Instance->ARR = HAL_RCC_GetSysClockFreq() / (pwm_frequency*get_prescaler());
}
void ControllerPWM::set_duty_cycle(uint16_t _duty_cycle) { ccr = (uint32_t)(_duty_cycle * htim->Instance->ARR) / 100; }

void ControllerPWM::start_pwm(uint32_t _channel) {
    if (_channel == TIM_CHANNEL_1) {
    	htim->Instance->CCR1 = ccr;
    } else if (_channel == TIM_CHANNEL_2) {
    	htim->Instance->CCR1 = ccr;
    } else if (_channel == TIM_CHANNEL_3) {
    	htim->Instance->CCR1 = ccr;
    } else if (_channel == TIM_CHANNEL_4) {
    	htim->Instance->CCR1 = ccr;
    }
}

void ControllerPWM::set_arr(uint32_t _arr) {
    arr = _arr;
    htim->Instance->ARR = _arr;
}
uint32_t ControllerPWM::get_frequency() { return (uint32_t) clock_frequency / htim->Instance->ARR ; }
uint32_t ControllerPWM::get_duty_cycle() { return (uint32_t) (ccr*100)/htim->Instance->ARR;}
uint32_t ControllerPWM::get_prescaler() { return htim->Init.Prescaler; }
void ControllerPWM::calibrateSignal() {}
