/**
 * @file     :IIC.h
 * @brief    :IIC接口程序
 * @details  :通过Arduino的硬件IIC对北醒IIC接口雷达进行数据读取
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.16
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _IIC_H_
#define _IIC_H_
#include <Wire.h>
#include "common.h" //雷达数据以及通用变量

u8 cmd[5] = {0x5a, 0x05, 0x00, 0x01, 0x60}; // Get measure value cmd

void FoudIICDevice(TF *Lidar);
void Get_LidarDatafromIIC(TF *Lidar);

#endif //_IIC_H_
