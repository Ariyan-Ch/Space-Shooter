#include <SFML/Graphics.hpp>
#include <string.h>
#include "enemy.h"
using namespace sf;

#ifndef MONSTER_H
#define MONSTER_H


class Monster: public Enemy{

private:
bool goingRight = true;
bool goingLeft = false;

bool firstOn = true, secondOn = false, thirdOn = false, fourthOn = false;

Sprite light;
Texture lightTexture1, lightTexture2, lightTexture3, lightTexture4;
float speed = 0.3;

public:

Monster(std::string s,float del = 2);
float getDelay();
void monsterMovement();
Sprite& getSpriteBomb(int j=0);

void fire(float&a,int b=0);

};

#endif