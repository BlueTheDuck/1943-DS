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

size_t ECS::getNextId() {
    // NOTE: Skip 0, that one is reserved for Super Ace
    for (size_t id = 1; id < 127; id++) {
        if (types[id] == EntityType::None)
            return id;
    }
    sassert(false, "Engine ran out of IDs");
    return -1;
}

void ECS::spawnEntity(EntityType type, Pos pos) {
    size_t id            = getNextId();
    this->directions[id] = Direction::Forward;
    this->types[id]      = type;
    this->positions[id]  = pos;
    switch (type) {
    case EntityType::Bullet:
        NF_CreateSprite(pos.getScreen(), id, Sprites::BULLET_GFX_ID,
                        Sprites::ALLIES_PALETTE_ID, pos.x, pos.getYMapped());
        // Hack: Do ⊕ to toggle first (and only) bit, and position sprite
        // outside of the screen
        NF_CreateSprite(pos.getScreen() ^ 1, id, Sprites::BULLET_GFX_ID,
                        Sprites::ALLIES_PALETTE_ID, pos.x, -64);
        // NF_ShowSprite(pos.getScreen() ^ 1, id, false);
        break;
    case EntityType::Enemy:
        NF_CreateSprite(pos.getScreen(), id, Sprites::BASIC_ENEMY_GFX_ID,
                        Sprites::ENEMIES_PALETTE_ID, pos.x, pos.getYMapped());
        NF_CreateSprite(pos.getScreen() ^ 1, id, Sprites::BASIC_ENEMY_GFX_ID,
                        Sprites::ENEMIES_PALETTE_ID, pos.x, -64);
        break;
    case EntityType::SuperAce:
        // TODO: Maybe adding multiplayer?
        sassert(false, "Can't create another player!");
    default:
        nocashMessage("Unknown entity type?");
        sassert(false, "Unknown entity type");
        break;
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
            timeSinceShoot  = 0;
            Pos bulletSpawn = {
                .x = static_cast<s16>(positions[S_ACE_ID].x + 8),
                .y = positions[S_ACE_ID].y,
            };
            spawnEntity(EntityType::Bullet, bulletSpawn);
            NF_PlayRawSound(Sounds::NORMAL_SHOOTING, 127, 64, false, 0);
        }
    }
    timeSinceShoot++;
}

void ECS::updatePositions() {
    for (int id = 0; id < 127; id++) {
        switch (this->types[id]) {
        case EntityType::SuperAce:
            if (keysCurrent() & KEY_LEFT) {
                positions[id].x -= PSPEED;
            }
            if (keysCurrent() & KEY_RIGHT) {
                positions[id].x += PSPEED;
            }
            if (keysCurrent() & KEY_UP) {
                positions[id].y -= PSPEED;
            }
            if (keysCurrent() & KEY_DOWN) {
                positions[id].y += PSPEED;
            }
            // Check world borders
            positions[id].x = cap(positions[id].x, -3, 228);
            positions[id].y =
                cap(positions[id].y, -3, (192 * 2 + SCREEN_GAP - 32 + 7));
            break;
        case EntityType::Bullet:
            positions[id].y -= BSPEED;
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
                if (NF_SPRITEOAM[spriteScreen][id].frame <= 1)
                    NF_SpriteFrame(spriteScreen, id, 0);
                else
                    NF_SpriteFrame(spriteScreen, id, 1);
                break;
            case Direction::Right:
                if (NF_SPRITEOAM[spriteScreen][id].frame >= 3)
                    NF_SpriteFrame(spriteScreen, id, 4);
                else
                    NF_SpriteFrame(spriteScreen, id, 3);
                break;
            case Direction::Forward:
                NF_SpriteFrame(spriteScreen, id, 2);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
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
            if (positions[id].y < 0 || positions[id].y > SCREENS_HEIGHT) {
                NF_DeleteSprite(Screen::TOP, id);
                NF_DeleteSprite(Screen::BOT, id);
                types[id] = EntityType::None;
            }
        default:
            break;
        }
    }
}

void ECS::timelineHandler() {
    int rn = rand() % 100;
    if (rn > 70) {
        Pos pos = {
            .x = rand() % 256,
            .y = rand() % 192,
        };
        if (getNextId() < 3)
            spawnEntity(EntityType::Enemy, pos);
        // spawnEntity();
    }
}
