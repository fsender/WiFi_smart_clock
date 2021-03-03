#include "tg2048.h"
void tg2048_setup() {
  quit_2048=0;
  if(life2048 == 1) return;
  randomSeed(millis());
  quit_2048=0;
  for(int8_t di=0;di<16;di++)
  num2048[di>>2][di&3]=0;
  for (int8_t a = 0; a < 2; a++)
  {
    int8_t x = random(0, 4);
    int8_t y = random(0, 4);
    if (num2048[x][y] == 0) num2048[x][y] = 2;
  }
  life2048 = 1;
  u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso26_tn);
    u8g2.setCursor(23, 30);
    u8g2.print(2048);
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(4, 45, "Press the key");
    u8g2.drawStr(20, 55, "to start");
  u8g2.sendBuffer();
  delay(500);
  while (digitalRead(TGOK)) yield();
  delay(90);
  time2048_begin=millis();
}

void tg2048_loop()
{
  int8_t f_game_over=0;
  while(1){
  uint32_t x_b = 0, y_b = 16, n;
  if (life2048 == 1) {
    u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_4x6_tr);
      u8g2.setCursor(104,12);
    u8g2.print((millis()-time2048_begin)/1000);
      u8g2.setCursor(12,12);
    u8g2.print("Score:");
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.setCursor(36,12);
     uint32_t g_score=0;
     for (int8_t i = 0; i < 4; i++)
        for (int8_t m = 0; m < 4; m++) g_score+=num2048[i][m]*num2048[i][m];
    u8g2.print(g_score);
    if(digitalRead(TGOK)==0) {
      u8g2.drawBox(0,0,11,16);
      u8g2.setColorIndex(0);
      u8g2.drawPixel(5,3);
      u8g2.drawHLine(4,4,3);
      u8g2.drawHLine(3,5,5);
      u8g2.drawPixel(5,12);
      u8g2.drawHLine(4,11,3);
      u8g2.drawHLine(3,10,5);
      u8g2.setColorIndex(1);
    }
      for (int8_t i = 0; i < 4; i++)
        for (int8_t m = 0; m < 4; m++){
          drawframe(x_b + 32 * i, y_b + 12 * m, 32, 12);
          if (num2048[i][m] != 0){
            if (num2048[i][m] / 1000 > 0)  n = 4;
            else if (num2048[i][m] / 100 > 0)  n = 3;
            else if (num2048[i][m] / 10 > 0)  n = 2;
            else  n = 1;
            u8g2.setCursor(x_b + 32 * i + 15 - n * 3, y_b + 12 * (m + 1) - 3);
            u8g2.print(num2048[i][m]);
          }
        }
    u8g2.sendBuffer();
    if (flag2048 == 1) {
      int8_t numFill=0;
        for(int8_t i=0;i<4;i++){
          for(int8_t j=0;j<4;j++){
            if(num2048[i][j]) numFill++;
          }
        }
        if(numFill==16) {
          f_game_over=1;
          flag2048 = 0;
        }
        else
          do{
            int8_t x = random(0, 4);
            int8_t y = random(0, 4);
            if (num2048[x][y] == 0)  {
              num2048[x][y] = ((1+(random(0,9)==5))<<1);
              flag2048=0;
            }
          }while(flag2048);
    }
    time2048_over=millis();
  }
  for (int8_t i = 0; i < 4; i++)
    for (int8_t m = 0; m < 4; m++)
    {
      if (num2048[i][m] == 2048)
      {
        u8g2.setColorIndex(0);
        u8g2.drawBox(8, 8, 94, 32);
        u8g2.setColorIndex(1);
          drawframe(10, 10, 60, 28);
          u8g2.setFont(u8g2_font_6x10_tf);
          u8g2.drawStr(15, 25, "YOU WIN");
          if (((time2048_over-time2048_begin)/1000)/ 1000 > 0)
              n = 4;
            else if (num2048[i][m] / 100 > 0)
              n = 3;
            else if (num2048[i][m] / 10 > 0)
              n = 2;
            else
              n = 1;
          u8g2.setCursor(42-n*3,35);
          u8g2.print((time2048_over-time2048_begin)/1000);
        u8g2.sendBuffer();
        delay(5000);
        life2048=0;
      }
    }
    if(f_game_over){
      u8g2.setFont(u8g2_font_6x10_tf);
        u8g2.setColorIndex(0);
      u8g2.drawBox(8, 8, 94, 32);
        u8g2.setColorIndex(1);
          drawframe(10, 10, 90, 28);
          u8g2.setFont(u8g2_font_6x10_tf);
          u8g2.drawStr(15, 25, "GAME OVER!");
          u8g2.sendBuffer();
          delay(3000);
        life2048=0;
    }
    if(quit_2048 || !life2048) return;
    yield();

    Control();
  }
}

void Control() {
  //switchVoltage = analogRead(0);
  int8_t getBtn=0;
  if(!digitalRead(TGLEFT)) {
    getBtn+=1;
    while(!digitalRead(TGLEFT)) {
      if(!digitalRead(TGRIGHT))
        quit_2048=1;
      yield();
    }
    delay(90);
  }
  if(!digitalRead(TGRIGHT)) {
    getBtn+=2;
    while(!digitalRead(TGRIGHT)) {
      if(!digitalRead(TGLEFT))
        quit_2048=1;
      yield();
    }
    delay(90);
  }
  if(quit_2048) return;
  if(!digitalRead(TGOK)) {
    getBtn+=4;
  }
  if (getBtn==5 )      //上
  {
    //移动数字
    for (int8_t i = 0; i < 4; i++)
    {
      for (int8_t m = 0; m < 4; m++)
      {
        if (num2048[i][m] == 0);
        flag2048 = 1;
      }
      //使用冒泡排序将0移到最后
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t m = 0; m < 3; m++)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i][m + 1];
            num2048[i][m + 1] = 0;
          }
        }
      }
      //相邻相同的数字相加
      for (int8_t m = 0; m < 3; m++)
      {
        if (num2048[i][m] == num2048[i][m + 1])
        {
          num2048[i][m] = num2048[i][m + 1] + num2048[i][m];
          num2048[i][m + 1] = 0;
          flag2048 = 1;
        }
      }
      //再次使用冒泡
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t m = 0; m < 3; m++)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i][m + 1];
            num2048[i][m + 1] = 0;
          }
        }
      }
    }
  }

  if (getBtn==6)       //下
  {
    for (int8_t i = 0; i < 4; i++)
    {
      for (int8_t m = 0; m < 4; m++)
      {
        if (num2048[i][m] == 0);
        flag2048 = 1;
      }
      //使用冒泡排序将0移到最前
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t m = 3; m > 0; m--)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i][m - 1];
            num2048[i][m - 1] = 0;
          }
        }
      }
      //再次相邻相同的数字相加
      for (int8_t m = 3; m > 0; m--)
      {
        if (num2048[i][m] == num2048[i][m - 1])
        {
          num2048[i][m] = num2048[i][m - 1] + num2048[i][m];
          num2048[i][m - 1] = 0;
          flag2048 = 1;
        }
      }
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t m = 3; m > 0; m--)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i][m - 1];
            num2048[i][m - 1] = 0;
          }
        }
      }
    }
  }

  if (getBtn==1)                               //左
  {
    for (int8_t m = 0; m < 4; m++)
    {
      for (int8_t i = 0; i < 4; i++)
      {
        if (num2048[i][m] == 0);
        flag2048 = 1;
      }
      //使用冒泡排序将0移到最后
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t i = 0; i < 3; i++)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i + 1][m ];
            num2048[i + 1][m ] = 0;
          }
        }
      }
      //相邻相同的数字相加
      for (int8_t i = 0; i < 3; i++)
      {
        if (num2048[i][m] == num2048[i + 1][m])
        {
          num2048[i][m] = num2048[i + 1][m] + num2048[i][m];
          num2048[i + 1][m ] = 0;
          flag2048 = 1;
        }
      }
      //再次使用冒泡
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t i = 0; i < 3; i++)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i + 1][m ];
            num2048[i + 1][m ] = 0;
          }
        }
      }
    }
  }

  if (getBtn==2)       //右
  {

    for (int8_t m = 0; m < 4; m++)
    {
      for (int8_t i = 0; i < 4; i++)
      {
        if (num2048[i][m] == 0);
        flag2048 = 1;
      }
      //使用冒泡排序将0移到最后
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t i = 3; i > 0; i--)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i - 1][m ];
            num2048[i - 1][m ] = 0;
          }
        }
      }
      //相邻相同的数字相加
      for (int8_t i = 3; i > 0; i--)
      {
        if (num2048[i][m] == num2048[i - 1][m])
        {
          num2048[i][m] = num2048[i - 1][m] + num2048[i][m];
          num2048[i - 1][m ] = 0;
          flag2048 = 1;
        }
      }
      //再次使用冒泡
      for (int8_t j = 0; j < 3; j++)
      {
        for (int8_t i = 3; i > 0; i--)
        {
          if (num2048[i][m] == 0)
          {
            num2048[i][m] = num2048[i - 1][m ];
            num2048[i - 1][m ] = 0;
          }
        }
      }
    }
  }
  }
  //   if ( switchVoltage > 0 && switchVoltage < 180 )
