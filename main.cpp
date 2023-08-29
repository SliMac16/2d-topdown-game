#include "raylib.h"
#include "raymath.h"


int main(){
    const int windowWidth{1920};
    const int windowHeight{1080};
    InitWindow(windowWidth,windowHeight, "Top Down Game");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0,0.0};
    float speed = 5.0;

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run =LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = knight_idle;

    Vector2 knightPos{
        windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0),
        windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height),

    };

    float rightLeft{1.0f};
    //animation:
    float runningTime{};
    int frame{};
    const int MaxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0){
            knight = knight_run;
            //set mapPos =mapPos - direction
            mapPos = Vector2Subtract(mapPos,Vector2Scale(Vector2Normalize(direction),speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }else knight = knight_idle;

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0,WHITE);

        //update animation frame
        runningTime += GetFrameTime();
        if(runningTime >= updateTime){
            frame++;
            runningTime = 0.f;
            if(frame > MaxFrames) frame = 0;

        }

        //draw the character
        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 6.0f * (float)knight.width/6.0f, 6.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
}