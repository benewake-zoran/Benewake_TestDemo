/**
 * @file     :TF40.ino
 * @brief    :北醒TF40产品的驱动程序
 * @details  :北醒TF40产品的驱动程序
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "TF40.h"
/**
 * @brief 扫描TF40的波特率和ID函数
 * @param 扫描TF40的波特率和ID函数
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
void ScanTF40FOC_ID(TF *Lidar)
{
  u8 i = 0;
  unsigned int count = 0;
  for (i = 0; i < 5; i++)
  {
    Serial.begin(UartFoc[i]);
    Serial.print(GET_TF40_BAUD);
    delay(100);
    if (Serial.available() > 0)
    {
      Lidar->LidarFlag = true;
    }
    if (Lidar->LidarFlag)
      break;
  }
  ScanFlag = 1;
}

// void GetTF40BaudRate(TF* Lidar) {
//   unsigned char i = 0;
//   unsigned int count = 0;
//   for (i = 0; i < 5; i++) {
//     //Lidar->BaudRate = UartFoc[i];
//     Serial.begin(UartFoc[i]);
//     Serial.print("getbaud");
//     while (!statue && count < 100) {
//       count ++;
//       StringSplitIntAndChar();
//       delay(100);
//       if (zhengshu == UartFoc[i]) {
//         Serial.println("OK");
//         Lidar->BaudRate = zhengshu;
//         Lidar->LidarFlag = true;
//       }
//     } if (Lidar->LidarFlag)break;
//   }
//   count = 0;
//   statue = 0;
//   zhengshu = 0;
//   zifu = ""; //全局变量
// }

// int GetTF40ID() {
//   unsigned int count = 0;
//   int id = 0;
//   while (!statue && count < 200) {
//     count ++;
//     StringSplitIntAndChar();
//   }
//   if (zhengshu > 0) {
//     Lidar->ID = zhengshu;
//     Lidar->LidarFlag = true;
//     ScanFlag = 1;
//   }
//   statue = 0;
//   zhengshu = 0;
//   zifu = "";
// }

// void GetTF40Measure( TF* Lidar) {
//   unsigned int count = 0;
//   while (!statue && count < 100) {
//     count ++;
//     StringSplitIntAndChar(Lidar);
//   }
//   statue = 0;
//   if (zhengshu > 0) {
//     Lidar->distance = zhengshu;
//     Lidar->receiveComplete = true;
//   }
//   zhengshu = 0;
//   zifu = "";
// }

// 使用硬件串口接收时使用
#include "TF40.h"
/**
 * @brief 参数转换函数
 * @param 字符串转换成数字和字符
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
int StringSplitIntAndChar()
{
  String intchars = ""; // 局部变量
  String chars = "";
  int temp = 0;
  while (Serial.available() > 0)
  { // 一直等待数据接收完成 用if的话loop函数执行一次接受1个字符
    char inchar = Serial.read();
    if (isDigit(inchar)) // 是数字就执行
    {
      intchars += inchar; // 数字字符串
    }
    else
    {
      chars += inchar; // 字符串
    }
    delay(2);                    // 等待延时，不同波特率延时时间不一样，需要细调
    if (Serial.available() == 0) // 等待一段时间后缓冲区仍然没有收到数据,认为一帧数据已经接收完成,进入条件
    {
      temp = intchars.toInt(); // 将数字字符串转换成整数
      zhengshu = temp;
      return temp;
    }
  }
}
