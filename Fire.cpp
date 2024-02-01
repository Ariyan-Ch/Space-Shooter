#include "Fire.h"

Fire::Fire(std::string s): AddOn(s){ }

bool Fire::getEquipped(){
    return isEquipped;
}
void Fire::setEquipped(bool b){
    isEquipped = b;
}
