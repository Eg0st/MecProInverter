#ifndef CONF_HPP
#define CONF_HPP
/****************************************************************************************************************
conf.hpp:
* Definitionen von spezifischen Macros für die Peripherie
* kompletter Pin Header, der Software
****************************************************************************************************************/

/********************************
* Slave Adressen des I2C
********************************/
#define SSD1306_I2C_ADDR 0x3D
#define TLA2528_ADDRESS 0x12

/********************************
* DISPLAY SSD1306
********************************/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define WIRE_MAX 32

/********************************
* ADC TLA2528
********************************/
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

/***************************
CHANNEL DEFINITION TLA25528
***************************/
#define V_15    0
#define V_3_3   1
#define V_TANK  2
#define CURR_U  3
#define CURR_W  4
#define CURR_AC 5

/****************************
VALUES FOR VOLTAGE
 * 
****************************/
#define V_15_CALC 3029.39
#define V_3_3_CALC 15276.46
#define V_TANK_CALC 163.14
/***********************************
THRESHOLD VALUES
***********************************/
#define V_TANK_VOLTAGE_THRES 18

/********************************
* Sensor Spezifikationen
********************************/
//Grenzwerte
#define V_TANK_BORD 230

/********************************
* ESP_32 SPECIFIC INFORMATION
********************************/
//ADC
#define ADC_RESOLUTION 12
#define TIMER_FREQUENCY_HZ 50
/*****************************************
* SPECIFIC INFORMATION ABOUT THE MACHINE
*****************************************/
//Data of the Engine
#define VELOCITY_LIMIT 50 // [Hz]
#define M_VOLTAGE_LIMIT 300
#define POLE_PAIR 3

//Data of the Driver
#define PWM_FREQUENCY 10000
#define DEAD_ZONE 0.1
#define VOLTAGE_POWER_SUPPLY 230
#define D_VOLTAGE_LIMIT 230

/********************************
* PIN Header
********************************/
// Definitionen Bus Pin
#define ONE_WIRE_PIN 0

#define BUS_NUM 0
#define I2C_SDA 8
#define I2C_SLK 9

#define SPI_CS 34
#define SPI_MOSI 35
#define SPI_CLK 36
#define SPI_MISO 37

// Definitionen USB
#define USB_N 19
#define USB_P 20

// Definitionen PWM-Ausgaenge
#define LINW 10
#define LINV 11
#define LINU 12
#define HINW 13
#define HINV 14
#define HINU 15

// Peripherie
#define FAN_CONTROL_PIN 1   //wofür
#define FAN1_PWM_FB 48      //wofür
#define FAN2_PWM_FB 47      //wofür

// Switch-Assembly
#define VFO 2
#define POT1 4
#define SW1 5
#define SW2 6
#define SW3 7

// Relay Output
#define RELAY_SHUNT_AC 16
#define RGBLED 17
#define TEMP_HEATSINK 18    //wofür


#define ISO_GPIO_1 21       //wofür
#define ISO_GPIO_2 38       //wofür
/**************************
* IGBT ausschalten
**************************/
#define I_TRIP 33           //wofür

// TEST-Definitionen
#define PWM_TEST

#endif