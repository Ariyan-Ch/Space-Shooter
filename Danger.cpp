#include "Danger.h"

Danger::Danger(std::string s): AddOn(s){ }

bool Danger::getEquipped(){
    return isEquipped;
}
void Danger::setEquipped(bool b){
    isEquipped = b;
}
