#include "bullet.h"

Bullet::Bullet(int x, int y, float I, float J){
    tex.loadFromFile("img/PurpBullet.png");
    texL.loadFromFile("img/PurpBulletLeft.png");
    texR.loadFromFile("img/PurpBulletRight.png");

    FireTex.loadFromFile("img/fireBulletFront.png");
    FireTexR.loadFromFile("img/fireBulletRight.png");
    FireTexL.loadFromFile("img/fireBulletLeft.png");

    Tex0.loadFromFile("img/bullet0.png");
    Tex1.loadFromFile("img/bullet1.png");
    Tex2.loadFromFile("img/bullet2.png");
    Tex3.loadFromFile("img/bullet3.png");
    Tex4.loadFromFile("img/bullet4.png");
    Tex5.loadFromFile("img/bullet5.png");
    Tex6.loadFromFile("img/bullet6.png");
    
    sprite.setTexture(tex);
    sprite.setPosition(x,y);
    positionX=x;
    positionY=y;
    i = I;
    j = J;
}

void Bullet::move(float I, float J){
    if(I==-10&&J==-10){
        I=i; J=j;
    }
    sprite.move(I*speed,J*speed);
    positionX +=I*speed;
    positionY +=J*speed;
}

void Bullet::setDirection(float I,float J){
    i=I; j=J;
    if(i>0&&j>0 || i<0&&j<0)
        sprite.setTexture(texL);
    else if(i>0&&j<0 || i<0&&j>0)
        sprite.setTexture(texR);
    else 
        sprite.setTexture(tex);
}

Sprite& Bullet::getSprite(){
    return sprite;
}
float Bullet::getPositionX(){
    return positionX;
}
float Bullet::getPositionY(){
    return positionY;
}
void Bullet::setPos(float i, float j){
    sprite.setPosition(i,j);
    positionX = i;
    positionY = j;
}

void Bullet::setFire(float I,float J){
    i=I; j=J;
    if(i>0&&j>0 || i<0&&j<0)
        sprite.setTexture(FireTexL);
    else if(i>0&&j<0 || i<0&&j>0)
        sprite.setTexture(FireTexR);
    else 
        sprite.setTexture(FireTex);
}

void Bullet::fire0(float I, float J){
    
    sprite.setTexture(Tex0);
    i=I;j=J;

}
void Bullet::fire1(float I, float J){
    
    sprite.setTexture(Tex1);
    i=I;j=J;

}
void Bullet::fire2(float I, float J){
    
    sprite.setTexture(Tex2);
    i=I;j=J;

}
void Bullet::fire3(float I, float J){
    
    sprite.setTexture(Tex3);
    i=I;j=J;

}
void Bullet::fire4(float I, float J){
    
    sprite.setTexture(Tex4);
    i=I;j=J;

}
void Bullet::fire5(float I, float J){
    
    sprite.setTexture(Tex5);
    i=I;j=J;

}
void Bullet::fire6(float I, float J){
    
    sprite.setTexture(Tex6);
    i=I;j=J;

}