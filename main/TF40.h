/**
 * @file     :TF40.h
 * @brief    :北醒TF40产品的驱动程序
 * @details  :北醒TF40产品的驱动程序
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */

#ifndef _TF40_H_
#define _TF40_H_
#include "common.h" //雷达数据以及通用变量

#define GET_TF40_BAUD "getbaud"
#define GET_TF40_ADDR "getaddr"
#define GET_TF40_SINGLE "single" // 单次测量
#define GET_TF40_CONTIS "contis" // 多次测量

boolean GetBaudRate = false;

u16 zhengshu;
String zifu = ""; // 全局变量
bool statue = 0;

int StringSplitIntAndChar();

#endif //_TF40_H_
