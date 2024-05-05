#include "character.h"
#include "raymath.h"
#include <iostream>

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;

}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {winWidth / 2.0 - knightScale * (0.5 * width),
                 winHeight / 2.0 - knightScale * (0.5 * height)};
};

void Character::tick(float deltaTime)
{
    lastWorldPos = getWorldPos();
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
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        frame = frame % maxFrames;
    }
    // draw character
    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, knightScale * width, knightScale * height};
    DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0, WHITE);
};

void Character::debug(float deltaTime)

{

    time += deltaTime;
    if (time >= 1)
    {

        time = 0.f;
        std::cout << "X " << worldPos.x;
        std::cout << " Y " << worldPos.y << std::endl;
        std::cout << " dT " << deltaTime << std::endl;
    }
}

void Character::undoMovement()
{
    worldPos = lastWorldPos;
}