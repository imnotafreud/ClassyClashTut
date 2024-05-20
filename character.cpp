#include "character.h"
#include "raymath.h"
#include <iostream>

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth), windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    // float rotation{};
    speed = 2.f;
    if (IsKeyDown(KEY_A))
        velocity.x = -1;
    if (IsKeyDown(KEY_D))
        velocity.x = 1;
    if (IsKeyDown(KEY_S))
        velocity.y = 1;
    if (IsKeyDown(KEY_W))
        velocity.y = -1;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed = 4;

    if (std::abs(rotation) > 0)
    {
        time += deltaTime;
        std::cout << rotation << std::endl;
        if (time >= 1)
        {
            rotation = 0.f;
            time = 0.f;
        }
    } 
    BaseCharacter::tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};

    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * knightScale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + offset.x,
                              getScreenPos().y + offset.y - weapon.height * knightScale,
                              weapon.width * knightScale,
                              weapon.height * knightScale};
        IsKeyPressed(KEY_SPACE) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * knightScale, weapon.height * knightScale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + offset.x - weapon.width * knightScale,
                              getScreenPos().y + offset.y - weapon.height * knightScale,
                              weapon.width * knightScale,
                              weapon.height * knightScale};
        IsKeyPressed(KEY_SPACE) ? rotation = -35.f : rotation = 0.f;
    }
    // draw sword
    Rectangle source{0.f, 0.f, weapon.width * rightLeft, weapon.height};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * knightScale, weapon.height * knightScale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weapon.width * knightScale, weapon.height * knightScale, RED);
};

Vector2 Character::getScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.f - knightScale * (0.5 * width),
                   static_cast<float>(windowHeight) / 2.f - knightScale * (0.5 * height)};
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f)
    {
        setAlive(false);
    }
}