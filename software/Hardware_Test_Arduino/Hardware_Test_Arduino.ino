#include <FastLED.h>


#define FAN_CONTROL_PIN 1
#define VFO 2
#define POT1 4
#define SW1 5
#define SW2 6
#define SW3 7
#define I2C_SDA 8
#define I2C_SLK 9

#define LINW 10
#define LINV 11
#define LINU 12
#define HINW 13
#define HINV 14
#define HINU 15

#define RELAY_SHUNT_AC 16
#define RGBLED 17
#define TEMP_HEATSINK 18

#define UART_TX 0
#define UART_RX 0

#define USB_N 19
#define USB_P 20

#define ISO_GPIO_1 21
#define ISO_GPIO_2 38

#define I_TRIP 33
#define SPI_CS 34
#define SPI_MOSI 35
#define SPI_CLK 36
#define SPI_MISO 37

#define FAN1_PWM_FB 48
#define FAN2_PWM_FB 47

bool state = 0;

int inverter_frequency = 0;
CRGB leds[1];

void setup() {
  // put your setup code here, to run once:
  USBSerial.begin(11500);
  USBSerial.println("[INFO] USBSerial online.");
  
  FastLED.addLeds<WS2812, RGBLED, GRB>(leds, 1);
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(2000);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);

  pinMode(LINW,OUTPUT);
  pinMode(HINW,OUTPUT);
  pinMode(LINV,OUTPUT);
  pinMode(HINV,OUTPUT);
  pinMode(LINU,OUTPUT);
  pinMode(HINU,OUTPUT);
  digitalWrite(LINW, LOW);
  digitalWrite(HINW, HIGH);
  digitalWrite(LINV, HIGH);
  digitalWrite(HINV, LOW);
  digitalWrite(LINU, LOW);
  digitalWrite(HINU, HIGH);


  pinMode(I_TRIP, OUTPUT);
  digitalWrite(I_TRIP, LOW);

  pinMode(RELAY_SHUNT_AC, OUTPUT);
  pinMode(FAN_CONTROL_PIN, OUTPUT);

}

void loop() {

  USBSerial.print("[Time] System time: ");
  USBSerial.println(millis());
  USBSerial.print("[INFO] Poti: ");
  USBSerial.println(analogRead(POT1));
  inverter_frequency = map(analogRead(POT1), 0, 4096, 0, 501);
  USBSerial.print("[INFO] Intverter frequency: ");
  USBSerial.println(inverter_frequency);


  digitalWrite(RELAY_SHUNT_AC, HIGH);
  digitalWrite(FAN_CONTROL_PIN, HIGH);

  if(state)
  {
    digitalWrite(LINW, LOW);
    digitalWrite(HINW, HIGH);
    state = 0;
  }
  else
  {
    digitalWrite(LINW, HIGH);
    digitalWrite(HINW, LOW);
    state = 1;
  }

  leds[0] = CRGB(0, 255, 0);

  if(digitalRead(SW1))
  {
    leds[0] = CRGB(0, 0, 255);
  }
  else if(digitalRead(SW2))
  {
    leds[0] = CRGB(0, 255, 255);
  }
  else if(digitalRead(SW3))
  {
    leds[0] = CRGB(255, 255, 0);
  }
  


  FastLED.show();

  delay(10);
}
