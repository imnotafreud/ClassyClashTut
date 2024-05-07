#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos()
    {
        return worldPos;
    }
    void tick(float deltaTime);
    void debug(float deltatime);
    void undoMovement();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 lastWorldPos{0.0};
    // right = 1
    float rightLeft{1.f};
    // animation
    float runningTime{0.f};
    int frame{0};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    float width{};
    float height{};
    //some parameters
    float speed{2.f};
    float knightScale{4.f};
    float dt = GetFrameTime();
    float time{0.f};



};