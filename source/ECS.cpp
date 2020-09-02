#include "ECS.hpp"

ECS::ECS() {
    // Initialize arrays of properties
    for (size_t id = 1; id < 127; id++) {
        types[id]      = EntityType::None;
        directions[id] = Direction::Forward;
        positions[id]  = {.x = -64, .y = -64};
    }

    // Initialize Super Ace (The player)
    types[S_ACE_ID]      = EntityType::SuperAce;
    directions[S_ACE_ID] = Direction::Forward;
    screens[S_ACE_ID]    = Screen::BOT;
    positions[S_ACE_ID]  = {.x = 40, .y = 192 + SCREEN_GAP + 40};

    // Create Super Ace sprites on both screens
    NF_CreateSprite(Screen::TOP, S_ACE_ID, 0, 0, 50, -32);
    NF_CreateSprite(Screen::BOT, S_ACE_ID, 0, 0, 50, 50);
    // Set the appropriate frame
    NF_SpriteFrame(Screen::TOP, S_ACE_ID, 2);
    NF_SpriteFrame(Screen::BOT, S_ACE_ID, 2);
    // Super Ace always spawns on the bottom screen, so we have to hide the top
    // sprite
    // NF_ShowSprite(Screen::TOP, S_ACE_ID, false);
}

void ECS::updatePositions() {
    for (int id = 0; id < 127; id++) {
        switch (this->types[id]) {
        case EntityType::SuperAce:
            if (keysCurrent() & KEY_LEFT) {
                positions[id].x -= PSPEED;
                /* NF_SPRITEOAM[Screen::BOT][id].x -= PSPEED;
                NF_SPRITEOAM[Screen::TOP][id].x -= PSPEED; */
            }
            if (keysCurrent() & KEY_RIGHT) {
                positions[id].x += PSPEED;
                /* NF_SPRITEOAM[Screen::BOT][id].x += PSPEED;
                NF_SPRITEOAM[Screen::TOP][id].x += PSPEED; */
            }
            if (keysCurrent() & KEY_UP) {
                positions[id].y -= PSPEED;
                /* NF_SPRITEOAM[screen[id]][id].y -= PSPEED; */
            }
            if (keysCurrent() & KEY_DOWN) {
                positions[id].y += PSPEED;
                /* NF_SPRITEOAM[screen[id]][id].y += PSPEED; */
            }
            // Check world borders
            positions[id].x = positions[id].x < -3 ? -3 : positions[id].x;
            positions[id].x = positions[id].x > 228 ? 228 : positions[id].x;
            positions[id].y = positions[id].y < -3 ? -3 : positions[id].y;
            positions[id].y = positions[id].y > (192 * 2 + SCREEN_GAP - 32 + 7)
                ? (192 * 2 + SCREEN_GAP - 32 + 7)
                : positions[id].y;
            break;
        case EntityType::Bullet:
            positions[id].y -= BSPEED;
            /* NF_SPRITEOAM[Screen::BOT][id].y -= BSPEED; */
            break;
        default:
            break;
        }
        NF_MoveSprite(positions[id].getScreen(), id, positions[id].x,
                      positions[id].getYMapped());
    }
}
void ECS::updateSprites() {
    for (size_t id = 0; id < 127; id++) {
        auto spriteScreen = positions[id].getScreen();
        switch (this->types[id]) {
        case EntityType::SuperAce:
            // TODO: Implement "barrel roll" and taking off animations

            // * Flying sprites
            // Super Ace has 2 sprites for left and 2 for right
            // [0-1 2 3-4]
            // 2 being "flying straight"
            // 1 and 3 are for smoothing the transition
            switch (directions[id]) {
            case Direction::Left:
                if (NF_SPRITEOAM[spriteScreen][id].frame <= 1) {
                    NF_SpriteFrame(spriteScreen, id, 0);
                } else
                    NF_SpriteFrame(spriteScreen, id, 1);
                break;
            case Direction::Right:
                if (NF_SPRITEOAM[spriteScreen][id].frame >= 3) {
                    NF_SpriteFrame(spriteScreen, id, 4);
                } else
                    NF_SpriteFrame(spriteScreen, id, 3);
                break;
            case Direction::Forward:
                NF_SpriteFrame(spriteScreen, id, 2);
                break;
            default:
                sassert(false, "What?");
                break;
            }
            break;
        default:
            break;
        }
    }
}

void ECS::handleInput() {
    auto down = keysHeld();
    if (down & KEY_LEFT) {
        directions[S_ACE_ID] = Direction::Left;
    } else if (down & KEY_RIGHT) {
        directions[S_ACE_ID] = Direction::Right;
    } else {
        directions[S_ACE_ID] = Direction::Forward;
    }

    if (down & KEY_Y) {
        if (timeSinceShoot > 10) {
            timeSinceShoot = 0;
            s16 x          = NF_SPRITEOAM[Screen::BOT][S_ACE_ID].x + 8;
            s16 y          = NF_SPRITEOAM[Screen::BOT][S_ACE_ID].y;
            if (positions[S_ACE_ID].getScreen() == Screen::BOT) {
                y += 192 + SCREEN_GAP;
            }
            spawnEntity(EntityType::Bullet, x, y);
        } else
            timeSinceShoot++;
    }
}

void ECS::spawnEntity(EntityType type, s16 x, s16 y) {
    size_t id            = getNextId();
    this->directions[id] = Direction::Forward;
    this->types[id]      = type;
    this->positions[id]  = {.x = x, .y = y};
    switch (type) {
    case EntityType::Bullet:
        NF_CreateSprite(Screen::BOT, id, 1, 1, x, y);
        break;
    case EntityType::SuperAce:
        // TODO: Maybe adding multiplayer?
        sassert(false, "Can't create another player!");
    default:
        break;
    }
}

void ECS::garbageCollector() {
    for (size_t id = 1; id < 127; id++) {
        switch (types[id]) {
        case EntityType::SuperAce:
        case EntityType::None:
            continue;
            break;
        case EntityType::Bullet:
            if (NF_SPRITEOAM[Screen::BOT][id].y < 0) {
                NF_DeleteSprite(Screen::BOT, id);
                types[id] = EntityType::None;
            }
        default:
            break;
        }
    }
}

size_t ECS::getNextId() {
    // NOTE: Skip 1, that one is reserved for Super Ace
    for (size_t id = 1; id < 127; id++) {
        if (types[id] == EntityType::None)
            return id;
    }
    sassert(false, "Engine ran out of IDs");
    return -1;
}
