#ifndef FOC_PWM_HPP
#define FOC_PWM_HPP

#include "SimpleFOC.h"
#include "conf.hpp"

/**************************************************************************************************************************************
* Bereich für die Field Oriented Controll

Anmerkungen:
driver.enable(): sollte nur gebraucht werden, wenn wir keinen Motor haben
driver.init(): sollte die pinMode belegung überflüssig machen, da das in dieser init() Methode enthalten ist
**************************************************************************************************************************************/
namespace FOC
{
    void init(BLDCDriver6PWM** driver,BLDCMotor** motor);
    void PWM_Generation(BLDCMotor* motor, float freq);
}

/**************************************************************************************************************************************
* Bereich für die Timing Function
* Anmerkungen: nur eine Instanz erstellen
**************************************************************************************************************************************/
    class Timing {
    public:
        Timing();
        ~Timing();
        void start(uint64_t timer_period_us);
        void stop();
        volatile uint8_t flag;
    private:
        esp_timer_handle_t myTimer;
        static void IRAM_ATTR timerCallback(void *arg);
    };
#endif
