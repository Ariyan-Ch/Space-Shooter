#include <SFML/Graphics.hpp>
#include <string.h>
#include "bomb.h"
using namespace sf;

#ifndef ENEMY_H
#define ENEMY_H
#include "bomb.cpp"

class Enemy{

protected:
Sprite enemySprite;
Texture enemyTexture;
float x,y;          //their exact positions.
float delay;
int bombSize = 0;
Bomb* bombs[10];
short int type;

public:

Enemy(std::string s, Bomb* b = NULL);
virtual float getDelay() = 0;
virtual void monsterMovement();
float getX();
float getY();

void setPos(float i = 1200, float j = 1200);
void moveBomb(int i, float x = -10, float y = -10);

virtual void unfire(int i);
virtual void fire(float&a,int b=0);


Sprite& getSprite();
int getbombSize();
virtual Sprite& getSpriteBomb(int j=0);
float getBombPos_X(int i);
float getBombPos_Y(int i);
short int getType();
void setDelay(float d);

};



#endif