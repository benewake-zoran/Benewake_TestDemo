/**
 * @file     :LC02.h
 * @brief    :ODM产品LC02驱动程序
 * @details  :通过串口读取LC02的程序
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _LC02_H_
#define _LC02_H_

#include "common.h"                                //雷达数据以及通用变量
u8 GetDatacmd[5] = {0x55, 0xAA, 0x81, 0x00, 0xFA}; // 获取距离指令

void getLidarDataFromLC02(TF *lidar);

#endif //_LC02_H_
