void Display_Boot()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(10, 15, "Benewake");
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(10, 50, "Demo A");
  } while ( u8g2.nextPage() );
}

void Display_Menu_P1_TTL()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P1-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF series");
  } while ( u8g2.nextPage() );
}

void Display_Menu_P2_TTL()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P2-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF-LC02");
  } while ( u8g2.nextPage() );
}

void Display_Menu_P3_TTL()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P3-TTL-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF40");
  } while ( u8g2.nextPage() );
}

void Display_Menu_P4_485()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P4-485-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "Modbus");
  } while ( u8g2.nextPage() );
}


void Display_Menu_P5_CAN()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P5-CAN-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF-i_TF03");
  } while ( u8g2.nextPage() );
}

void Display_Menu_P6_IIC()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0, 15, "P6-IIC-PORT");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.drawStr(0, 56, "TF series");
  } while ( u8g2.nextPage() );
}

//北醒485版本数据更新显示界面
void Display_BW_485(TF* Lidar)
{
  u8g2.firstPage();
  do {
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
  } while ( u8g2.nextPage() );
}

//北醒485版本数据更新显示界面
void Display_BW_CAN(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate/1000);
    u8g2.print("K");
    u8g2.setCursor(70, 15);
    u8g2.print("ID:0x");
    u8g2.print(Lidar->ID, HEX);
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while ( u8g2.nextPage() );
}


//ODM LC02显示界面
void Display_ODM_LC02(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(10, 56);
    u8g2.print(Lidar->distance);
  } while ( u8g2.nextPage() );
}

//ODM TF40显示界面
void Display_ODM_TF40(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    u8g2.setCursor(70, 15);
    u8g2.print("ID:0x");
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(10, 56);
    u8g2.print(Lidar->distance);
  } while ( u8g2.nextPage() );
}

//北醒串口通用版本数据更新显示界面
void Display_BW_TTL(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("F:");
    u8g2.print(Lidar->BaudRate);
    //    u8g2.setCursor(70, 15);
    //    u8g2.print("S:");
    u8g2.setCursor(75, 56);
    //u8g2.print("S:");
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while ( u8g2.nextPage() );
}
//北醒IIC通用版本数据更新显示界面
void Display_BW_IIC(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("ID:0x");
    u8g2.print(Lidar->ID, HEX);
    u8g2.setCursor(75, 56);
    u8g2.print(Lidar->strength);
    u8g2.setFont(u8g2_font_fub20_tf);
    u8g2.setCursor(0, 56);
    u8g2.print(Lidar->distance);
  } while ( u8g2.nextPage() );
}

//显示扫描错误显示界面
void Display_Scan_Error(TF* Lidar)
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("ERROR");
    u8g2.setCursor(0, 40);
    u8g2.print("Can't find lidar");
    u8g2.setCursor(0, 55);
    u8g2.print("Retry again!!!");
  } while ( u8g2.nextPage() );
}
