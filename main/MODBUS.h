/**
 * @file     :modbus.h
 * @brief    :TTL转CAN板的驱动程序
 * @details  :通过TTL转CAN板与北醒CAN接口雷达通信，包含TFmini-i,TF02-i,TF03
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */

#ifndef _MODBUS_H_
#define _MODBUS_H_

#include "common.h" //雷达数据以及通用变量

unsigned char Modbus_Write[8]; // Get measure value cmd
unsigned char Modbus_Read[9];  // Get measure value cmd

#define FUNCHTION_ID 0x03
#define REGISTADRESS 0x00
#define DATE_READLEN 0x02

#define ModbusScan 5
void ScanModbusFOC_ID(SoftwareSerial *port, TF *Lidar);
void ModbusRead(SoftwareSerial *port, TF *Lidar);
void ModbusWrite(SoftwareSerial *port, TF *Lidar);

#endif //_MODBUS_H_
