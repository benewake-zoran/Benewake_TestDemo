void ScanUartFoc(TF* Lidar) {
  u8 i = 0;
  for (i = 0; i < 6; i++)
  {
    Lidar->BaudRate = UartFoc[i];
    Serial.begin(UartFoc[i]);
    delay(100);
    for (int j = 0; j < 50; j++) {
      getLidarData(Lidar);
      if (Lidar->receiveComplete)break;
    } if (Lidar->receiveComplete)break;
  }
  if (Lidar->receiveComplete) {
    Lidar->LidarFlag = true;
  }
  ScanFlag = 1;
}

void getLidarData(TF * Lidar)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  while (Serial.available() > 0) {
    rx[i] = Serial.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256)) {
        Lidar->distance = rx[2] + rx[3] * 256;
        Lidar->strength = rx[4] + rx[5] * 256;
        Lidar->receiveComplete = true;
      }
      i = 0;
    } else {
      i++;
    }
  }
}
