#include "character.h"
#include "raymath.h"
#include <iostream>

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {static_cast<float>(winWidth) / 2.f - knightScale * (0.5 * width),
                 static_cast<float>(winHeight) / 2.f - knightScale * (0.5 * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

    speed = 2.f;
    Vector2 direction{0.f, 0.f};
    if (IsKeyDown(KEY_A))
        direction.x = -1;
    if (IsKeyDown(KEY_D))
        direction.x = 1;
    if (IsKeyDown(KEY_S))
        direction.y = 1;
    if (IsKeyDown(KEY_W))
        direction.y = -1;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed = 4;
    if (Vector2Length(direction) >= 0.00001)
    {

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // update animation
};