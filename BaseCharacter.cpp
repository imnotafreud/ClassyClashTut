#include "BaseCharacter.h"
#include "raymath.h"
#include <iostream>

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::debug(float deltaTime)

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

void BaseCharacter::undoMovement()

{
    worldPos = lastWorldPos;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * knightScale,
        height * knightScale};
}

void BaseCharacter::tick(float deltaTime)
{
    lastWorldPos = worldPos;
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
}