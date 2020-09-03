#include "nf_lib.h"
#include <nds.h>

#include <stdio.h>

#include "ECS.hpp"
#include "config.hpp"
#include "helper.hpp"
#include "world.hpp"

static size_t FRAME = 0;

int main(int argc, char *argv[]) {
    /* #region Setup */
    NF_SetRootFolder("NITROFS");

    NF_Set2D(Screen::TOP, 0);
    NF_Set2D(Screen::BOT, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(Screen::TOP);
    NF_InitTiledBgSys(Screen::BOT);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(Screen::TOP);
    NF_InitSpriteSys(Screen::BOT);

    NF_InitRawSoundBuffers();
    soundEnable();

    /* #endregion */

    /* #region Sprites */
    NF_LoadSpriteGfx("sprites/super-ace", Sprites::S_ACE_GFX_ID, 32, 32);
    NF_LoadSpriteGfx("sprites/bullet", Sprites::BULLET_GFX_ID, 16, 16);
    NF_LoadSpriteGfx("sprites/basic-enemy", Sprites::BASIC_ENEMY_GFX_ID, 16, 16);

    NF_LoadSpritePal("sprites/spritesheet-allies", Sprites::ALLIES_PALETTE_ID);
    NF_LoadSpritePal("sprites/spritesheet-enemies", Sprites::ENEMIES_PALETTE_ID);

    // Player
    NF_VramSpriteGfx(Screen::TOP, Sprites::S_ACE_GFX_ID, Sprites::S_ACE_GFX_ID,
                     false);
    NF_VramSpriteGfx(Screen::BOT, Sprites::S_ACE_GFX_ID, Sprites::S_ACE_GFX_ID,
                     false);
    NF_VramSpritePal(Screen::TOP, Sprites::ALLIES_PALETTE_ID, Sprites::ALLIES_PALETTE_ID);
    NF_VramSpritePal(Screen::BOT, Sprites::ALLIES_PALETTE_ID, Sprites::ALLIES_PALETTE_ID);
    NF_VramSpritePal(Screen::TOP, Sprites::ENEMIES_PALETTE_ID, Sprites::ENEMIES_PALETTE_ID);
    NF_VramSpritePal(Screen::BOT, Sprites::ENEMIES_PALETTE_ID, Sprites::ENEMIES_PALETTE_ID);
    // Bullet
    NF_VramSpriteGfx(Screen::TOP, Sprites::BULLET_GFX_ID,
                     Sprites::BULLET_GFX_ID, false);
    NF_VramSpriteGfx(Screen::BOT, Sprites::BULLET_GFX_ID,
                     Sprites::BULLET_GFX_ID, false);
    NF_VramSpriteGfx(Screen::BOT, Sprites::BASIC_ENEMY_GFX_ID,
                     Sprites::BASIC_ENEMY_GFX_ID, false);
    /* #endregion */

    /* #region Sounds */
    NF_LoadRawSound("sound/sound_0", Sounds::NORMAL_SHOOTING, 11025,
                    SoundFormat_8Bit);
    /* #endregion */

    ECS game = ECS();

    Background bg = Background();

    while (1) {
        scanKeys();
        bg.scroll();
        game.handleInput();
        game.updatePositions();
        game.updateSprites();
        game.garbageCollector();
        NF_SpriteOamSet(Screen::TOP);
        NF_SpriteOamSet(Screen::BOT);
        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
        FRAME++;
    }

    return 0;
}