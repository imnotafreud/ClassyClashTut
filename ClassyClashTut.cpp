#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "settings.h"
#include "character.h"

int main()
{

     // prepare window
     InitWindow(screen_width, screen_height, "Classy Clash");
     SetTargetFPS(TARGET_FPS);
     // load map
     Texture2D map = LoadTexture("map/my_map_v01.png");
     float mapScale = 4.0;
     Vector2 mapPos{0.0, 0.0};

     // create knight
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
          if (knight.getWorldPos().x < 0.f ||
              knight.getWorldPos().y < 0.f ||
              knight.getWorldPos().x + screen_width > map.width * mapScale ||
              knight.getWorldPos().y + screen_height > map.height * mapScale)
          {
               knight.undoMovement();
          }
          knight.debug(dt);
          EndDrawing();
     }
     UnloadTexture(map);
     CloseWindow();
}