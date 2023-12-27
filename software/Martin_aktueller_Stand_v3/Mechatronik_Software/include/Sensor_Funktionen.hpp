#ifndef SENSOR_FKT
#define SENSOR_FKT

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "conf.hpp"

/***********************************************************************
TLA2528 Teil:
* ist ein 8-Kanal ADC der folgende Aufgaben erfüllt:
* Strommessung:     Motor 2-phasig, Eingangsstrom
* Spannungsmessung: Zwischenkreis, 3.3V, 15V, Netzspannung
* Funktionen um den ADC zu konfigurieren bzw. etwas auszumessen
***********************************************************************/
namespace TLA2528
{
  uint8_t StartUp_TLA2528(TwoWire* wire);
  uint8_t single_write_to_reg(TwoWire*wire,uint8_t reg_addr,uint8_t data,bool stop);
  uint8_t single_read_to_reg(TwoWire*wire,uint8_t reg_addr);
  uint8_t set_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit);
  uint8_t clr_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit);
  uint16_t man_CHA_Read(TwoWire*wire,uint8_t chan_id);

  void auto_CHA_Read_conf(TwoWire*wire);
  uint16_t auto_CHA_Read(TwoWire*wire);
}

/***********************************************************************
Temperatursensor MAX31820:
misst die Temperatur im Gerät
***********************************************************************/
namespace MAX31820
{
  float readTemperature(DallasTemperature sensors);
}

/***********************************************************************
Entprellsoftware:
 * einfache Funktion um dauerhaft eine Entprellung zu gewährleisten
************************************************************************/
namespace POTI_FKT
{
  float Read_Out_Frequency(uint8_t adc_pin,uint16_t ads_res,uint16_t frequ);
}
#endif