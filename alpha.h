#include <SFML/Graphics.hpp>
#include <string.h>
#include "invader.h"
using namespace sf;

#ifndef ALPHA_H
#define ALPHA_H


class Alpha: public Invader{

private:


public:

Alpha(std::string s , Bomb* b,float del = 5);
float getDelay();

};





#endif