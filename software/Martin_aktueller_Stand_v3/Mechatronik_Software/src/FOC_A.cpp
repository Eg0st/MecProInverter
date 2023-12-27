#include "FOC_A.hpp"

using namespace PWM_GEN;

void PWM_GEN::init(BLDCDriver6PWM* driver,BLDCMotor* motor)
{
    driver = new BLDCDriver6PWM(LINW, HINW, LINV, HINV, LINU, HINU);
    motor = new BLDCMotor(3);
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

    driver->pwm_frequency = PWM_FREQUENCY;
    driver->dead_zone = DEAD_ZONE;
    driver->voltage_power_supply = VOLTAGE_POWER_SUPPLY;
    driver->voltage_limit = D_VOLTAGE_LIMIT;
;
    driver->init();
    //driver.enable();
    //current_sense.init();
    motor->linkDriver(driver);

    motor->voltage_limit = M_VOLTAGE_LIMIT;   // [V]
    motor->velocity_limit = (float) 2*PI*VELOCITY_LIMIT; // [rad/s] cca 50rpm
 
    // open loop control config
    motor->controller = MotionControlType::velocity_openloop;
    motor->init();
    _delay(1000);
}

void PWM_GEN::PWM_Generation(BLDCDriver6PWM* driver,BLDCMotor* motor, float freq)
{
    static float new_target_value=2*PI*freq;
    motor->move(new_target_value);
}


