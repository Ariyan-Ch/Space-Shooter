#include <SFML/Graphics.hpp>
#include <iostream>
#include "AddOn.h"
using namespace sf;

#ifndef LIVES_H
#define LIVES_H

class Lives: public AddOn{
    private:

    bool isEquipped = false;

    public:
    Lives(std::string s);
    bool getEquipped();
    void setEquipped(bool b);
    
};





#endif