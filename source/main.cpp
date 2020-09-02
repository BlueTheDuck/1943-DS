#include <nds.h>
#include "nf_lib.h"

#include <stdio.h>

#include "config.hpp"
#include "helper.hpp"
#include "world.hpp"
#include "ECS.hpp"

static size_t    FRAME      = 0;

int main(int argc, char *argv[]) {
    /* #region Setup */
    nocashMessage("Initialzing");

    NF_SetRootFolder("NITROFS");

    NF_Set2D(Screen::TOP, 0);
    NF_Set2D(Screen::BOT, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(Screen::TOP);
    NF_InitTiledBgSys(Screen::BOT);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(Screen::TOP);
    NF_InitSpriteSys(Screen::BOT);

    /* #endregion */

    /* #region Sprites */
    NF_LoadSpriteGfx("sprites/super-ace", 0, 32, 32);
    NF_LoadSpritePal("sprites/super-ace", 0);
    NF_LoadSpriteGfx("sprites/bullet", 1, 16, 16);
    NF_LoadSpritePal("sprites/bullet", 1);

    // Player
    NF_VramSpriteGfx(Screen::TOP, 0, 0, false);
    NF_VramSpritePal(Screen::TOP, 0, 0);
    NF_VramSpriteGfx(Screen::BOT, 0, 0, false);
    NF_VramSpritePal(Screen::BOT, 0, 0);
    // Bullet
    NF_VramSpriteGfx(Screen::TOP, 1, 1, false);
    NF_VramSpritePal(Screen::TOP, 1, 1);
    NF_VramSpriteGfx(Screen::BOT, 1, 1, false);
    NF_VramSpritePal(Screen::BOT, 1, 1);
    /* #endregion */

    ECS game = ECS();

    Background bg(SCREEN_GAP);

    while (1) {
        scanKeys();
        bg.scroll();
        // player.update();
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