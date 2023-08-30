#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(){
    const int windowWidth{1920};
    const int windowHeight{1080};
    InitWindow(windowWidth,windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0,0.0};
    const float mapScale{3.0f};

    Character knight;
    knight.setScreenPos(windowWidth,windowHeight);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);


        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale,WHITE);

        knight.tick(GetFrameTime());
        // preventing character from getting off the map
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }

        EndDrawing();
    }
}