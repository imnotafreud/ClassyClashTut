#include "raylib.h"
#include  "settings.h"



int main()
{

     //prepare window
     InitWindow(screen_width, screen_height, "Classy Clash");
     SetTargetFPS(TARGET_FPS);

     //main loop
     while (!WindowShouldClose())
     { 

          DrawFPS(0, 0);
          BeginDrawing();
          ClearBackground(WHITE);
          EndDrawing();
     }

     CloseWindow();
} 