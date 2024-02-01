#include "Lives.h"

Lives::Lives(std::string s): AddOn(s){ }

bool Lives::getEquipped(){
    return isEquipped;
}
void Lives::setEquipped(bool b){
    isEquipped = b;
}

