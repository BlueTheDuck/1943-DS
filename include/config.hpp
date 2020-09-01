#ifndef __CONFIG_H
#define __CONFIG_H

#include <nds.h>

// Player speed in pixels per frame
static s16 PSPEED = 3;

// Bullet speed in ppf
static s16 BSPEED = 10;

// Size of the gap between screens
// in pixles (or lines, as of Wikipedia)
// NOTE: 64 is not a real value, 
// MelonDS has this setting and I chose it 
// for testing purpouses
static const u16 SCREEN_GAP = 64;

#endif