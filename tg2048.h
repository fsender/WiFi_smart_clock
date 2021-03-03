#ifndef _CTG_TG2048
#define _CTG_TG2048

#include "U8g2lib.h"
#include "ctg_stack.h"

extern U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2;

#define TGLEFT BtnL//定义方向键上为Arduino上的BtnR号引脚
#define TGRIGHT BtnR//定义方向键上为Arduino上的BtnR号引脚
#define TGOK BtnM//定义方向键上为Arduino上的BtnR号引脚
//#define TGPAUSE 47//定义方向键上为Arduino上的D9号引脚(暂时不用）
#define TGSWITCHTIME 30

static uint32_t  flag2048,life2048=0;                      //按键
static uint32_t  num2048[4][4] ;
static uint32_t time2048_begin,time2048_over;
static uint8_t quit_2048=0;

void tg2048_setup();
void tg2048_loop() ;
void Control();

#endif
