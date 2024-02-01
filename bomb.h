#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef BOMB_H
#define BOMB_H

class Bomb{
private:
Texture tex, fireDown, fireRight, fireLeft;
Sprite sprite;
float speed = 0.2;
float i,j; //direction of bomb.
float positionX,positionY;

public:

Bomb(int x=0, int y=0, float I=0, float J=1, std::string S= "0");
void move(float I=-10, float J=-10);
void setDirection(float I,float J);

Sprite& getSprite();
float getPositionX();
float getPositionY();
void setPos(float i, float j);

void setFireTexture(int i);


};




#endif