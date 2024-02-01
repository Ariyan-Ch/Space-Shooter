#include <SFML/Graphics.hpp>
#include <iostream>
#include "AddOn.h"
using namespace sf;

#ifndef FIRE_H
#define FIRE_H

class Fire: public AddOn{
    private:

    bool isEquipped = false;

    public:
    Fire(std::string s);
    bool getEquipped();
    void setEquipped(bool b);
    
};





#endif