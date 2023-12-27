#ifndef PWM_GENERATION
#define PWM_GENERATION

#include "SimpleFOC.h"
#include "conf.hpp"
namespace PWM_GEN
{
    void init(BLDCDriver6PWM* driver,BLDCMotor* motor);
    void PWM_Generation(BLDCDriver6PWM* driver,BLDCMotor* motor, float freq);
}

#endif