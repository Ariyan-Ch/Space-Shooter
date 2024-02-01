#include "alpha.h"

Alpha::Alpha(std::string s,Bomb* b, float del): Invader(s,b){
    type=0;
    delay = del;
    enemySprite.setScale(0.60,0.60);
}
float Alpha::getDelay(){
    return delay;
}