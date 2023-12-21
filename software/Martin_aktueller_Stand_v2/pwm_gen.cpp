#include "pwm_gen.hpp"

using namespace PWM_GE;

void PWM_GE::init(Interface inf)
{
    inf.motor=new BLDCMotor(3);
    inf.driver=new BLDCDriver6PWM(PIN_PH1_H, PIN_PH1_L, PIN_PH2_H, PIN_PH2_L, PIN_PH3_H, PIN_PH3_L);
    
}
