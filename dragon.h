#include <SFML/Graphics.hpp>
#include <string.h>
#include "enemy.h"

using namespace sf;

#ifndef DRAGON_H
#define DRAGON_H


class Dragon: public Enemy{

private:

float speed = 0.3;

public:

Dragon(std::string s,Bomb* b, float del = 2);

float getDelay();

// Sprite& getSpriteBomb(int j=0);

void fire(float&a, int b=0);
void unfire(int i);

};

#endif