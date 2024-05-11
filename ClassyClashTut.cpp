#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "settings.h"
#include "character.h"
#include "enemy.h"
#include "prop.h"

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
     Character knight(screen_width, screen_height);

     // create enemy
     Enemy goblin(Vector2{550.f, 700.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
     goblin.setTarget(&knight);

     Prop props[2]{
         Prop{Vector2{450.f, 550.f}, LoadTexture("nature_tileset/Rock.png")},
         Prop{Vector2{750.f, 600.f}, LoadTexture("nature_tileset/Log.png")}};

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
          // draw props
          for (auto prop : props)
          {
               prop.Render(knight.getWorldPos());
               if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
               {
                    knight.undoMovement();
               }
          }
          goblin.tick(dt);
          EndDrawing();
     }
     UnloadTexture(map);
     CloseWindow();
}