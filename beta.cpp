#include "beta.h"

Beta::Beta(std::string s,Bomb* b, float del): Invader(s,b){
    type=1;
    delay = del;
    enemySprite.setScale(0.6,0.6);
}
float Beta::getDelay(){
    return delay;
}