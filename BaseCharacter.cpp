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
        std::cout<<typeid(BaseCharacter).name()<<std::endl;
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
        getScreenPos().x,
        getScreenPos().y,
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
    //update texture for movement
        if (Vector2Length(velocity) >= 0.00001)
    {

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    // draw character
    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, knightScale * width, knightScale * height};
    DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0, WHITE);
}