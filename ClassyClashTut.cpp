#include "raylib.h"
#include  "settings.h"



int main()
{

     //prepare window
     InitWindow(screen_width, screen_height, "Classy Clash");
     SetTargetFPS(TARGET_FPS);
          
          
     Texture2D map = LoadTexture("map/my_map_v01.png");
     float mapScale = 4.0;
     Vector2 pos{0.0, 0.0};


     //main loop
     while (!WindowShouldClose())
     { 

          DrawFPS(0, 0);
          BeginDrawing();
          ClearBackground(WHITE);



          DrawTextureEx(map, pos, 0, mapScale, WHITE);






          EndDrawing();
     }
     UnloadTexture(map);
     CloseWindow();
     
} 