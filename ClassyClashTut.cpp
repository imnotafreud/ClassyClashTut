#include <iostream>
#include <string>
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
     /*      Enemy goblin(Vector2{550.f, 700.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
          goblin.setTarget(&knight); */

     Prop props[2]{
         Prop{Vector2{450.f, 550.f}, LoadTexture("nature_tileset/Rock.png")},
         Prop{Vector2{750.f, 600.f}, LoadTexture("nature_tileset/Log.png")}};

     /*      Enemy goblins[2]{
          Enemy{Vector2{550.f, 700.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")},
          Enemy{Vector2{550.f, 700.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")}}; */
     const int size = 5;
     Enemy goblins[size] = {Enemy};
     for (int i = 0; i < 5; i++)
     {
          goblins[i] = Enemy{Vector2{i * 100.f, 0.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
     }

     // main loop
     while (!WindowShouldClose())
     {

          DrawFPS(0, 0);
          BeginDrawing();
          ClearBackground(WHITE);
          float dt = GetFrameTime();
          // draw map
          mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
          DrawTextureEx(map, mapPos, 0, mapScale, WHITE);
          // draw props
          for (auto prop : props)
          {
               prop.Render(knight.getWorldPos());
               if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
               {
                    knight.undoMovement();
               }
          }
          if (!knight.getAlive())
          {
               DrawText("GAME OVER!", 55.f, 172.f, 40, RED);
               EndDrawing();
               continue;
          }
          else
          {
               std::string knightsHeals = "Health: ";
               knightsHeals.append(std::to_string(knight.getHealth()), 0, 3);
               DrawText(knightsHeals.c_str(), 0.f, 0.f, 50, RED);
          }
          knight.tick(dt);
          // check map boundaries

          if (knight.getWorldPos().x < 0.f ||
              knight.getWorldPos().y < 0.f ||
              knight.getWorldPos().x + screen_width > map.width * mapScale ||
              knight.getWorldPos().y + screen_height > map.height * mapScale)
          {
               knight.undoMovement();
          }

          knight.debug(dt);

          for (int i = 0; i < 5; i++)
          {
               goblins[i].tick(dt);
          }

          if (IsKeyPressed(KEY_SPACE))
          {
               for (int i = 0; i < 5; i++)
               {
                    if (CheckCollisionRecs(goblins[i].getCollisionRec(), knight.getWeaponCollision()))
                    {
                         goblins[i].setAlive(false);
                    };

                    EndDrawing();
               }
          }
          UnloadTexture(map);
          CloseWindow();
     }
}