//-------------- Createen Studios --------------//
//2021.1.3
//A library to make characters alive!
//Remade from U8G2 offical example: Shennong.ino

#ifndef _CTG_SCROLL_STRING
#define _CTG_SCROLL_STRING

#define FULL_BUFFERED

//Includings:
#include "Arduino.h"
#include "U8g2lib.h"
#include <FS.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//constants
#define BUFLEN 2048
#define LINE_BUFLEN 64
#define _FONT u8g2_font_wqy12_t_gb2312
#define getchs_max 60
#define SCROLL_DELTA 1
#define SCROLL_DELAY 100
#define SCROLL_BEGIN_LINES 3
#define MOTION_ON
extern U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2;

void drawframe(uint8_t x,uint8_t y,uint8_t w,uint8_t h);
uint16_t procline(const char *st,uint8_t *lfeed,int perline);
uint16_t procfile(File *fp,uint8_t *lfeed,int perline);
void scroll_string(const char *c_str0,uint8_t readFile=0,File *fp=NULL);
int16_t getchs (char *tbuff,uint16_t maxlen=LINE_BUFLEN);
void drawKey(const char c,uint8_t x,uint8_t y,uint8_t st=0);
uint8_t switchMode(const uint8_t spin,const uint8_t dtime=25);
uint8_t controlBoard(const char * txt[]);
int16_t slider(const char *title,int16_t maxval=100,int16_t minval=0);

uint8_t listdraw(const char *title,const char *items[],uint8_t numitem);
void drawList(const char*s1,const char*s2,const char*s3,const char*s4,uint32_t delayms=0);
void drawLists(const char*s1,const char*s2,const char*s3,const char*s4,
const uint8_t way,const uint8_t cn,const uint8_t al,uint8_t delta=0);


#endif
