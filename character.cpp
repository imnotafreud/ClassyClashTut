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

    BaseCharacter::tick(deltaTime);
    // update animation
};

Vector2 Character::getScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.f - knightScale * (0.5 * width),
                     static_cast<float>(windowHeight) / 2.f - knightScale * (0.5 * height)};

}