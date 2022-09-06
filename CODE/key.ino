void key_scan()//按键扫描函数 放在定时中断里
{
  if (digitalRead(SWITCH_A_PIN) == HIGH) //IO是高电平，说明两个按键没有全部被按下，这时要及时清零一些标志位
  {
    ucKeyLock1 = 0; //按键自锁标志清零
    uiKeyTimeCnt1 = 0; //按键去抖动延时计数器清零，此行非常巧妙，是我实战中摸索出来的。
    if (ucShortTouchFlag1 == 1) //短按触发标志
    {
  //    Serial.println("-------");
      ucShortTouchFlag1 = 0;
      ucKeySec = 1;  //触发一号键的短按
    }
  }
  else if (ucKeyLock1 == 0) //有按键按下，且是第一次被按下
  {
    uiKeyTimeCnt1++; //累加定时中断次数
    if (uiKeyTimeCnt1 > const_key_time_short1)
    {
      ucShortTouchFlag1 = 1; //激活按键短按的有效标志
    }
    if (uiKeyTimeCnt1 > const_key_time_long1)
    {
      ucShortTouchFlag1 = 0; //清除按键短按的有效标志

      uiKeyTimeCnt1 = 0;
      ucKeyLock1 = 1; //自锁按键置位,避免一直触发

      ucKeySec = 2;  //触发1号键的长按
    }
  }

  if (digitalRead(SWITCH_B_PIN) == HIGH) //IO是高电平，说明两个按键没有全部被按下，这时要及时清零一些标志位
  {
    ucKeyLock2 = 0; //按键自锁标志清零
    uiKeyTimeCnt2 = 0; //按键去抖动延时计数器清零，此行非常巧妙，是我实战中摸索出来的。
    if (ucShortTouchFlag2 == 1) //短按触发标志
    {
      ucShortTouchFlag2 = 0;
      ucKeySec = 3;  //触发2号键的短按
    }
  }
  else if (ucKeyLock2 == 0) //有按键按下，且是第一次被按下
  {
    uiKeyTimeCnt2++; //累加定时中断次数
    if (uiKeyTimeCnt2 > const_key_time_short2)
    {
      ucShortTouchFlag2 = 1; //激活按键短按的有效标志
    }

    if (uiKeyTimeCnt2 > const_key_time_long2)
    {
      ucShortTouchFlag2 = 0; //清除按键短按的有效标志

      uiKeyTimeCnt2 = 0;
      ucKeyLock2 = 1; //自锁按键置位,避免一直触发
      ucKeySec = 4;  //触发2号键的长按
    }
  }
}

void key_Service() {
  if (WindowNum == WINDOW_MENU) {
    if (ucKeySec != 0) {
      switch (ucKeySec) {
        case 1: FunctionMode++;  break;
        case 2: break;
        case 3: WindowNum = WINDOW_DATA;MsTimer2::stop(); break;
        case 4: break;
        default: break;
      }
      if (FunctionMode > FuncNum)FunctionMode = 1;  
      DisplayFlag = 1;
      ucKeySec = 0;
    }
  }
}

//按键测试
//void key_Service_Test() {
//  if (ucKeySec != 0) {
//    Serial.println(ucKeySec);
//  }
//  if (ucKeySec == 1) {
//    Serial.println("按键1短按");
//  } else if (ucKeySec == 2) {
//    Serial.println("按键1长按");
//  } else if (ucKeySec == 3) {
//    Serial.println("按键2短按");
//  } else if (ucKeySec == 4) {
//    Serial.println("按键2长按");
//  }
//  ucKeySec = 0;
//}
