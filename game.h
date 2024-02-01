#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>

#include "menu.cpp"

#include "bullet.h"
#include "player.cpp"

#include "bomb.h"
#include "invader.cpp"
#include "alpha.cpp"
#include "beta.cpp"
#include "gamma.cpp"

#include "Fire.cpp"
#include "Danger.cpp"
#include "Lives.cpp"
#include "PowerUp.cpp"
#include "monster.cpp"
#include "dragon.cpp"

using namespace std;
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;


#ifndef GAME_H
#define GAME_H
class Game
{
private:
Font font;
Text currentScoreObject, highScoreObject;
Sprite background,background_over; //Game background sprite
Texture bg_texture,bg_over;
Texture lvl1_1,lvl1_2,lvl1_3,lvl2_1,lvl2_2,lvl2_3,lvl3_1,lvl3_2,lvl3_3, endScreen;
Sprite lvlScreen;
Texture badge1,badge2,badge3,noBadge;
Sprite badgeSprite;

SoundBuffer bufferPewPew,bufferOof;
Sound PewPew,Oof;

Player* p; //player 
Bullet b[100]{1200,1200};   //bullets, all outside the screen
Bomb bomba[800]{1400,1400}; //bombs, all outside the screen 


int totalAlpha = 25;
int totalBeta = 25;
int totalGamma = 25;


int totalEnemies = totalAlpha+totalBeta+totalGamma;
int activeEnemyCount = 0;

AddOn** addOns;
Enemy** enemy;
Enemy** activeEnemies;

Enemy* monsterEnemy;
Enemy* dragonEnemy;
std::string s= "h";
Bomb bombDragon[10]= {  //initializing all elements with that parameter list
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
    Bomb(1400, 1400, 0, 1, "fire"),
};

short int level = 0;

Menu m;

public:

Game();  //constructor

int start_game();   //main game loop runs in this 

void removeEnemy(int j); // removes enemy when bullets collide

//============================================== level formation functions
void resetFormation();      //erases enemy formations
void setFormationRectangle();   //empty Rectangle Formation
void setFormationTriangle();    //empty Triangle Formation
void setFormationCross();       //cross 
void setFormationCircle();      //empty circle
void setFormationDiamond();      //diamond formation
void setFormationHeart();       //heart formation
void setFormationTriangleFill();    //filled triangle formation
void setFormationCircleFill();      //filled circle formation
void setFormationRectangleFill();   //filled Rectangle Formation

void updateScores(int currentScore, std::string name);  //updates the highscores.txt file
std::string findHighScore();

void adjustDifficulty(int i); //takes the level as parameter and then slightly increases the speed of all enemies.
int monsterSpawn(RenderWindow& window);
int dragonSpawn(RenderWindow& window);

//startMenu
void startMenu();


};

#endif