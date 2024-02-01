#include <SFML/Graphics.hpp>
#include <string.h>
#include "bullet.h"
#include "AddOn.h"
using namespace sf;

#ifndef PLAYER_H
#define PLAYER_H
#include "bullet.cpp"


class Player{
private:
Texture tex;
Texture texRot_L,texRot_R,texRot_LB, texRot_RB; //rotated textures


Texture protectionTexture;
Sprite protectionBubble;

Texture liveIconTex;
Sprite liveIcons[20];

Sprite sprite;
Bullet* bullets[100];

AddOn * addOns[4];

float playerHitCoolDown = 3;

int playerLives = 3;
int bulletSize=0;
float speed=0.5;
int x,y;
float textureRadius = 40.0;
float center_x, center_y;	//keep tracks of the center of the player spaceship at all times


public:
//===== Constructor
Player(std::string png_path, Bullet* p, AddOn** adds);

//====== functions

void changeTexture(Texture& tex);
void rotate(std::string s);

void fire(float i=0, float j=-1);
void unfire(int i);

void wrap(std::string side);
void move(std::string s);

float getCenter_x();    //getters
float getCenter_y();
float getTextureRadius();
int getbulletSize();
float getBulletPos_X(int x);
float getBulletPos_Y(int y);
Sprite& getSprite();
Sprite& getSpriteBullet(int i);
int getLives();
float getLiveX();
float getLiveY();
Sprite& getLiveSprite(int i);
float getHitCoolDown();
Sprite& getProtectionSprite();

Sprite& getAddOnSprite(int i);
bool unFallAddOn(int i);
bool addOnCollision(int i);

void setAddOnPosition(int i, float x, float y);
void moveAddOn(int i);

void setLives(int l);
void moveBullet(int i, float x = -10, float y = -10);

void setPlayerPos(float xx, float yy);
void UnEquipAddOn();
bool isFireEquipped();
bool isPowerEquipped();

};

#endif