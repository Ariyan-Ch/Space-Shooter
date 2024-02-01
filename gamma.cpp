#include "gamma.h"

Gamma::Gamma(std::string s,Bomb* b, float del): Invader(s,b){
    type = 2;
    delay = del;
    enemySprite.setScale(0.75,0.6);
}
float Gamma::getDelay(){
    return delay;
}