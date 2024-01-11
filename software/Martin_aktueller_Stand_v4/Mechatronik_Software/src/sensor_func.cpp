#include "sensor_func.hpp"

using namespace MAX31820;
using namespace TLA2528;
using namespace POTI_FKT;

/**************************************************************************************************************************************
* Bereich für den Temperatursensor
**************************************************************************************************************************************/
float MAX31820::readTemperature(DallasTemperature sensors)
{
  sensors.requestTemperatures(); // löst die Temperaturabfrage für alle Sensoren aus
  float temperatureC = sensors.getTempCByIndex(0); // Get temperature in Celsius for the first device
  if (temperatureC == -127.00) // Check for errors in reading temperature
  {
    return -1;
  }
  else
  {
    return temperatureC;
  }
}

/**************************************************************************************************************************************
* Bereich für den TLA25528
**************************************************************************************************************************************/
uint8_t TLA2528::StartUp_TLA2528(TwoWire* wire) {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_ADDRESS);
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
  wire->beginTransmission(TLA2528_ADDRESS);
  error_write+=(wire->write(TLA2528_SINGLE_REG_WRITE)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(data)) ? 0 : 1;
  if(!error_write)  error_write+=wire->endTransmission(stop);
  return error_write;
}

uint8_t TLA2528::single_read_to_reg(TwoWire*wire,uint8_t reg_addr)
{
  uint8_t error_write;
  wire->beginTransmission(TLA2528_ADDRESS);
  error_write+=(wire->write(TLA2528_SINGLE_REG_READ)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  if(!error_write)  error_write+=wire->endTransmission(false);
  if(!error_write)  error_write+=(wire->requestFrom(TLA2528_ADDRESS,0x01)) ? 0 : 1;
  if(!error_write)  { return wire->read();  } else  { return 0; }
}

// Hier wird clr oder set auf dasjenige Bit angewandt das 1 ist,
// wenn null wird das Bit im Register nicht angefasst
uint8_t TLA2528::set_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit)  {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_ADDRESS);
  error_write+=(wire->write(TLA2528_SET_BIT_REG)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(bit))  ? 0 : 1;
  if(!error_write)  wire->endTransmission(true);
  return error_write;
}

uint8_t TLA2528::clr_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit)  {
  uint8_t error_write;
  wire->beginTransmission(TLA2528_ADDRESS);
  error_write+=(wire->write(TLA2528_CLR_BIT_REG)) ? 0 : 1;
  error_write+=(wire->write(reg_addr)) ? 0 : 1;
  error_write+=(wire->write(bit)) ? 0 : 1;
  if(!error_write)  wire->endTransmission(true);
  return error_write;
}

//ChannelRead
uint16_t TLA2528::man_CHA_Read(TwoWire*wire,uint8_t chan_id)
{
  uint8_t error_chan;
  uint16_t data;
  error_chan+=TLA2528::single_write_to_reg(wire,TLA2528_CHANNEL_SEL,chan_id,false); //den static_cast braucht man, da eine implizite Typ Konveriterung nicher erlaubt ist bei enum class
  if(!error_chan)  error_chan+=(wire->requestFrom(TLA2528_ADDRESS,0x02)) ? 0 : 1;
  if(!error_chan) { data=wire->read()<<8 | wire->read();  } else  { data=error_chan;  }
  return data;
}

/**************************************************************************************************************************************
Legt Reihenfolge des Auslesevorgangs fest
* return counter, welche Daten, werden aktuell ausgelesen
* return -1 Fehler (TODO: sinnvolle Lösung, aktuell aber zuviel zeug zu testen)
* return 0 nichts ausgelesen
**************************************************************************************************************************************/
int Auslesereihenfolge(TwoWire*wire,uint8_t flag)
{
  static uint8_t counter=1;
  constexpr uint8_t grenzwert_tank=4095*(V_TANK_BORD/3300);
  uint8_t error_flag;
  if(flag)
  {
    switch(counter)
    {
      case 1:
        error_flag=(TLA2528::man_CHA_Read(wire,V_TANK));
        error_flag=TLA2528::man_CHA_Read(wire,V_15);
      case 2:
        error_flag=TLA2528::man_CHA_Read(wire,V_TANK);
        error_flag=TLA2528::man_CHA_Read(wire,V_3_3);
      case 3:
        error_flag=TLA2528::man_CHA_Read(wire,V_TANK);
        error_flag=TLA2528::man_CHA_Read(wire,V_3_3);
      case 4:
        error_flag=TLA2528::man_CHA_Read(wire,CURR_U);
        error_flag=TLA2528::man_CHA_Read(wire,CURR_W);
      case 5:
        error_flag=TLA2528::man_CHA_Read(wire,V_TANK);
        error_flag=TLA2528::man_CHA_Read(wire,CURR_AC);
      default:
        counter=0;
    }
    counter++;
    return error_flag;
  }
  return 0;
}

/**************************************************************************************************************************************
* Bereich für die POTI_FKT
**************************************************************************************************************************************/
float POTI_FKT::Read_Out_Frequency(uint8_t adc_pin,uint16_t ads_res,uint16_t frequ)
{
  float freq=(analogRead(adc_pin)/((2^ads_res)-1))*frequ;
  return freq;
}