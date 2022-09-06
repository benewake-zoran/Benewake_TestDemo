void ScanModbusFOC_ID(SoftwareSerial* port, TF* Lidar)
{
  u8 i = 0;
  int count = 0;
  for (i = 0; i < 5; i++) {
    port->begin(UartFoc[i]);
    for (int j = 1; j < 51; j++) {
      Serial.println(j);
      Lidar->ID = j;
      ModbusWrite(port, Lidar);
      delay(20);
      if (port->available() > 5) break;
    }if (port->available() > 5) break;
  }
  if (port->available() > 5) {
    Lidar->BaudRate = UartFoc[i];
    Lidar->LidarFlag = true;
  }
  ScanFlag = 1;
}

void ModbusRead(SoftwareSerial * port, TF * Lidar)
{
  unsigned int i = 0;
  unsigned int crc16;  //校验位
  while (port->available() > 0) {
    Modbus_Read[i] = port->read();
    i++;
  }
  delay(1);
  if (port->available() == 0) //1.5个字符时间后缓冲区仍然没有收到数据,认为一帧数据已经接收完成,进入条件
  {
    if (Modbus_Read[0] == Lidar->ID && Modbus_Read[1] == FUNCHTION_ID && Modbus_Read[2] == 0x04) {
      crc16 = ((Modbus_Read[7] << 8) | Modbus_Read[8]);
      if (calculateCRC(&Modbus_Read[0], 7) == crc16) {
        Lidar->distance = Modbus_Read[3] * 256 +  Modbus_Read[4];
        Lidar->strength = Modbus_Read[5] * 256 +  Modbus_Read[6];
        Lidar->receiveComplete = true;
      }
    }
  }
}


void ModbusWrite(SoftwareSerial * port, TF * Lidar)
{
  unsigned int crc16;  //校验位
  Modbus_Write[0] = Lidar->ID;
  Modbus_Write[1] = FUNCHTION_ID;
  Modbus_Write[2] = 0x00;
  Modbus_Write[3] = REGISTADRESS;
  Modbus_Write[4] = 0x00;
  Modbus_Write[5] = DATE_READLEN;
  crc16 = calculateCRC(&Modbus_Write[0], 6); //计算校验值
  Modbus_Write[6] = crc16 >> 8;  //填写校验位
  Modbus_Write[7] = crc16 & 0xFF;

  port->write(&Modbus_Write[0], 8);
}

//CRC校验函数
//参数1:待校验数组的起始地址
//参数2:待校验数组的长度
//返回值CRC校验结果,16位,低字节在前
unsigned int calculateCRC(unsigned char* _regs, unsigned char arraySize)
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < arraySize; i++)
  {
    temp = temp ^ *(_regs + i);
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  temp2 = temp >> 8;
  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp;
}
