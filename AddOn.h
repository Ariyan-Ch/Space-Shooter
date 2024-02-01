#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef ADDON_H
#define ADDON_H

class AddOn{
protected:
Texture tex;
Sprite sprite;
float speed = 0.25;
float i,j; //direction of ADDON.// goes down
float positionX,positionY;

public:

AddOn(std::string s, int x=0, int y=0, float I=0, float J=1);

void move(float I=-10, float J=-10);

virtual bool getEquipped()=0;
virtual void setEquipped(bool b) =0;

Sprite& getSprite();
float getPositionX();
float getPositionY();
void setPos(float i, float j);


};




#endif