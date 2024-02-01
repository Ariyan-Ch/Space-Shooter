#include "AddOn.h"

AddOn::AddOn(std::string s, int x, int y, float I, float J){
    tex.loadFromFile(s);
    sprite.setTexture(tex);
    sprite.setPosition(x,y);
    positionX=x;
    positionY=y;
    i = I;
    j = J;
}

void AddOn::move(float I, float J){
    if(I==-10&&J==-10){
        I=i; J=j;
    }
    sprite.move(I*speed,J*speed);
    positionX +=I*speed;
    positionY +=J*speed;
}
Sprite& AddOn::getSprite(){
    return sprite;
}
float AddOn::getPositionX(){
    return positionX;
}
float AddOn::getPositionY(){
    return positionY;
}
void AddOn::setPos(float i, float j){
    sprite.setPosition(i,j);
    positionX = i;
    positionY = j;
}