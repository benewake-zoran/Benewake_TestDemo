/**
 * @file     :DISPLAY.ino
 * @brief    :显示程序
 * @details  :通过SSD1306_12864_IIC显示
 * @author   :benewake.zoran
 * @version  :beta 1.0
 * @date     :2023.01.17
 * @copyright:北醒北京（光子）科技有限公司
 */
#include "DISPLAY.h"

/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Boot()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(10, 15, BENEWAKE_LOGO);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(10, 50, SOFTWARE_VER);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P1_TTL()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P1-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF series");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P2_TTL()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P2-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF-LC02");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P3_TTL()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P3-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF40");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P4_485()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P4-485-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "Modbus");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P5_CAN()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P5-CAN-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF-i_TF03");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P6_IIC()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P6-IIC-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF series");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return 无
 * @retval 无
 */
void Display_Menu_P7_IO()
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P7-IO-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF series");
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 北醒485版本数据更新显示界面
void Display_BW_485(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    u8g2.setCursor(70, 15);
    u8g2.print("ID:0x");
    u8g2.print(Lidar->ID, HEX);
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 北醒485版本数据更新显示界面
void Display_BW_CAN(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate / 1000);
    u8g2.print("K");
    u8g2.setCursor(70, 15);
    u8g2.print("ID:0x");
    u8g2.print(Lidar->ID, HEX);
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] 无
 * @return TF 雷达参数，函数成功后用来更新
 * @retval 无
 */
// ODM LC02显示界面
void Display_ODM_LC02(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(10, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// ODM TF40显示界面
void Display_ODM_TF40(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    u8g2.setCursor(70, 15);
    u8g2.print("ID:0x");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(10, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 北醒串口通用版本数据更新显示界面
void Display_BW_TTL(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    //    u8g2.setCursor(70, 15);
    //    u8g2.print("S:");
    u8g2.setCursor(75, 56);
    // u8g2.print("S:");
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 北醒IIC通用版本数据更新显示界面
void Display_BW_IIC(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("ID:0x");
    u8g2.print(Lidar->ID, HEX);
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while (u8g2.nextPage());
}
/**
 * @brief 启动界面
 * @param 开机启动显示北醒LOGO和版本号
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 北醒IIC通用版本数据更新显示界面
void Display_BW_IO(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print("IO:");
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->IO);
  } while (u8g2.nextPage());
}
/**
 * @brief 错误显示函数
 * @param 显示扫描错误显示界面
 * @param[in] 无
 * @param[out] TF 雷达参数，函数成功后用来更新
 * @return 无
 * @retval 无
 */
// 显示扫描错误显示界面
void Display_Scan_Error(TF *Lidar)
{
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("ERROR");
    u8g2.setCursor(0, 40);
    u8g2.print("Can't find lidar");
    u8g2.setCursor(0, 55);
    u8g2.print("Retry again!!!");
  } while (u8g2.nextPage());
}
