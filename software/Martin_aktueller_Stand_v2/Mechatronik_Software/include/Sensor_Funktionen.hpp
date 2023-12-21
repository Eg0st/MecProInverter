#ifndef SENSOR_FKT
#define SENSOR_FKT

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

/************************************************
TLA2528 Registerdefinitionen
************************************************/
//STATS ist bullshit
//Alles was mit dem TLA2528 zu tun hat
#define TLA2528_SLAVE_ADDRESS 0x12

// Register-Definitionen
#define TLA2528_SYSTEM_STATUS   0x00    //aktueller Status des ADC
#define TLA2528_GENERAL_CFG     0x01
#define TLA2528_DATA_CFG        0x02
#define TLA2528_OSR_CFG         0x03
#define TLA2528_OPMODE_CFG      0x04
#define TLA2528_PIN_CFG         0x05
#define TLA2528_SEQUENCE_CFG    0x10
#define TLA2528_CHANNEL_SEL     0x11
#define TLA2528_AUTO_SEQ_CH_SEL 0x12

//Opcodes
#define TLA2528_SINGLE_REG_READ     0x10
#define TLA2528_SINGLE_REG_WRITE    0x08
#define TLA2528_SET_BIT_REG         0x18
#define TLA2528_CLR_BIT_REG         0x20
#define TLA2528_READ_CONTI_BLOCK    0x30
#define TLA2528_WRITE_CONTI_BLOCK   0x28

// Funktion zur Konfiguration des TLA2528
namespace TLA2528   {
  enum class CH_ID : uint8_t {CH0,CH1,CH2,CH3,CH4,CH5,CH6,CH7};
  //void mcpwm(void *arg)
  uint8_t StartUp_TLA2528(TwoWire* wire);
  uint8_t single_write_to_reg(TwoWire*wire,uint8_t reg_addr,uint8_t data,bool stop);
  uint8_t single_read_to_reg(TwoWire*wire,uint8_t reg_addr);
  uint8_t set_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit);
  uint8_t clr_singleBit(TwoWire*wire,uint8_t reg_addr,uint8_t bit);
  uint16_t man_CHA_Read(TwoWire*wire,CH_ID chan_id);

  void auto_CHA_Read_conf(TwoWire*wire);
  uint16_t auto_CHA_Read(TwoWire*wire);
}

/****************************************************************
ab hier alles was mit dem Temperatursensor MAX31820
****************************************************************/
namespace MAX31820  {
  float readTemperature(DallasTemperature sensors);
}
#endif