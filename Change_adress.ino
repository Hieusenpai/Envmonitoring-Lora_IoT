// ESP32 Serial Bridge (UART0 <-> UART2)
// tải file RF_Setting_EN_V2.7 để công tắc 2p mức cao để setup 2 modul lora rồi mới upload code.
#define UART2_TX 17  // TX2
#define UART2_RX 16  // RX2
#define BAUDRATE 9600

void setup() {
  // Khởi tạo UART0 (Serial USB)
  Serial.begin(BAUDRATE);

  // Khởi tạo UART2
  Serial2.begin(BAUDRATE, SERIAL_8N1, UART2_RX, UART2_TX);

 // Serial.println("UART Bridge ESP32 (UART0 <-> UART2) started");
}

void loop() {
  // Nhận từ UART0 và gửi sang UART2
  while (Serial.available()) {
    int c = Serial.read();
    Serial2.write(c);
  }

  // Nhận từ UART2 và gửi sang UART0
  while (Serial2.available()) {
    int c = Serial2.read();
    Serial.write(c);
  }
}
