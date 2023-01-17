/**
 * @file     :DISPLAY.h
 * @brief    :显示程序
 * @details  :通过SSD1306_12864_IIC显示
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#ifndef _SSD1306_12864_DISPLAY_H_
#define _SSD1306_12864_DISPLAY_H_

#include <Arduino.h>
#include "common.h" //雷达数据以及通用变量

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

void Display_Boot();
void Display_Menu_P1_TTL();
void Display_Menu_P2_TTL();
void Display_Menu_P3_TTL();
void Display_Menu_P4_485();
void Display_Menu_P5_CAN();
void Display_Menu_P6_IIC();
void Display_Menu_P7_IO();
void Display_BW_485(TF *Lidar);
void Display_BW_CAN(TF *Lidar);
void Display_ODM_LC02(TF *Lidar);
void Display_ODM_TF40(TF *Lidar);
void Display_BW_TTL(TF *Lidar);
void Display_BW_IIC(TF *Lidar);
void Display_BW_IO(TF *Lidar);
void Display_Scan_Error(TF *Lidar);

#endif //_SSD1306_12864_DISPLAY_H_
