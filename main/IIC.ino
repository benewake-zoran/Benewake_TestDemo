/**
 * @file     :IIC.c
 * @brief    :IIC接口程序
 * @details  :通过Arduino的硬件IIC对北醒IIC接口雷达进行数据读取
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "IIC.h"
/**
 * @brief 扫描IIC接口地址
 * @param 通过轮询的方式扫描IIC地址
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void FoudIICDevice(TF *Lidar)
{
  for (u8 i = 1; i < 127; i++)
  {
    if (i == 60)
      continue;
    Wire.beginTransmission(i); // （和地址i连接）
    int error = Wire.endTransmission();
    if (error == 0)
    {
      Lidar->LidarFlag = true;
      Lidar->ID = i;
    }
  }
  ScanFlag = 1;
}
/**
 * @brief 获取雷达距离数据和信号强度数据
 * @param 通过雷达指令获取雷达数据
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void Get_LidarDatafromIIC(TF *Lidar)
{
  char i = 0;
  char j = 0;
  byte rx_buf[9] = {0};
  Wire.beginTransmission(Lidar->ID); // Begin a transmission to the I2C Slave device with the given address.
  for (j = 0; j < 5; j++)
  {
    Wire.write(cmd[j]);
  }
  Wire.endTransmission();         // Send a START Sign
  Wire.requestFrom(Lidar->ID, 9); // request 7 bytes from slave device address

  while (Wire.available())
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
