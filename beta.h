#include <SFML/Graphics.hpp>
#include <string.h>
#include "invader.h"
using namespace sf;

#ifndef BETA_H
#define BETA_H


class Beta: public Invader{

private:


public:
Beta(std::string s,Bomb* b, float del = 3);
float getDelay();

};





#endif