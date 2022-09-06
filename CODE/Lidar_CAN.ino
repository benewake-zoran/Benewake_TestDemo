void ScanCanFoc(SoftwareSerial * port, TF * Lidar)
{
  u8 i = 0;
  for (i = 0; i < 7; i++)
  {
    SetCanFoc(port, CanFoc[i]);
    delay(100);
    while (port->available() > 0) {
      port->read();
    }
    delay(100);
    //Serial.println(port->available());
    if (port->available() > 20) {
      Lidar->BaudRate = CanFoc[i];
      Lidar->LidarFlag = true;
    }
    if (port->available() > 20)break;
  }
  ScanFlag = 1;
}


void getLidarDataFromCan(SoftwareSerial * port, TF * Lidar)
{
  static char i = 0;
  static int rx[17];
  //port->listen();
  while (port->available() > 0)
  {
    rx[i] = port->read();
    if (rx[0] != 0xAA)
    {
      i = 0;
    } else if (i == 17 )
    {
      i = 0;
      if (rx[16] == 0x7A)
      {
        Lidar->distance = rx[8] + rx[9] * 256;
        Lidar->strength = rx[10] + rx[11] * 256;
        Lidar->ID       = rx[7] + rx[6] * 256;
        if (Lidar->distance > 0 && Lidar->strength > 0) { //因为使用了软串口，数据会出现错误的情况
          Lidar->receiveComplete = true;
        }
      }
    } else {
      i++;
    }
  }
}



void SetCanFoc(SoftwareSerial * port, long int FOC)
{
  delay(10);
  port->print(ENTER_SET_MODE);
  delay(10);
  port->print(SET_CAN_FOC);
  port->println(FOC);
  delay(10);
  port->println(ENTER_DATA_MODE);
  delay(10);
}

void CanIni(SoftwareSerial * port, long int FOC)
{
  port->print(ENTER_SET_MODE);
  delay(10);
  port->print(SET_CAN_FOC);
  port->println(FOC);
  delay(10);
  port->println(ENTER_DATA_MODE);
  delay(10);
}
