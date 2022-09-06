#ifndef _TF40_H_
#define _TF40_H_

#define GET_TF40_BAUD     "getbaud"
#define GET_TF40_ADDR     "getaddr"
#define GET_TF40_SINGLE   "single"   //单次测量
#define GET_TF40_CONTIS   "contis"   //多次测量

boolean GetBaudRate = false;

u16 zhengshu;
String  zifu = ""; //全局变量
bool statue = 0;

#endif  //_TF40_H_
