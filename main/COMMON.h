#ifndef _COMMON_H_
#define _COMMON_H_

#include <SoftwareSerial.h> //Arduino的软串口
#include <U8g2lib.h>        //显示使用的字符模块

/******* SoftwareSerial port(RX, TX);*******/
SoftwareSerial port(5, 4);
SoftwareSerial port_485(10, 9);

#define BENEWAKE_LOGO "Benewake"
#define SOFTWARE_VER "Demo A5"

typedef struct
{
  int distance = 0;
  int strength = 0;
  int ID = 0; // 雷达 ID

  long int BaudRate = 0;

  boolean LidarFlag = false;
  // boolean LidarOnOffFlag = false;
  boolean receiveComplete = false;
  boolean IO = 0;
} TF;
TF Lidar;

static long int CanFoc[7] = {250000, 125000, 800000, 500000, 1000000, 400000, 100000};
long int UartFoc[6] = {9600, 115200, 19200, 38400, 57600};

bool DisplayFlag = false; // 是否需要刷新显示的标志
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

#define MODE_TTL_TF 1
#define MODE_TTL_TF_LC02 2
#define MODE_TTL_TF40 3
#define MODE_485_Modbus 4
#define MODE_CAN 5
#define MODE_IIC_TF 6
#define MODE_IO_TF 7
u8 FunctionMode = 1;

#define WINDOW_BOOT 1
#define WINDOW_MENU 2
#define WINDOW_DATA 3
#define WINDOW_ERROR 4

u8 WindowNum = 1;
boolean ScanFlag = 0; // 0代表还未扫描,1代表已经扫描结束

#endif //_COMMON_H_
