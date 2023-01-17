/**
 * @file     :TTL.h
 * @brief    :硬件串口驱动程序
 * @details  :通过硬件串口读取雷达数据
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _TTL_H_
#define _TTL_H_

#include "common.h" //雷达数据以及通用变量

#define StartLidarScan 5000

void ScanUartFoc(TF *Lidar);
void getLidarData(TF *Lidar);

#endif //_TTL_H_
