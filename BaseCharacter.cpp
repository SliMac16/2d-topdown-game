#include "BaseCharacter.h"


BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    //update animation frame
        runningTime += deltaTime;
        if(runningTime >= updateTime){
            frame++;
            runningTime = 0.f;
            if(frame > MaxFrames) frame = 0;

        }
        //draw the base character
        Rectangle source{frame * width, 0.f, rightLeft * width, height};
        Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}


void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec(){
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}