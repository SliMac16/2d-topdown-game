#include "raylib.h"


int main(){
    const int windowWidth{1920};
    const int windowHeight{1080};
    InitWindow(windowWidth,windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{0.0,0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0,WHITE);
        EndDrawing();
    }
}