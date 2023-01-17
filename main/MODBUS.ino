/**
 * @file     :modbus.ino
 * @brief    :模拟Modbus协议
 * @details  :模拟Modbus协议并驱动读取北醒雷达数据，包含TFmini-i,TF02-i,TF03
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "MODBUS.h"

/**
 * @brief 扫描Modbus设备的波特率和站号
 * @param 使用软串口扫描Modbus设备的波特率和站号
 * @param[in] SoftwareSerial 软串口
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ScanModbusFOC_ID(SoftwareSerial *port, TF *Lidar)
{
  u8 i = 0;
  int count = 0;
  for (i = 0; i < 5; i++)
  {
    port->begin(UartFoc[i]);
    for (int j = 1; j < 51; j++)
    {
      Serial.println(j);
      Lidar->ID = j;
      ModbusWrite(port, Lidar);
      delay(20);
      if (port->available() > 5)
        break;
    }
    if (port->available() > 5)
      break;
  }
  if (port->available() > 5)
  {
    Lidar->BaudRate = UartFoc[i];
    Lidar->LidarFlag = true;
    Lidar->receiveComplete = false;
  }
  ScanFlag = 1;
}
/**
 * @brief Modbus读取函数
 * @param 通过Modbus读取
 * @param[in] SoftwareSerial 软串口
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ModbusRead(SoftwareSerial *port, TF *Lidar)
{
  unsigned int i = 0;
  unsigned int crc16; // 校验位
  port->listen();
  while (port->available() > 0)
  {
    Modbus_Read[i] = port->read();
    i++;
  }
  delay(1);
  if (port->available() == 0) // 1.5个字符时间后缓冲区仍然没有收到数据,认为一帧数据已经接收完成,进入条件
  {
    if (Modbus_Read[0] == Lidar->ID && Modbus_Read[1] == FUNCHTION_ID && Modbus_Read[2] == 0x04)
    {
      crc16 = ((Modbus_Read[7] << 8) | Modbus_Read[8]);
      Serial.println("OK");
      if (calculateCRC(&Modbus_Read[0], 7) == crc16)
      {
        Lidar->distance = Modbus_Read[3] * 256 + Modbus_Read[4];
        Lidar->strength = Modbus_Read[5] * 256 + Modbus_Read[6];
        Lidar->receiveComplete = true;
      }
    }
  }
}
/**
 * @brief Modbus写函数
 * @param 通过Modbus写
 * @param[in] SoftwareSerial 软串口
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ModbusWrite(SoftwareSerial *port, TF *Lidar)
{
  unsigned int crc16; // 校验位
  Modbus_Write[0] = Lidar->ID;
  Modbus_Write[1] = FUNCHTION_ID;
  Modbus_Write[2] = 0x00;
  Modbus_Write[3] = REGISTADRESS;
  Modbus_Write[4] = 0x00;
  Modbus_Write[5] = DATE_READLEN;
  crc16 = calculateCRC(&Modbus_Write[0], 6); // 计算校验值
  Modbus_Write[6] = crc16 >> 8;              // 填写校验位
  Modbus_Write[7] = crc16 & 0xFF;

  port->write(&Modbus_Write[0], 8);
}
/**
 * @brief CRC校验函数
 * @param 返回值CRC校验结果,16位,低字节在
 * @param[in] _regs 待校验数组的起始地址
 * @param[out] arraySize 待校验数组的长度
 * @return 无
 * @retval 无
 */

unsigned int calculateCRC(unsigned char *_regs, unsigned char arraySize)
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
