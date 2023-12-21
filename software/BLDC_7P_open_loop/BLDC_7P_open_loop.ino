#include <SimpleFOC.h>

#define PIN_IPH1 A15 //ADC2_5 == A15
#define PIN_IPH2 A16 //ADC2_6 == A16 
#define PIN_IPH3 A17 //ADC2_7 == A17



#define HALL_PH1 19 
#define HALL_PH2 18 
#define HALL_PH3 5

#define PIN_PH1_H 18 //23
#define PIN_PH2_H 17 //1
#define PIN_PH3_H 32
#define PIN_PH1_L 33
#define PIN_PH2_L 25
#define PIN_PH3_L 26

#define CURRENT_SENSE_GAIN -40.633
#define NBR_POLE_PAIRS 7




MagneticSensorI2C as5600 = MagneticSensorI2C(AS5600_I2C);
BLDCDriver6PWM driver = BLDCDriver6PWM(PIN_PH1_H, PIN_PH1_L, PIN_PH2_H, PIN_PH2_L, PIN_PH3_H, PIN_PH3_L);
InlineCurrentSense current_sense  = InlineCurrentSense(1, CURRENT_SENSE_GAIN, PIN_IPH1, PIN_IPH2, PIN_IPH3);
BLDCMotor motor = BLDCMotor(NBR_POLE_PAIRS);


int adcValue1;
int adcValue2;
int adcValue3;
uint8_t hall_sensor_state;

void setup() {
  // monitoring port
  Serial.begin(115200);
  Serial.print("Serial begin...");

  // init magnetic sensor hardware
  as5600.init();

  pinMode(PIN_IPH1, INPUT);
  pinMode(PIN_IPH2, INPUT);
  pinMode(PIN_IPH3, INPUT);

  pinMode(HALL_PH1, INPUT);
  pinMode(HALL_PH2, INPUT);
  pinMode(HALL_PH3, INPUT);
  
  pinMode(PIN_PH1_H, OUTPUT);
  pinMode(PIN_PH2_H, OUTPUT);
  pinMode(PIN_PH3_H, OUTPUT);
  pinMode(PIN_PH1_L, OUTPUT);
  pinMode(PIN_PH2_L, OUTPUT);
  pinMode(PIN_PH3_L, OUTPUT);

  digitalWrite(PIN_PH1_H, LOW);
  digitalWrite(PIN_PH2_H, LOW);
  digitalWrite(PIN_PH3_H, LOW);
  digitalWrite(PIN_PH1_L, LOW);
  digitalWrite(PIN_PH2_L, LOW);
  digitalWrite(PIN_PH3_L, LOW);

driver.pwm_frequency = 20000;
driver.dead_zone = 0.05;
driver.voltage_power_supply = 12;
driver.voltage_limit = 12;
driver.init();
//driver.enable();
//current_sense.init();
  motor.linkDriver(&driver);

  motor.voltage_limit = 3;   // [V]
  motor.velocity_limit = 90; // [rad/s] cca 50rpm
 
  // open loop control config
  motor.controller = MotionControlType::velocity_openloop;
  motor.init();
_delay(1000);
    
}

void loop() {
  motor.move(40);

  
  // display the angle and the angular velocity to the terminal
  /*Serial.print("Angle[rad]: ");
  Serial.print(as5600.getAngle());
  Serial.print("\t Speed [rad/s]:");
  Serial.println(as5600.getVelocity());


  currents = current_sense.getPhaseCurrents();
  Serial.print("Current Ph1 [mA]: ");
  Serial.println(currents.a*1000);
  Serial.print("Current Ph2 [mA]: ");
  Serial.println(currents.b*1000);
  Serial.print("Current Ph3 [mA]: ");
  Serial.println(currents.c*1000);
  Serial.println("");*/
  
}
