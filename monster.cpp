#include "monster.h"

Monster::Monster(std::string s, float del): Enemy(s){
    type=0;
    delay = del;
    //enemySprite.setScale(0.5,0.5);
    x = 400;
    y = 60;
    enemySprite.setPosition(x,y);
    lightTexture1.loadFromFile("img/monsterElectricity1.png");
    lightTexture2.loadFromFile("img/monsterElectricity2.png");
    lightTexture3.loadFromFile("img/monsterElectricity3.png");
    lightTexture4.loadFromFile("img/monsterElectricity4.png");
    light.setTexture(lightTexture1);
    light.setPosition(x+60,y+250);
    light.setScale(1,1.2);
}
float Monster::getDelay(){
    return delay;
}

void Monster::monsterMovement(){
    if(goingRight){
        if(x<730){
            enemySprite.move(1*speed,0);
            x += 1*speed;
            light.move(1*speed,0);
        }
        else{
            goingRight = false;
            goingLeft = true;
        }
    }
    else if(goingLeft){
        if(x>1){
            enemySprite.move(-1*speed,0);
            x-= 1*speed;
            light.move(-1*speed,0);
        }
        else{
            goingRight = true;
            goingLeft = false;
        }
    }
}

Sprite& Monster::getSpriteBomb(int j){
    return light;
}
void Monster::fire(float&a,int b){    //gives the electricity animation
    if(firstOn){
        if(a>0.044){
            secondOn = true;
            firstOn = false;
            a = 0;
        }
    }
    else if(secondOn){
        if(a>0.044){
            secondOn = false;
            thirdOn = true;
            a = 0;
        } 
    }
    else if(thirdOn){
        if(a>0.044){
            thirdOn = false;
            fourthOn = true;
            a = 0;
        } 
    }
    else if(fourthOn){
        if(a>0.044){
            fourthOn = false;
            firstOn = true;
        }
    }

    if(firstOn){
        light.setTexture(lightTexture1);
    }
    else if(secondOn){
        light.setTexture(lightTexture2);
    }
    else if(thirdOn){
        light.setTexture(lightTexture3);
    }
    else if(fourthOn)
        light.setTexture(lightTexture4);
}