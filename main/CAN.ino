/**
 * @file     :CAN.ino
 * @brief    :TTL转CAN板的驱动程序
 * @details  :通过TTL转CAN板与北醒CAN接口雷达通信，包含TFmini-i,TF02-i,TF03
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.16
 * @copyright:北醒北京（光子）科技有限公司
 */

#include "can.h"

/**
 * @brief 扫描CAN接口波特率函数
 * @param 通过TTL转CAN板的特性，如果TTL口没有数据,则CAN接口波特率不正确
 * @param[in] SoftwareSerial 软串口
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ScanCanFoc(SoftwareSerial *port, TF *Lidar)
{
  u8 i = 0;
  for (i = 0; i < 7; i++)
  {
    SetCanFoc(port, CanFoc[i]);
    delay(100);
    while (port->available() > 0)
    {
      port->read();
    }
    delay(100);
    // Serial.println(port->available());
    if (port->available() > 20)
    {
      Lidar->BaudRate = CanFoc[i];
      Lidar->LidarFlag = true;
    }
    if (port->available() > 20)
      break;
  }
  ScanFlag = 1;
}
/**
 * @brief 获取雷达数据的函数
 * @param 根据雷达CAN接口协议，获取雷达的数据
 * @param[in] SoftwareSerial 软串口
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void getLidarDataFromCan(SoftwareSerial *port, TF *Lidar)
{
  static char i = 0;
  static int rx[17];
  // port->listen();
  while (port->available() > 0)
  {
    rx[i] = port->read();
    if (rx[0] != 0xAA)
    {
      i = 0;
    }
    else if (i == 17)
    {
      i = 0;
      if (rx[16] == 0x7A)
      {
        Lidar->distance = rx[8] + rx[9] * 256;
        Lidar->strength = rx[10] + rx[11] * 256;
        Lidar->ID = rx[7] + rx[6] * 256;
        if (Lidar->distance > 0 && Lidar->strength > 0)
        { // 因为使用了软串口，数据会出现错误的情况
          Lidar->receiveComplete = true;
        }
      }
    }
    else
    {
      i++;
    }
  }
}
/**
 * @brief 设置TTL转CAN板波特率
 * @param 根据雷达CAN接口协议，获取雷达的数据
 * @param[in] SoftwareSerial 软串口
 * @param[out]
 * @return 无
 * @retval 无
 */
void SetCanFoc(SoftwareSerial *port, long int FOC)
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
/**
 * @brief 初始化TTL转CAN板
 * @param 根据雷达CAN接口协议，获取雷达的数据
 * @param[in] SoftwareSerial 软串口
 * @param[out]
 * @return 无
 * @retval 无
 */
void CanIni(SoftwareSerial *port, long int FOC)
{
  port->print(ENTER_SET_MODE);
  delay(10);
  port->print(SET_CAN_FOC);
  port->println(FOC);
  delay(10);
  port->println(ENTER_DATA_MODE);
  delay(10);
}
