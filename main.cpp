#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


int main(){
    const int windowWidth{860};
    const int windowHeight{720};
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

     
        Enemy goblin = Enemy{Vector2{1400.f, 600.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
        //Enemy{Vector2{1500.f, 600.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")}

        Enemy slime = Enemy{Vector2{1800.f, 600.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};

        Enemy* enemies[]
        {
            &goblin, &slime
        }; 

        for(auto enemy : enemies){
            enemy->setTarget(&knight);
        }
    
    

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

        if(!knight.getAlive()) //character is not alive
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
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

            for(auto enemy : enemies)
            { enemy->tick(GetFrameTime()); }
            
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true){
            for(auto enemy : enemies)
            {
            if(CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetCollisionRec()) == true)
            {
                enemy->setAlive(false);
            } 
            }
        }
        

        EndDrawing();
    }
}