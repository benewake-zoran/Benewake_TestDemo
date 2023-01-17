/**
 * @file     :can.h
 * @brief    :TTL转CAN板的驱动程序
 * @details  :通过TTL转CAN板与北醒CAN接口雷达通信，包含TFmini-i,TF02-i,TF03
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.16
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _LIDAR_CAN_H_
#define _LIDAR_CAN_H_

// #include <SoftwareSerial.h>

#include "common.h" //雷达数据以及通用变量
/*TTL转CAN板的通信协议*/
#define ENTER_SET_MODE "+++"       // 进入配置模式
#define ENTER_DATA_MODE "ATO"      // 进入数据模式
#define SET_CAN_FOC "AT+CAN_BAUD=" // 设置波特率

void ScanCanFoc(SoftwareSerial *port, TF *Lidar);
void getLidarDataFromCan(SoftwareSerial *port, TF *Lidar);

#endif //_LIDAR_CAN_H_
