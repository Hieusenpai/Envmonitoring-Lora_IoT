const uint16_t myImage[] PROGMEM = {
  0xFFFF, 0xF800, 0x07E0, 0x001F,
  0xFFFF, 0xF800, 0x07E0, 0x001F,
  0xFFFF, 0xF800, 0x07E0, 0x001F,
  0xFFFF, 0xF800, 0x07E0, 0x001F
};

char buffer[10];  // Kích thước đủ để chứa số và ký tự kết thúc '\0'

void drawRGB565Image(int16_t x, int16_t y,const uint16_t *img , int16_t w, int16_t h ) {
  tft.startWrite();
  tft.setAddrWindow(x, y, w, h);
  for (int i = 0; i < w * h; i++) {
    tft.pushColor(pgm_read_word(&img[i]));
  }
  tft.endWrite();
}

void TFT_Print() {

  tft.fillScreen(ST77XX_BLACK);
  tft.drawRect(1, 2, 158, 126, ST77XX_WHITE);
  tft.drawLine(40, 0, 40, 128, ST77XX_WHITE);
 // tft.drawLine(100, 0, 100, 128, ST77XX_WHITE);
  tft.drawLine(0, 29, 158, 29, ST77XX_WHITE);
  tft.drawLine(0, 54, 158, 54, ST77XX_WHITE);
  tft.drawLine(0, 79, 158, 79, ST77XX_WHITE);
  tft.drawLine(0, 103, 158, 103, ST77XX_WHITE);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(8, 35);
  tft.print("T");
 // tft.setSwapBytes(true);
//drawRGB565Image(2, 30,nhietdo, 24, 24);
 tft.setTextColor(ST77XX_WHITE);
 tft.setTextSize(2);
  tft.setCursor(8, 60);
  tft.print("H");
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(6, 87);
  tft.print("PM2.5");
  tft.setTextColor(ST77XX_WHITE);
 tft.setTextSize(2);
  tft.setCursor(8, 106);
  tft.print("B");

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(21, 40); tft.print("(C)");
  tft.setCursor(22, 65); tft.print("(%)");

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(7, 8); tft.print((String)hour()); tft.print(":");
  if (minute() < 10) {
    tft.print("0");
  }
  else {}
  tft.print(String(minute()));
  tft.setCursor(15, 17);
  if (second() < 10) {
    tft.print("0");
  }
  else {}
  tft.print((String)second());

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  
  tft_drawString("TRAM 1", 70, 7); 
  //tft_drawString("KV.2", 110, 7);

  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
    tft.setCursor(50, 36);tft.print(nhietdo1, 2);
    tft.setCursor(50, 63);tft.print(doam1, 2);


  if ( mauCanhBao == 1) {
    tft.setTextColor(ST77XX_RED);
  }
  else tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(50, 84); tft.print(bui1, 2); tft.print(" ");
  tft.setCursor(50, 106); tft.print(dienap1, 2); tft.print(" ");

}

void tft_drawString(char* str , int x , int y)
{
  tft.setCursor(x, y);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print(str);
}
