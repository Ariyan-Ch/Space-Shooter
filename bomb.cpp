#include "bomb.h"

Bomb::Bomb(int x, int y, float I, float J,std::string S){
    tex.loadFromFile("img/bomb.png");
    fireDown.loadFromFile("img/dragonFireDown.png");
    fireRight.loadFromFile("img/dragonFireRight.png");
    fireLeft.loadFromFile("img/dragonFireLeft.png");

    if(S=="0")
        sprite.setTexture(tex);
    else
        sprite.setTexture(fireDown);
    sprite.setPosition(x,y);
    positionX=x;
    positionY=y;
    i = I;
    j = J;
}

void Bomb::move(float I, float J){
    if(I==-10&&J==-10){
        I=i; J=j;
    }
    sprite.move(I*speed,J*speed);
    positionX +=I*speed;
    positionY +=J*speed;
}

void Bomb::setDirection(float I,float J){
    i=I; j=J;
}

Sprite& Bomb::getSprite(){
    return sprite;
}
float Bomb::getPositionX(){
    return positionX;
}
float Bomb::getPositionY(){
    return positionY;
}
void Bomb::setPos(float i, float j){
    sprite.setPosition(i,j);
    positionX = i;
    positionY = j;
}

void Bomb::setFireTexture(int i){
    if(i==0)
        sprite.setTexture(fireDown);
    else if(i==1)
        sprite.setTexture(fireLeft);
    else if(i==2)
        sprite.setTexture(fireRight);
}