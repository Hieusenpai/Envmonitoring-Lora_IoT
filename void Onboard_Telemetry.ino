void Onboard_Telemetry() {

  currentSerialMillis = millis();
  if (currentSerialMillis - prevSerialMillis >= 2000) { //Run routine every millisRoutineInterval (ms)
    prevSerialMillis = currentSerialMillis;
   Serial.print("Nhiệt độ 1: "); Serial.println(nhietdo1);
    Serial.print("Độ ẩm 1   : "); Serial.println(doam1);
    Serial.print("Bụi 1     : "); Serial.println(bui1);
    Serial.print("Điện áp 1 : "); Serial.println(dienap1);
    Serial.println();
    Serial.print("Nhiệt độ 2: "); Serial.println(nhietdo2);
    Serial.print("Độ ẩm 2   : "); Serial.println(doam2);
    Serial.print("Bụi 2     : "); Serial.println(bui2);
    Serial.print("Điện áp 2 : "); Serial.println(dienap2);
    Serial.println("=============");
  }
}
