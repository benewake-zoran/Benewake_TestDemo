/**
 * @file     :TTL.ino
 * @brief    :硬件串口驱动程序
 * @details  :通过硬件串口读取雷达数据
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "TTL.h"
/**
 * @brief 扫描雷达波特率
 * @param 扫描雷达波特率
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ScanUartFoc(TF *Lidar)
{
  u8 i = 0;
  for (i = 0; i < 6; i++)
  {
    Lidar->BaudRate = UartFoc[i];
    Serial.begin(UartFoc[i]);
    delay(100);
    for (int j = 0; j < 50; j++)
    {
      getLidarData(Lidar);
      if (Lidar->receiveComplete)
        break;
    }
    if (Lidar->receiveComplete)
      break;
  }
  if (Lidar->receiveComplete)
  {
    Lidar->LidarFlag = true;
  }
  ScanFlag = 1;
}
/**
 * @brief 获取雷达数据
 * @param 获取雷达数据
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void getLidarData(TF *Lidar)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  while (Serial.available() > 0)
  {
    rx[i] = Serial.read();
    if (rx[0] != 0x59)
    {
      i = 0;
    }
    else if (i == 1 && rx[1] != 0x59)
    {
      i = 0;
    }
    else if (i == 8)
    {
      for (j = 0; j < 8; j++)
      {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256))
      {
        Lidar->distance = rx[2] + rx[3] * 256;
        Lidar->strength = rx[4] + rx[5] * 256;
        Lidar->receiveComplete = true;
      }
      i = 0;
    }
    else
    {
      i++;
    }
  }
}
