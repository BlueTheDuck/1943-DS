#include "nf_lib.h"
#include <nds.h>

#include <stdio.h>

#include "helper.hpp"
#include "world.hpp"

static const u16 SCREEN_GAP = 0;

int main(int argc, char *argv[]) {
    NF_SetRootFolder("NITROFS");

    swiWaitForVBlank();

    NF_Set2D(Screen::TOP, 0);
    NF_Set2D(Screen::BOT, 0);

    consoleDemoInit();
    iprintf("Initialazing");

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(Screen::TOP);
    NF_InitTiledBgSys(Screen::BOT);
    
    auto bg = new Background(SCREEN_GAP);

    while (1) {
        bg->scroll();
        swiWaitForVBlank();
    }

    return 0;
}