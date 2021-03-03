#ifndef _CTG_SPACETRASH
#define _CTG_SPACETRASH

#include "U8g2lib.h"
#include "ctg_stack.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

extern U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2;

/* object types */
struct _st_ot_struct
{
  /* 
    missle and hit: 
      bit 0: player missle and trash
      bit 1: trash, which might hit the player
  */
  
  uint8_t missle_mask;    /* this object is a missle: it might destroy something if the target is_hit_fn says so */ 
  uint8_t hit_mask;     /* if missle_mask & hit_mask is != 0  then the object can be destroyed */
  uint8_t points;
  uint8_t draw_fn;
  uint8_t move_fn;
      /* ST_MOVE_FN_NONE, ST_MOVE_FN_X_SLOW */
  uint8_t destroy_fn;   /* object can be destroyed by a missle (e.g. a missle from the space ship) */
      /* ST_DESTROY_FN_NONE, ST_DESTROY_FN_SPLIT */
  uint8_t is_hit_fn;    /* is hit procedure */
      /* ST_IS_HIT_FN_NONE, ST_IS_HIT_BBOX */
  uint8_t fire_fn;
    /* ST_FIRE_FN_NONE, ST_FIRE_FN_X_LEFT */
  
};
typedef struct _st_ot_struct st_ot;

/*
  objects, which are visible at the play area
*/
struct _st_obj_struct
{
  uint8_t ot;       /* object type: zero means, object is not used */
  int8_t tmp;     /* generic value, used by ST_MOVE_IMPLODE */
  /* absolute position */
  /* LCD pixel position is x>>ST_FP and y>>ST_FP */
  int16_t x, y;
  int8_t x0,y0,x1,y1; /* object outline in pixel, reference point is at 0,0 */
};
typedef struct _st_obj_struct st_obj;


uint8_t st_rnd(void) U8X8_NOINLINE;
static st_obj *st_GetObj(uint8_t objnr) U8X8_NOINLINE;
uint8_t st_GetMissleMask(uint8_t objnr);
uint8_t st_GetHitMask(uint8_t objnr);
int8_t st_FindObj(uint8_t ot) U8X8_NOINLINE;
void st_ClrObjs(void) U8X8_NOINLINE;
int8_t st_NewObj(void) U8X8_NOINLINE;
uint8_t st_CntObj(uint8_t ot);
uint8_t st_CalcXY(st_obj *o) U8X8_NOINLINE;
void st_SetXY(st_obj *o, uint8_t x, uint8_t y) U8X8_NOINLINE;

void st_FireStep(uint8_t is_auto_fire, uint8_t is_fire) U8X8_NOINLINE;

void st_InitTrash(uint8_t x, uint8_t y, int8_t dir);
void st_NewGadget(uint8_t x, uint8_t y);
void st_NewPlayerMissle(uint8_t x, uint8_t y) ;
void st_NewTrashDust(uint8_t x, uint8_t y, int ot);
void st_NewTrashDustAreaArgs(int16_t x, int16_t y, int ot); 
void st_SetupPlayer(uint8_t objnr, uint8_t ot);

char *st_itoa(unsigned long v);
void st_CalcBBOX(uint8_t objnr);
uint8_t st_ClipBBOX(void);
uint8_t st_IsOut(uint8_t objnr); 
void st_Disappear(uint8_t objnr);
void st_Move(uint8_t objnr);
void st_DrawBBOX(uint8_t objnr);
#ifdef FN_IS_NOT_IN_USE
void st_DrawFilledBox(uint8_t objnr);
#endif
void st_DrawBitmap(uint8_t objnr, const uint8_t * bm, uint8_t w, uint8_t h);
void st_DrawObj(uint8_t objnr);
uint8_t st_IsHitBBOX(uint8_t objnr, uint8_t x, uint8_t y);
void st_Destroy(uint8_t objnr);
uint8_t st_IsHit(uint8_t objnr, uint8_t x, uint8_t y, uint8_t missle_mask);

void st_Fire(uint8_t objnr);
//void st_NewGadget(uint8_t x, uint8_t y);
void st_NewWall(void);
void st_NewPlayerMissle(uint8_t x, uint8_t y);
void st_NewPlayer(void);
void st_InitDeltaWall(void);
void st_InitDeltaTrash(void);
void st_InitDelta(void);

void _spacetrash(void);
#endif
