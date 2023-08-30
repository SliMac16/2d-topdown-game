#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(){
    const int windowWidth{1920};
    const int windowHeight{1080};
    InitWindow(windowWidth,windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0,0.0};
    Character knight;
    knight.setScreenPos(windowWidth,windowHeight);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);


        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0,WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
}