#include <SFML/Graphics.hpp>
#include <string.h>
#include "enemy.h"


using namespace sf;

#ifndef INVADER_H
#define INVADER_H

#include "enemy.cpp"

class Invader: public Enemy{

protected:


public:
Invader(std::string s,Bomb* b);


};





#endif