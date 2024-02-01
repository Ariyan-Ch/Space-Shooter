#include "dragon.h"

Dragon::Dragon(std::string s,Bomb* b, float del): Enemy(s,b){
    type=0;
    delay = del;

    x = 360;
    y = 20;
    enemySprite.setPosition(x,y);
    enemySprite.setScale(1,1);
    for(int i=0;i<10;i++){
        bombs[i]->setFireTexture(0);
        bombs[i]->getSprite().setScale(0.7,0.7);
    }
}

float Dragon::getDelay(){
    return delay;
}
void Dragon::unfire(int i){	//removes that bullet
	bombs[i]->setPos(1400,1400);
	Bomb* temp = bombs[i];
	bombs[i] = bombs[bombSize-1];
	bombs[bombSize-1] = temp;
	bombSize--;
}

void Dragon::fire(float&a,int b){
    if(a>1){
        if(b==0){
            bombs[bombSize]->setDirection(0,1);
            bombs[bombSize]->setFireTexture(0);
            bombs[bombSize]->setPos(430,400);
            bombSize++;
        }
        else if(b==1){
            bombs[bombSize]->setDirection(-0.8,0.8);
            bombs[bombSize]->setFireTexture(1);
            bombs[bombSize]->setPos(380,400);
            bombSize++;
        }
        else if(b==2){
            bombs[bombSize]->setDirection(0.8,0.8);
            bombs[bombSize]->setFireTexture(2);
            bombs[bombSize]->setPos(480,400);
            bombSize++;
        }
        a = 0;
    }

    for(int i=0;i<bombSize;i++)
        bombs[i]->move();
}