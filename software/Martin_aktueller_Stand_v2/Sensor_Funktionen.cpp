#include "Sensor_Funktionen.hpp"

using namespace MAX31820;
using namespace TLA2528;

/**********************************
Bereich für den Temperatursensor
**********************************/
float MAX31820::readTemperature(DallasTemperature sensors)
{
  // löst die Temperaturabfrage für alle Sensoren aus
  
  sensors.requestTemperatures();
  
  // Get temperature in Celsius for the first device
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Check for errors in reading temperature
  if (temperatureC == -127.00) {
    return -1;
  } else {
    // Return temperature
    return temperatureC;
  }
}

/**********************************
//Bereich für den ADC
**********************************/
uint8_t TLA2528::StartUp_TLA2528(TwoWire* wire) {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_SLAVE_ADDRESS);
  wire->write(TLA2528_WRITE_CONTI_BLOCK);
  wire->write(TLA2528_OSR_CFG);
  wire->write(0x02);
  wire->write(TLA2528_OPMODE_CFG);
  wire->write(0x02);
  wire->write(TLA2528_PIN_CFG);
  wire->write(0x00);
  wire->write(TLA2528_AUTO_SEQ_CH_SEL);
  error_write+=(wire->write(0xFF))  ? 0 : 1;
  if(!error_write) error_write+=wire->endTransmission(true);
  //Offset-Calibration
  if(!error_write) error_write+=TLA2528::set_singleBit(wire,TLA2528_GENERAL_CFG,0x02);
  delay(500);
  if(!error_write) error_write+=(0x02&single_read_to_reg(wire,TLA2528_GENERAL_CFG)) ? 0 : 1; //gegencheck, ob eine 0x02 zu lesen ist
  return error_write;
}

uint8_t TLA2528::single_write_to_reg(TwoWire*wire,uint8_t reg_addr,uint8_t data,bool stop)  {
  uint8_t error_write=0;
  wire->beginTransmission(TLA2528_SLAVE_ADDRESS);
  error_write+=(wire->write(TLA2528_SINGLE_REG_WRITE)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(data)) ? 0 : 1;
  if(!error_write)  error_write+=wire->endTransmission(stop);
  return error_write;
}

uint8_t TLA2528::single_read_to_reg(TwoWire*wire,uint8_t reg_addr)
{
  uint8_t error_write;
  wire->beginTransmission(TLA2528_SLAVE_ADDRESS);
  error_write+=(wire->write(TLA2528_SINGLE_REG_READ)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  if(!error_write)  error_write+=wire->endTransmission(false);
  if(!error_write)  error_write+=(wire->requestFrom(TLA2528_SLAVE_ADDRESS,0x01)) ? 0 : 1;
  if(!error_write)  { return wire->read();  } else  { return 0; }
}

// Hier wird clr oder set auf dasjenige Bit angewandt das 1 ist,
// wenn null wird das Bit im Register nicht angefasst
uint8_t TLA2528::set_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit)  {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_SLAVE_ADDRESS);
  error_write+=(wire->write(TLA2528_SET_BIT_REG)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(bit))  ? 0 : 1;
  if(!error_write)  wire->endTransmission(true);
  return error_write;
}

uint8_t TLA2528::clr_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit)  {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_SLAVE_ADDRESS);
  error_write+=(wire->write(TLA2528_CLR_BIT_REG)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(bit)) ? 0 : 1;
  if(!error_write)  wire->endTransmission(true);
  return error_write;
}

//ChannelRead
uint16_t TLA2528::man_CHA_Read(TwoWire*wire,CH_ID chan_id)
{
  uint8_t error_chan;
  uint16_t data;
  error_chan+=TLA2528::single_write_to_reg(wire,TLA2528_CHANNEL_SEL,static_cast<uint8_t>(chan_id),false); //den static_cast braucht man, da eine implizite Typ Konveriterung nicher erlaubt ist bei enum class
  if(!error_chan)  error_chan+=(wire->requestFrom(TLA2528_SLAVE_ADDRESS,0x02)) ? 0 : 1;
  if(!error_chan) { data=wire->read()<<8 | wire->read();  } else  { data=error_chan;  }
  return data;
}