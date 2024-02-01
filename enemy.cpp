#include "enemy.h"

Enemy::Enemy(std::string s,Bomb* b){
    if(b!=NULL){
        for(int i=0;i<10;i++){
            bombs[i] = &b[i];
        }
    }
    enemyTexture.loadFromFile(s);
    enemySprite.setTexture(enemyTexture);
    x = 1200, y = 1200;
    enemySprite.setPosition(x,y);
    enemySprite.setScale(0.75,0.75);
}

void Enemy::monsterMovement(){}

void Enemy::setPos(float i, float j){
    x = i; y = j;
    enemySprite.setPosition(i,j);
}

Sprite& Enemy::getSprite(){return enemySprite;}

int Enemy::getbombSize(){return bombSize;}

void Enemy::moveBomb(int i, float x, float y){
	bombs[i]->move(x,y);
}

Sprite& Enemy::getSpriteBomb(int j){
    return bombs[j]->getSprite();
}

float Enemy::getBombPos_X(int i){
    return bombs[i]->getPositionX();
}
float Enemy::getBombPos_Y(int i){
    return bombs[i]->getPositionY();
}

void Enemy::fire(float&a,int b){	//adds a bullet| by default, it goes down only
    if(a>delay){
      
        if(type==0 || type == 1){
            bombs[bombSize]->setPos(x+45.3,y+67);
            bombSize++;
        }
        else if(type==2){
            bombs[bombSize]->setPos(x+45.3,y+87);
            bombSize++;
        }
        a=0;
    }
}
void Enemy::unfire(int i){	//removes that bullet
	bombs[i]->setPos(1200,1200);
	Bomb* temp = bombs[i];
	bombs[i] = bombs[bombSize-1];
	bombs[bombSize-1] = temp;
	bombSize--;
}
short int Enemy::getType(){
    return type;
}

void Enemy::setDelay(float d){
    delay = d;
}

float Enemy::getX(){return x;}
float Enemy::getY(){return y;}