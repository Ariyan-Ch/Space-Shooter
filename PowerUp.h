#include <SFML/Graphics.hpp>
#include <iostream>
#include "AddOn.h"
using namespace sf;

#ifndef POWERUP_H
#define POWERUP_H

class PowerUp: public AddOn{
    private:

    bool isEquipped = false;

    public:
    PowerUp(std::string s);
    bool getEquipped();
    void setEquipped(bool b);
    
};





#endif