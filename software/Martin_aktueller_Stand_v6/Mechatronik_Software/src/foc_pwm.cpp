#include "foc_pwm.hpp"

using namespace FOC;

/**************************************************************************************************************************************
* Bereich für die Field Oriented Controll
**************************************************************************************************************************************/
void FOC::init(BLDCDriver6PWM** driver,BLDCMotor** motor)
{
    *driver = new BLDCDriver6PWM(HINW, LINW, HINV, LINV, HINU, LINU);
    *motor = new BLDCMotor(POLE_PAIR);
    pinMode(LINW,OUTPUT);
    pinMode(HINW,OUTPUT);
    pinMode(LINV,OUTPUT);
    pinMode(HINV,OUTPUT);
    pinMode(HINU,OUTPUT);
    pinMode(HINU,OUTPUT);
    digitalWrite(LINW, LOW);
    digitalWrite(HINW, LOW);
    digitalWrite(LINV, LOW);
    digitalWrite(HINV, LOW);
    digitalWrite(HINU, LOW);
    digitalWrite(HINU, LOW);

    // Driver-Part
    (*driver)->pwm_frequency = PWM_FREQUENCY;
    (*driver)->dead_zone = DEAD_ZONE;
    (*driver)->voltage_power_supply = VOLTAGE_POWER_SUPPLY;
    (*driver)->voltage_limit = D_VOLTAGE_LIMIT;
    (*driver)->init();
    //driver->enable(); //waere glaube ich ohne motor

    // Motor-Part
    (*motor)->linkDriver(*driver);
    (*motor)->voltage_limit = M_VOLTAGE_LIMIT;   // [V]
    (*motor)->velocity_limit = (float) 2*PI*VELOCITY_LIMIT; // [rad/s] cca 50rpm
    (*motor)->controller = MotionControlType::velocity_openloop;   // open loop control config
    (*motor)->init();
    _delay(1000);
}

void FOC::PWM_Generation(BLDCMotor* motor, float freq)
{
    static float new_target_value=2*PI*freq;
    motor->move(new_target_value);
}

/**************************************************************************************************************************************
* Bereich für die Timing Function

Anmerkungen: 
* static Timing*instance: Globaler Zeiger auf die Timing Instanz, da so die ISR aufgerufen werden kann
* nur eine Timing Klasse erstellen
**************************************************************************************************************************************/
volatile uint64_t flag_isr = 0;

void IRAM_ATTR onTimer()
{
  flag_isr++;
}

namespace TIMING
{
hw_timer_t * timer_p;
void initTimer(uint64_t us_frequenz)
{
  timer_p = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_p, &onTimer, true);
  timerAlarmWrite(timer_p, us_frequenz, true);
}

void startTimer()
{
  timerAlarmEnable(timer_p);
}

void stopTimer()
{
  timerAlarmDisable(timer_p);
}

void destructTimer()
{
  timerEnd(timer_p);
}
}

