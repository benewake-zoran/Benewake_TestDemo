/**
 * @file     :LC02.c
 * @brief    :ODM产品LC02驱动程序
 * @details  :通过串口读取LC02的程序
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "LC02.h"
/***************************************
 -  通讯协议：
 -  2 byte : 帧头 0x55 0xAA
 -  1 byte : 功能码 (详细参考使用说明) 例：0x81 获取距离值 单位:mm
 -  1 byte : 后面参数的长度
 -  N byte : 设定参数
 -  1 byte : 帧尾 0xFA
 -  ***************************************
 -  例：获取距离值
 -  Arduino 发送：55 AA 81 00 FA
 -  TOF模组回复 ： 55 AA 81 03 01 55 00 FA
 **************************************/
/**
 * @brief 获取LC02的数据
 * @param 通过硬件串口获取LC02的数据
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void getLidarDataFromLC02(TF *lidar)
{
  static char i = 0;
  static int rx[8];
  if (Serial.available())
  {
    rx[i] = Serial.read();
    if (rx[0] != 0x55)
    {
      i = 0;
    }
    else if (i == 1 && rx[1] != 0xAA)
    {
      i = 0;
    }
    else if (i == 7)
    {
      i = 0;
      if (rx[7] == 0xFA)
      {
        lidar->distance = rx[5] + rx[4] * 256;
        lidar->receiveComplete = true;
      }
    }
    else
    {
      i++;
    }
  }
}
