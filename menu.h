#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#ifndef MENU_H
#define MENU_H
class Menu{
private:

Sprite background; //Game background sprite
Texture bg_texture;

Texture Texplay,Texinstructions,Texhighscores,Texexit;
Texture TexplayS,TexinstructionsS,TexhighscoresS,TexexitS;
Sprite PlayB,InstructionsB,HighscoresB,ExitB;

Sprite InstrucSprite,HsSprite;
Texture InstrucTexture,HsTexture;

Texture TexResume,TexResumeS;
Sprite ResumeB;

public:
//add menu attributes here
Menu();
int display_menu(); //main menu
int display_ins();  //instruction page  
int display_hs(Font& font);   //highscore page
std::string GetName(RenderWindow &window,Font &font);   //gets the screen where player enters their name
int display_pause(RenderWindow &window, Font &font);    //pause menu;
std::string getBadge(std::string playerName, Font &font);  //checks if the player name is among the top three scores.

};
#endif