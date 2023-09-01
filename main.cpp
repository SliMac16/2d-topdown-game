#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main(){
    const int windowWidth{1920};
    const int windowHeight{1080};
    InitWindow(windowWidth,windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0,0.0};
    const float mapScale{4.0f};

    Character knight(windowWidth, windowHeight);


    Prop props[2]
    {
        Prop{Vector2{1200.f, 600.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{800.f, 1000.f}, LoadTexture("nature_tileset/Log.png")}
    };
    

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);


        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale,WHITE);

        //draw the props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        // preventing character from getting off the map
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }

        //check collisions between Character:knight and Props
        for(auto prop : props)
        {
            if(CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
}