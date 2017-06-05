#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"

// Enemy Car.
//static byte const _enemyleft[] = {0x00, 0x00, 0x00, 0x15, 0x1B, 0x0A, 0x1F, 0x11};
//static byte const _enemyup[] = {0x00, 0xE7, 0x42, 0x7F, 0x7F, 0x42, 0xE7, 0x00};
//static byte const _enemydown[] = {0x00, 0xE7, 0x42, 0xFE, 0xFE, 0x42, 0xE7, 0x00};

static byte const _enemyleft[] = {0x5A, 0x7E, 0x5A, 0x18, 0x18, 0x5A, 0x7E, 0x5A};
static byte const _enemyup[] = {0x00, 0xE7, 0x42, 0x7F, 0x7F, 0x42, 0xE7, 0x00};
static byte const _enemydown[] = {0x00, 0xE7, 0x42, 0xFE, 0xFE, 0x42, 0xE7, 0x00};

// Player Car.
static byte const _playerleft[] = {0x99, 0xE7, 0xA5, 0x24, 0x24, 0xA5, 0xE7, 0xBD};
static byte const _playerleftmask[] = {0x66, 0x18, 0x5A, 0xDB, 0xDB, 0x5A, 0x18, 0x42};
static byte const _playerup[] = {0xE7, 0x42, 0xFE, 0x81, 0x81, 0xFE, 0x42, 0xE7};
static byte const _playerdown[] = {0xE7, 0x42, 0x7F, 0x81, 0x81, 0x7F, 0x42, 0xE7};

// Explosion.
static byte const _explosion[] = {0x00, 0x92, 0x54, 0x28, 0x82, 0x44, 0x00, 0x44, 0x82, 0x28, 0x54, 0x92, 0x00};

// Playfield blocks.  These are 1/2 screen wide and mirrored for efficiency.
static byte const _pfblock1[] = {0x0F, 0x0F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

static byte const _pfblock2[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock3[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock4[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock5[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x0F, 0x0F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock6[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock7[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
                                0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

static byte const _pfblock8[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock10[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

static byte const _pfblock11[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock12[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock13[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock14[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock15[] = {0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static byte const _pfblock16[] = {0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
                                0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

// Holds data related to the cars.
// Type: 0=player, 1=enemy
// Directions: 1=up, 2=down, 4=left, 8=right
typedef struct 
{
    byte type;
    byte x;
    byte y;
    byte dir;
    byte lane;
    byte speed;
    byte* imageleft;
    byte* imageleftmask;
    byte* imageup;
    byte* imagedown;
} Vehicle;

typedef struct
{
    byte x;
    byte y;
    byte visible;
} Dot;

// Game vars.
int lives = 3;
int score = 0;
Vehicle player;
Vehicle enemy;
Dot dots[48];

void waitForADown() {
    byte keys = 0;
    unsigned int counter = 0;
    for (;;) {
        keys = READ_BUTTONS();
        if ((keys & 16) == 0)
            break;
        
        WAIT();
        
        ++counter;
    }
}

void waitForAUp() {
    byte keys = 0;
    for (;;) {
        keys = READ_BUTTONS();
        if ((keys & 16) == 16)
            break;
        
        WAIT();
    }
}
void center(byte row, char *text) {
    byte len = strlen(text);
    byte x = ((17 - len) / 2) + 1;
    SET_CURSOR(row, x);
    DRAW_STRING(text);
}

void prompt(char *text) {
    CLEAR();
    SET_CURSOR(2, 2);
    DRAW_STRING("\311\315\315\315\315\315\315\315\315\315\315\315\315\315\273");
    center(3, text);
    SET_CURSOR(3, 2);
    DRAW_STRING("\272");
    SET_CURSOR(3, 16);
    DRAW_STRING("\272");
    SET_CURSOR(4, 2);
    DRAW_STRING("\310\315\315\315\315\315\315\315\315\315\315\315\315\315\274");
    center(6, "Press (A)");
    DISPLAY();
    waitForADown();
    waitForAUp();
}

void loadDotQuadrant(byte startx, byte starty, byte endx, byte endy, byte incx, byte incy)
{
    byte cntx;
    byte cnty;
    byte dotindex = 0;
    
    // Loop through x values.
    for (cntx = startx; cntx < endx; cntx += incx)
    {
        // Loop through y values.
        for (cnty = starty; cnty < endy; cnty += incy)
        {
            // Assign dot location to array.
            dots[dotindex].x = cntx;
            dots[dotindex].y = cnty;
            dots[dotindex].visible = 1;
            
            // Set pixel on screen that represents it.
            SET_PIXEL(cntx, cnty, 1);
            
            // Increment dot index.
            dotindex++;
        }
    }
}

void initVehicles()
{
    // Setup vehicles.
    player.type = 0;
    player.x = 72;
    player.y = 55;
    player.dir = 8;
    player.lane = 3;
    player.speed = 1;
    player.imageleft = (byte*)_playerleft;
    player.imageup = (byte*)_playerup;
    player.imagedown = (byte*)_playerdown;
    player.imageleftmask = (byte*)_playerleftmask;
    
    enemy.type = 1;
    enemy.x = 56;
    enemy.y = 55;
    enemy.dir = 4;
    enemy.lane = 3;
    enemy.speed = 1;
    enemy.imageleft = (byte*)_enemyleft;
    enemy.imageup = (byte*)_enemyup;
    enemy.imagedown = (byte*)_enemydown;
    
}

void initPlayfield()
{
    byte* pf1 = (byte*)_pfblock1;
    byte* pf2 = (byte*)_pfblock2;
    byte* pf3 = (byte*)_pfblock3;
    byte* pf4 = (byte*)_pfblock4;
    byte* pf5 = (byte*)_pfblock5;
    byte* pf6 = (byte*)_pfblock6;
    byte* pf7 = (byte*)_pfblock7;
    byte* pf8 = (byte*)_pfblock8;
    byte* pf10 = (byte*)_pfblock10;
    byte* pf11 = (byte*)_pfblock11;
    byte* pf12 = (byte*)_pfblock12;
    byte* pf13 = (byte*)_pfblock13;
    byte* pf14 = (byte*)_pfblock14;
    byte* pf15 = (byte*)_pfblock15;
    byte* pf16 = (byte*)_pfblock16;

    DRAW_SPRITE(pf1, 0, 0, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf1, 64, 0, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf2, 0, 4, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf2, 64, 4, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf3, 0, 8, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf3, 64, 8, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf4, 0, 12, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf4, 64, 12, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf5, 0, 16, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf5, 64, 16, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf6, 0, 20, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf6, 64, 20, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf7, 0, 24, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf7, 64, 24, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf8, 0, 28, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf8, 64, 28, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf8, 0, 32, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf8, 64, 32, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf10, 0, 36, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf10, 64, 36, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf11, 0, 40, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf11, 64, 40, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf12, 0, 44, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf12, 64, 44, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf13, 0, 48, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf13, 64, 48, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf14, 0, 52, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf14, 64, 52, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf15, 0, 56, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf15, 64, 56, 64, 8, 1, DRAW_NOP);
    DRAW_SPRITE(pf16, 0, 60, 64, 8, 0, DRAW_NOP);
    DRAW_SPRITE(pf16, 64, 60, 64, 8, 1, DRAW_NOP);

    // Draw horizontal lines.
/*
    DRAW_LINE(0,0,127,0,1);
    DRAW_LINE(12,9,48,9,1);
    DRAW_LINE(79,9,115,9,1);
    DRAW_LINE(24,18,48,18,1);
    DRAW_LINE(79,18,103,18,1);
    DRAW_LINE(36,27,92,27,1);
    DRAW_LINE(36,36,92,36,1);
    DRAW_LINE(24,45,48,45,1);
    DRAW_LINE(79,45,103,45,1);
    DRAW_LINE(12,54,48,54,1);
    DRAW_LINE(79,54,115,54,1);
    DRAW_LINE(0,63,127,63,1);

    // Draw vertical lines.
    DRAW_LINE(0,0,0,63,1);
    DRAW_LINE(127,0,127,63,1);
    DRAW_LINE(12,9,12,22,1);
    DRAW_LINE(115,9,115,22,1);
    DRAW_LINE(24,18,24,22,1);
    DRAW_LINE(103,18,103,22,1);
    DRAW_LINE(36,27,36,36,1);
    DRAW_LINE(92,27,92,36,1);
    DRAW_LINE(24,45,24,41,1);
    DRAW_LINE(103,45,103,41,1);
    DRAW_LINE(12,54,12,41,1);
    DRAW_LINE(115,54,115,41,1);
*/
    
    // Draw dots.
    loadDotQuadrant(6, 4, 48, 27, 13, 9);
    loadDotQuadrant(80, 4, 126, 27, 14, 9);
    loadDotQuadrant(6, 41, 48, 63, 13, 9);
    loadDotQuadrant(80, 41, 126, 63, 14, 9);
}

void drawVehicle(Vehicle *vehicle)
{
    if ((*vehicle).dir == 1)
    {
        DRAW_SPRITE((*vehicle).imageup, (*vehicle).x, (*vehicle).y, 5, 8, 0, DRAW_OR);
    }        
    
    else if ((*vehicle).dir == 2)
    {
        DRAW_SPRITE((*vehicle).imagedown, (*vehicle).x, (*vehicle).y, 5, 8, 0, DRAW_OR);
    }        
    
    else if ((*vehicle).dir == 4)
    {
        DRAW_SPRITE((*vehicle).imageleftmask, (*vehicle).x, (*vehicle).y, 8, 8, 0, DRAW_AND);
        DRAW_SPRITE((*vehicle).imageleft, (*vehicle).x, (*vehicle).y, 8, 8, 0, DRAW_OR);
    }
    
    else if ((*vehicle).dir == 8)
    {
        DRAW_SPRITE((*vehicle).imageleftmask, (*vehicle).x, (*vehicle).y, 8, 8, 1, DRAW_AND);
        DRAW_SPRITE((*vehicle).imageleft, (*vehicle).x, (*vehicle).y, 8, 8, 1, DRAW_OR);
    }
    
}

void drawDots()
{
    byte i;
    
    // Loop through dots.
    for (i=0;i< sizeof(dots);i++)
    {
        // First check to see if this is a dot we care about.
        if (dots[i].visible == 1)
        {
            // Draw dot.
            SET_PIXEL(dots[i].x, dots[i].y, 1);
        }
    }
}

void checkForDotCollision()
{
    byte i;
    
    // Loop through dots.
    for (i=0;i< sizeof(dots);i++)
    {
        // First check to see if this is a dot we care about.
        if (dots[i].visible == 1)
        {
            // Check to see if the player hit this dot.
            if (player.x == dots[i].x && player.y == dots[i].y)
            {
                // Remove the dot and mark as not visible.
                dots[i].visible = 0;
                SET_PIXEL(dots[i].x, dots[i].y, 0);
                
                // Increment score.
                score++;
                break;
            }
        }
    }
}

void checkForVehicleCollision()
{
    // Check to see if the cars hit.
    if (player.x == enemy.x && player.y == enemy.y)
    {
        // Deduct life.
        lives--;
        
        // Show prompt.
        prompt("boom");
    }
}

void handleVehicleMovement(Vehicle *vehicle)
{
    // First clear the current sprite.
    CLEAR_SPRITE((*vehicle).x, (*vehicle).y, 8, 8);
    
    // Check to see which way the vehicle is moving now.
    switch ((*vehicle).dir)
    {
        case 1:
            // Check to see if the car can go that way.
            if ((*vehicle).y-1 > 0)
            {
                // Update the position.
                (*vehicle).y -= 1;
            }
            
            else
            {
                // Update the direction and position.
                (*vehicle).dir = (*vehicle).type == 0 ? 4 : 8;
                (*vehicle).x -= 1;
            }
            
            break;
            
        case 2:
            // Check to see if the car can go that way.
            if ((*vehicle).y+1 < 56)
            {
                // Update the position.
                (*vehicle).y += 1;
            }
            
            else
            {
                // Update the direction and position.
                (*vehicle).dir = (*vehicle).type == 0 ? 8 : 4;
                (*vehicle).x += 1;
            }

            break;
        
        case 4:
            // Check to see if the car can go that way.
            if ((*vehicle).x-1 > 0)
            {
                // Update the *vehicle position.
                (*vehicle).x -= 1;
            }
            
            else
            {
                // Update the direction and position.
                (*vehicle).dir = (*vehicle).type == 0 ? 2 : 1;
                (*vehicle).y += 1;
            }

            break;
        
        case 8:
            // Check to see if the car can go that way.
            if ((*vehicle).x+1 < 120)
            {
                // Update the position.
                (*vehicle).x += 1;
            }
            
            else
            {
                // Update the direction and position.
                (*vehicle).dir = (*vehicle).type == 0 ? 1 : 2;
                (*vehicle).y -= 1;
            }

            break;
    }
    
    // Now draw the vehicle.
    drawVehicle(vehicle);
}

int main() {
	
	// Game logic vars.
	byte keys;
    
	// Initialize the API
	api_init();

	// Clear the graphics in video memory
	CLEAR();

    // Setup playfield.
    initPlayfield();
   
    // Setup vehicles.
    initVehicles();
    
	for (;;) 
	{
	    while (lives > 0)
	    {
            handleVehicleMovement(&player);
            handleVehicleMovement(&enemy);
            checkForVehicleCollision();
            
    		DISPLAY();
    		
    		WAIT();
	    }
    }
	return 0;
}