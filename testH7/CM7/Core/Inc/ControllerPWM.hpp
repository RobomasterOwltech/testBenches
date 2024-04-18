//#include "stm32f4xx_hal.h"
#include "stm32h7xx_hal.h"
class ControllerPWM {
   private:
    TIM_HandleTypeDef* htim;
    //uint32_t timer_frequency;
    uint32_t clock_frequency;
    //uint32_t pwm_frequency;
    //uint32_t duty_cycle;
    //uint32_t prescaler;
    uint32_t ccr;  // Capture Compare Register
    uint32_t arr;  // AutoReload Register
    uint32_t channel;
    // Signal variables
    int maximum_pulse;
    int minimum_pulse;

   public:
    ControllerPWM(TIM_HandleTypeDef* _timer, uint16_t _channel);
    ~ControllerPWM();

    uint32_t get_frequency();
    uint32_t get_duty_cycle();
    uint32_t get_prescaler();

    void set_clock_frequency(uint32_t _clock_frequency);
    void set_signal_frequency(uint16_t _frequency);
    void set_duty_cycle(uint16_t _duty_cycle);

    void set_arr(uint32_t _arr);
    void set_ccr();
    void set_prescaler(uint16_t _prescaler);

    void start_pwm(uint32_t _channel);

    //virtual void set_positon(int desiredPosition);
    //virtual void set_velocity(int desiredVelocity);
    void calibrateSignal();
};
