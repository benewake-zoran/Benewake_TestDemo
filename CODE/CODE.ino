#include <MsTimer2.h>

#include "SSD1306_12864_DISPLAY.h"  //包含屏幕显示程序
#include "Lidar_IIC.h"              //IIC驱动程序
#include "Lidar_CAN.h"              //CAN驱动程序
#include "LC02.H"
#include "TF40.h"
#include "Lidar_Common.h"           //雷达数据以及通用变量
#include "key.h"                    //包含按键程序
#include "BW_TTL.h"                 //包含屏幕显示程序
#include "MODBUS.h"


U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  Serial.begin(9600);
  pinMode(SWITCH_A_PIN, INPUT_PULLUP);
  pinMode(SWITCH_B_PIN, INPUT_PULLUP);
  MsTimer2::set(KEY_TIME, key_scan);
  MsTimer2::start();

  u8g2.begin();
  if (WindowNum == WINDOW_BOOT) {
    Display_Boot();
    delay(1000);
    WindowNum = WINDOW_MENU;
    DisplayFlag = 1;
  }
}

void loop(void) {

  key_Service();

  if (WindowNum == WINDOW_MENU)
  {
    if (DisplayFlag) {
      DisplayFlag = 0;
      switch (FunctionMode)
      {
        case MODE_TTL_TF      : Display_Menu_P1_TTL() ; break;
        case MODE_TTL_TF_LC02 : Display_Menu_P2_TTL() ; break;
        case MODE_TTL_TF40    : Display_Menu_P3_TTL() ; break;
        case MODE_485_Modbus  : Display_Menu_P4_485() ; break;
        case MODE_CAN         : Display_Menu_P5_CAN() ; break;
        case MODE_IIC_TF      : Display_Menu_P6_IIC() ; break;
      }
    }
  }
  if (WindowNum == WINDOW_DATA)
  {
    if (FunctionMode == MODE_TTL_TF) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        // LidarDeviceScan(&Lidar);
        ScanUartFoc(&Lidar);
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {
        WindowNum = WINDOW_ERROR;
        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        while (!Lidar.receiveComplete) {
          getLidarData(&Lidar);
          if (Lidar.receiveComplete == true) {
            DisplayFlag = 1;
          }
        }
      }
    }
    if (FunctionMode == MODE_TTL_TF_LC02) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        Lidar.BaudRate = 115200;
        Serial.begin(Lidar.BaudRate);
        ScanFlag = 1;
        Lidar.LidarFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {
        WindowNum = WINDOW_ERROR;
        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        if (!Lidar.receiveComplete)
        {
          Serial.write(GetDatacmd, 5);
        } else
        {
          DisplayFlag = 1;
          delay(33);                       //延时33ms,雷达探测速率最快33ms
        }
      }
    }
    if (FunctionMode == MODE_TTL_TF40) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        ScanFlag = 1;
        Lidar.LidarFlag = true;
        Lidar.ID = 1;
        Lidar.BaudRate = 38400;
        Serial.begin(Lidar.BaudRate);
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {

        WindowNum = WINDOW_ERROR;

        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        delay(700);
        if (!Lidar.receiveComplete)
        {
          Serial.print(GET_TF40_SINGLE);
        } else
        {
          DisplayFlag = 1;
        }
      }
    }
    if (FunctionMode == MODE_485_Modbus) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        ScanModbusFOC_ID(&port_485, &Lidar);
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {
        WindowNum = WINDOW_ERROR;
        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        while (!Lidar.receiveComplete) {
          ModbusWrite(&port_485, &Lidar);
          ModbusRead(&port_485, &Lidar);
          if (Lidar.receiveComplete) {
            DisplayFlag = 1;
          }
        }
        delay(100);
      }
    }
    if (FunctionMode == MODE_CAN) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        port.begin(115200);
        ScanCanFoc(&port, &Lidar);
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {
        WindowNum = WINDOW_ERROR;
        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        if (!Lidar.receiveComplete) {
          getLidarDataFromCan(&port, &Lidar);
          if (Lidar.receiveComplete == true) {
            DisplayFlag = 1;
          }
        }
      }
    }
    if (FunctionMode == MODE_IIC_TF) {
      if (ScanFlag == 0  && Lidar.LidarFlag == false) {
        Wire.begin();        // join i2c bus (address optional for master)
        FoudIICDevice(&Lidar);
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == false) {
        WindowNum = WINDOW_ERROR;
        DisplayFlag = 1;
      }
      if (ScanFlag == 1  && Lidar.LidarFlag == true) {
        if (!Lidar.receiveComplete) {
          Get_LidarDatafromIIC(&Lidar);
          if (Lidar.receiveComplete == true) {
            DisplayFlag = 1;
          }
        }
      }
    }
  }
  if (WindowNum == WINDOW_DATA) {
    if (DisplayFlag == 1) {
      switch (FunctionMode) {
        case MODE_TTL_TF      : Display_BW_TTL(&Lidar) ; break;
        case MODE_TTL_TF_LC02 : Display_ODM_LC02(&Lidar) ; break;
        case MODE_TTL_TF40    : Display_ODM_TF40(&Lidar) ; break;
        case MODE_485_Modbus  : Display_BW_485(&Lidar) ; break;
        case MODE_CAN         : Display_BW_CAN(&Lidar) ; break;
        case MODE_IIC_TF      : Display_BW_IIC(&Lidar) ; break;
      }
      DisplayFlag = 0;
     }
  }
  if (WindowNum == WINDOW_ERROR) {
    if (DisplayFlag == 1) {
      DisplayFlag = 0;
      Display_Scan_Error(&Lidar);
    }
  }
  if (Lidar.receiveComplete) {
    // SerialPrint_Debug();
    Lidar.distance = 0;
    Lidar.receiveComplete = false;
  }
}

void SerialPrint_Debug() {
  Serial.print("DIST = ");
  Serial.print(Lidar.distance);
  Serial.print(" AMP = ");
  Serial.println(Lidar.strength);
}
void serialEvent() {
  if (FunctionMode == MODE_TTL_TF_LC02) {
    getLidarDataFromLC02(&Lidar);
  }
  if (FunctionMode == MODE_TTL_TF40 && Lidar.LidarFlag == true) {
    Lidar.distance = StringSplitIntAndChar();
    if (Lidar.distance > 0) {
      Lidar.receiveComplete = true;
    }
  }
}
