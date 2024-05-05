#include "raylib.h"
#include "raymath.h"
#include "settings.h"

class Character
{
public:
     Vector2 getWorldPos()
     {
          return worldPos;
     }
     void setScreenPos(int winWidth, int winHeight);
     void tick(float deltaTime);

private:
     Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
     Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
     Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
     Vector2 screenPos;
     Vector2 worldPos{0.0, 0.0};
     // right = 1
     float rightLeft{1.f};
     // animation
     float runningTime{};
     int frame{};
     const int maxFrames{6};
     const float updateTime{1.f / 12.f};
     float speed{2.f};
     float knightScale{4.f};
     float dt = GetFrameTime();
};

void Character::setScreenPos(int winWidth, int winHeight)
{
     screenPos = {winWidth / 2.0 - knightScale * (0.5 * texture.width / 6.0),
                  winHeight / 2.0 - knightScale * (0.5 * texture.height)};
};

void Character::tick(float deltaTime)
{
     speed = 2.f;
     Vector2 direction{};
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
     if (Vector2Length(direction) != 0.0)
     {

          worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
          direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
          texture = run;
     }
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
     Rectangle source{frame * texture.width / 6.0, 0, rightLeft * texture.width / 6.0, texture.height};
     Rectangle dest{screenPos.x, screenPos.y, knightScale * texture.width / 6.0, knightScale * texture.height};
     DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0, WHITE);
};



int main()
{

     // prepare window
     InitWindow(screen_width, screen_height, "Classy Clash");
     SetTargetFPS(TARGET_FPS);
     //load map
     Texture2D map = LoadTexture("map/my_map_v01.png");
     float mapScale = 4.0;
     Vector2 mapPos{0.0, 0.0};

     //create knight
     Character knight;
     knight.setScreenPos(screen_width, screen_height);

     // main loop
     while (!WindowShouldClose())
     {

          DrawFPS(0, 0);
          BeginDrawing();
          ClearBackground(WHITE);

          float dt = GetFrameTime();
          mapPos = Vector2Scale(knight.getWorldPos(), -1.f);


          DrawTextureEx(map, mapPos, 0, mapScale, WHITE);
          knight.tick(dt);
          EndDrawing();
     }
     UnloadTexture(map);
     CloseWindow();
}