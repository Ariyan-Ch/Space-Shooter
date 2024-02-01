#include "PowerUp.h"

PowerUp::PowerUp(std::string s): AddOn(s){ }

bool PowerUp::getEquipped(){
    return isEquipped;
}
void PowerUp::setEquipped(bool b){
    isEquipped = b;
}
