#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef BULLET_H
#define BULLET_H

class Bullet{
private:
Texture tex,texL,texR;
Texture FireTex, FireTexL, FireTexR;

Texture Tex0,Tex1,Tex2,Tex3,Tex4,Tex5,Tex6;

Sprite sprite;
float speed = 0.9;
float i,j; //direction of bullet.// currently it goes up only up
float positionX,positionY;

public:

Bullet(int x=0, int y=0, float I=0, float J=-1);
void move(float I=-10, float J=-10);
void setDirection(float I,float J);

Sprite& getSprite();
float getPositionX();
float getPositionY();
void setPos(float i, float j);
void setFire(float I,float J);

void fire0(float I, float J);
void fire1(float I, float J);
void fire2(float I, float J);
void fire3(float I, float J);
void fire4(float I, float J);
void fire5(float I, float J);
void fire6(float I, float J);

};




#endif