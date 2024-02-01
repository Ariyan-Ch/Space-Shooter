#include <SFML/Graphics.hpp>
#include <iostream>
#include "AddOn.h"
using namespace sf;

#ifndef DANGER_H
#define DANGER_H
#include "AddOn.cpp"

class Danger: public AddOn{
    private:

    bool isEquipped = false;

    public:
    Danger(std::string s);
    bool getEquipped();
    void setEquipped(bool b);
    
};





#endif