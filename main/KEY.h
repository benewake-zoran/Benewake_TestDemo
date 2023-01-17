/**
 * @file     :key.h
 * @brief    :按键驱动程序
 * @details  :按键驱动程序
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _KEY_H_
#define _KEY_H_

#include "common.h" //雷达数据以及通用变量
#define SWITCH_A_PIN 3
#define SWITCH_B_PIN 2
#define const_key_time 50 // 按键去抖动延时的时间

#define FuncNum 7 // 定义功能界面数量

unsigned char KeyLock = 0;
unsigned int KeyTimeCnt = 0;

/* 注释一：
 * 调整抖动时间阀值的大小，可以更改按键的触发灵敏度。
 * 去抖动的时间本质上等于累计定时中断次数的时间。
 */

#define const_key_time_short1 10 // 短按的按键去抖动延时的时间
#define const_key_time_long1 100 // 长按的按键去抖动延时的时间

#define const_key_time_short2 10 // 短按的按键去抖动延时的时间
#define const_key_time_long2 200 // 长按的按键去抖动延时的时间

#define KEY_TIME 10 // 定时器扫描时间

unsigned char ucKeySec = 0; // 被触发的按键编号

unsigned int uiKeyTimeCnt1 = 0;      // 按键去抖动延时计数器
unsigned char ucKeyLock1 = 0;        // 按键触发后自锁的变量标志
unsigned char ucShortTouchFlag1 = 0; // 短按的触发标志

unsigned int uiKeyTimeCnt2 = 0;      // 按键去抖动延时计数器
unsigned char ucKeyLock2 = 0;        // 按键触发后自锁的变量标志
unsigned char ucShortTouchFlag2 = 0; // 短按的触发标志

void key_scan();
void key_Service();

#endif //_KEY_H_
