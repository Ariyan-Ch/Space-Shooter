#include <SFML/Graphics.hpp>
#include <string.h>
#include "invader.h"

using namespace sf;

#ifndef GAMMA_H
#define GAMMA_H


class Gamma: public Invader{

private:


public:
Gamma(std::string s,Bomb* b, float del = 2);
float getDelay();

};





#endif