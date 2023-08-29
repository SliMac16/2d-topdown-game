#include "raylib.h"
#include "raymath.h"

class Character{
    public:
    Vector2 getWorldPos() {return worldPos;}
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.0f};
    //animation:
    float runningTime{};
    int frame{};
    const int MaxFrames{6};
    const float updateTime{1.f/12.f};
    const float speed{6.f};
};
void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos ={
        (float)winWidth/2.0f - 4.0f * (0.5f * (float)texture.width/6.0),
        (float)winHeight/2.0f - 4.0f * (0.5f * (float)texture.height),
    };
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0){
            texture = run;
            //set worldPos = worldPos + direction
            worldPos = Vector2Add(worldPos,Vector2Scale(Vector2Normalize(direction),speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }else texture = idle;

        //update animation frame
        runningTime += deltaTime;
        if(runningTime >= updateTime){
            frame++;
            runningTime = 0.f;
            if(frame > MaxFrames) frame = 0;

        }
}

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