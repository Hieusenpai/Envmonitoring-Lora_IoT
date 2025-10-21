/*
   LoRa E32-TTL-100
   Receive fixed transmission message as a specified point.
   https://www.mischianti.org/2019/11/10/lora-e32-device-for-arduino-esp32-or-esp8266-fixed-transmission-part-4/
  
  Update:
          + 04/04/2024: Sửa lại code nhằm phù hợp với BLynk phiên bản mới
  Địa chỉ:
          - configuration.ADDL = 6;
          - configuration.ADDH = 0;
          - configuration.CHAN = 0x09;

   LIBRARY
   - TFT_eSPI (2.5.43)

*/

TaskHandle_t Task2;

#include "iconSuDung.h"
//#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
//TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32)  // Feather Huzzah32
#define TFT_CS 15
#define TFT_RST 4
#define TFT_DC 2

#elif defined(ESP8266)
#define TFT_CS 4
#define TFT_RST 16
#define TFT_DC 5

#else
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 15
#define TFT_RST 4  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 2
#endif
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//===== Blynk IOT =====//
#define BLYNK_TEMPLATE_ID "TMPL6px07Al-A"
#define BLYNK_TEMPLATE_NAME "do an"
#define BLYNK_AUTH_TOKEN "Tmx16VjEhxsQhgO0s2Q59lQgbqtl9TVb"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FPT Telecom-E01E";
char pass[] = "12341234";
TaskHandle_t Core2;
BlynkTimer timer;
WidgetRTC rtc;

void clockDisplay() {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
}
BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}


#define ledRun 5
#define ledAlarm 21
#define buzz 12


// -------------------------------------
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

long dv, chuc, tram, nghin, chucnghin;
int s;
long t1, t2, t3, t4, t5;
String str = "";

float
  nhietdo1,
  doam1,
  bui1,
  dienap1,
  nhietdo2,
  doam2,
  bui2,
  dienap2,
  buiHigh = 120.00,
  batLow = 3.60;

unsigned long
  previousMillis = 0,
  currentMillis = 0,
  prevSerialMillis = 0,
  currentSerialMillis = 0,
  prevBlynkMillis = 0,
  currentBlynkMillis = 0;

int
  ledState = 0,
  mauCanhBao = 0,
  ERR = 0,
  ERR2 = 0;

#define UART2_TX 17  // TX2
#define UART2_RX 16  // RX2
#define BAUDRATE 9600

void setup() {
  Serial.begin(115200);
  Serial2.begin(BAUDRATE, SERIAL_8N1, UART2_RX, UART2_TX);
  pinMode(ledRun, OUTPUT);
  pinMode(ledAlarm, OUTPUT);
  pinMode(buzz, OUTPUT);

  digitalWrite(ledRun, HIGH);
  digitalWrite(ledAlarm, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);


  // ---------------------------


  xTaskCreatePinnedToCore(
    Task2code, /* Task function. */
    "Task2",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);        /* pin task to core 1 */

}  // end Setup
uint32_t send_data = 0;
void Task2code(void* pvParameters) {
  Blynk.begin(auth, ssid, pass);
  setSyncInterval(5);  // Sync interval in seconds (10 minutes)
  while (1) {
    if (millis() - send_data > 1000) {
      send_data = millis();
      senBlynk();
       Serial.print("send Blynk ! \r\n");
    }
    Blynk.run();
    timer.run();
    vTaskDelay(100);
  }
}
uint32_t timer_sceen = 0;
void loop() {
  NhanDuLieu();
  if (millis() - timer_sceen > 500) {
    timer_sceen = millis();
    TFT_Print();
  }

  Onboard_Telemetry();
  CanhBao();
}  // end loop
