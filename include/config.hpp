#ifndef __CONFIG_H
#define __CONFIG_H

#include <nds.h>

// Player speed in pixels per frame
const s16 PSPEED = 3;

// Bullet speed in ppf
const s16 BSPEED = 10;

// Size of the gap between screens
// in pixles (or lines, as of Wikipedia)
// NOTE: 64 is not a real value,
// MelonDS has this setting and I chose it
// for testing purpouses
const u16 SCREEN_GAP = 64;

// Total height of the 2 screens combined
// with the gap taken into account
const u16 SCREENS_HEIGHT = SCREEN_HEIGHT * 2 + SCREEN_GAP;

/// ID of the sounds used
namespace Sounds {
/// Shooting sound when the player has no powerups
const u16 NORMAL_SHOOTING = 0;
} // namespace Sounds

/// IDs of the sprites used
namespace Sprites {
/// ID of the palette used by all the allies sprites in game
const u8 ALLIES_PALETTE_ID = 0;
/// ID of the palette used by all the enemies sprites in game
const u8 ENEMIES_PALETTE_ID = 1;
/// Super Ace gfx
const u16 S_ACE_GFX_ID = 0;
/// Basic bullet gfx
const u16 BULLET_GFX_ID = 1;
/// Basic enemy gfx
const u16 BASIC_ENEMY_GFX_ID = 2;
} // namespace Sprites

#endif