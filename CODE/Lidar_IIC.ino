void FoudIICDevice(TF* Lidar)
{
  for (u8 i = 1; i < 127; i++) {
    if(i == 60)continue;
    Wire.beginTransmission(i);//（和地址i连接）
    int error = Wire.endTransmission();
    if (error == 0) {
      Lidar->LidarFlag = true;
      Lidar->ID = i;
    }
  }
  ScanFlag = 1;
}

void Get_LidarDatafromIIC(TF* Lidar) {
  char i = 0;
  char j = 0;
  byte rx_buf[9] = {0};
  Wire.beginTransmission(Lidar->ID); // Begin a transmission to the I2C Slave device with the given address.
  for (j = 0; j < 5; j++)
  {
    Wire.write(cmd[j]);
  }
  Wire.endTransmission();  // Send a START Sign
  Wire.requestFrom(Lidar->ID, 9); // request 7 bytes from slave device address

  while ( Wire.available())
  {
    rx_buf[i] = Wire.read(); // received one byte
    i++;
    if (i >= 9)
    {
      i = 0;
      Lidar->distance = rx_buf[3] * 256 + rx_buf[2];
      Lidar->strength = rx_buf[5] * 256 + rx_buf[4];
      Lidar->receiveComplete = true;
    }
  }
}
