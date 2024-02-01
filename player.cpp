#include "player.h"


Player::Player(std::string png_path, Bullet* p, AddOn** adds){
for(int i=0;i<100;i++){
	bullets[i] = &p[i];
}
for(int i=0;i<4;i++)
	addOns[i] = adds[i];

tex.loadFromFile(png_path);

std::string tempPath = png_path;	//path for rotated images
tempPath.erase(tempPath.size()-4);
tempPath = tempPath+"_L.png";
texRot_L.loadFromFile(tempPath);
tempPath.erase(tempPath.size()-4);
tempPath = tempPath+"B.png";
texRot_LB.loadFromFile(tempPath);
tempPath.erase(tempPath.size()-6);
tempPath = tempPath+"R.png";
texRot_R.loadFromFile(tempPath);
tempPath.erase(tempPath.size()-4);
tempPath = tempPath+"B.png";
texRot_RB.loadFromFile(tempPath);

sprite.setTexture(tex);
x=500;y=770;

center_x = x+textureRadius;
center_y = y+textureRadius;

protectionTexture.loadFromFile("img/playerProtection.png");
protectionBubble.setTexture(protectionTexture);

sprite.setPosition(x,y);

protectionBubble.setPosition(x,y);
protectionBubble.setScale(0.75,0.75);

sprite.setScale(0.75,0.75);

liveIconTex.loadFromFile("img/LivesIcon.png");

for(int i=0;i<20;i++){
	liveIcons[i].setTexture(liveIconTex);
	liveIcons[i].setPosition(750+(i*20),880);
}


}

void Player::changeTexture(Texture& tex){	//mostly used for rotating the ship when moving diagonally
	sprite.setTexture(tex);
}
void Player::rotate(std::string s){	//sets the rotated texture
	if(s=="L")
		sprite.setTexture(texRot_L);
	else if(s=="R")
		sprite.setTexture(texRot_R);
	else if(s=="LB")
		sprite.setTexture(texRot_LB);
	else if(s=="RB")
		sprite.setTexture(texRot_RB);
	else
		sprite.setTexture(tex);
}

void Player::fire(float i, float j){	//adds a bullet| by default, it goes up only
	if(addOns[0]->getEquipped()){	//first checks if the powerUp is equipped
		bullets[bulletSize]->fire0(-0.7,-0.7);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire1(-0.6,-0.85);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire2(-0.25,-0.96);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire3(0,-1);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire4(0.25,-0.96);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire5(0.6,-0.85);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
		bullets[bulletSize]->fire6(0.7,-0.7);
		bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		bulletSize++;
	}
	else{
		if(addOns[1]->getEquipped()){	//then checks if the fire is equipped
			bullets[bulletSize]->setFire(i,j);
		}
		else
			bullets[bulletSize]->setDirection(i,j);

		if(i<0&&j<0){
			bullets[bulletSize]->setPos(center_x-18,center_y-20);
		}
		else if(i>0&&j<0){
			bullets[bulletSize]->setPos(center_x-14,center_y-20);
		}
		else if(i<0&&j>0){
			bullets[bulletSize]->setPos(center_x-60,center_y+28);
		}
		else if(i>0&&j>0){
			bullets[bulletSize]->setPos(center_x+23,center_y+28);
		}

		else{
			bullets[bulletSize]->setPos(center_x-16.5,center_y-50);
		}
		bulletSize++;
	}
}
void Player::unfire(int i){	//removes that bullet
	bullets[i]->setPos(1200,1200);
	Bullet* temp = bullets[i];
	bullets[i] = bullets[bulletSize-1];
	bullets[bulletSize-1] = temp;
	bulletSize--;
}

void Player::wrap(std::string side){	//wraps the player when it goes out of the screen to appear from the other side.
	if(side=="left"){
		sprite.setPosition(1000,center_y-textureRadius);
		center_x= 1000+textureRadius;
	}
	else if(side=="right"){
		sprite.setPosition(0- 2*textureRadius,center_y-textureRadius);
		center_x= 0-textureRadius;
	}
	else if(side=="up"){
		sprite.setPosition(center_x-textureRadius,855);
		center_y = 855+textureRadius;
	}
	else if(side=="down"){
		sprite.setPosition(center_x-textureRadius, 0-2*textureRadius);
		center_y = 0-textureRadius;
	}
}
void Player::setPlayerPos(float xx,float yy){
	sprite.setPosition(xx,yy);
	center_x = xx+=textureRadius;
	center_y = yy+=textureRadius;
}

void Player::move(std::string s){	//moves the player

float delta_x=0,delta_y=0;

if(s=="l")
	delta_x = -1;
else if(s=="r")
	delta_x = 1;
if(s=="u")
	delta_y=-1;
else if(s=="d")
	delta_y=1;

delta_x*=speed;
delta_y*=speed;

sprite.move(delta_x, delta_y);
center_x+=delta_x;
center_y+=delta_y;
}


//====== Getters
float Player::getCenter_x(){return center_x;}
float Player::getCenter_y(){return center_y;}
float Player::getTextureRadius(){return textureRadius;}
int Player::getbulletSize(){return bulletSize;}

float Player::getBulletPos_X(int x){
	return bullets[x]->getPositionX();
}
float Player::getBulletPos_Y(int y){
	return bullets[y]->getPositionY();
}

Sprite& Player::getSprite(){return sprite;}

Sprite& Player::getSpriteBullet(int i){
	return bullets[i]->getSprite();
}

void Player::moveBullet(int i, float x, float y){
	bullets[i]->move(x,y);
}
int Player::getLives(){
	return playerLives;
}
void Player::setLives(int l){
	playerLives = l;
}

Sprite& Player::getLiveSprite(int i){
	return liveIcons[i];
}

float Player::getHitCoolDown(){
	return playerHitCoolDown;
}

Sprite& Player::getProtectionSprite(){
	return protectionBubble;
}

void Player::setAddOnPosition(int i, float x, float y){
	addOns[i]->setPos(x,y);
}

void Player::moveAddOn(int i){
	addOns[i]->move();
}
Sprite& Player::getAddOnSprite(int i){
	return addOns[i]->getSprite();
}

bool Player::unFallAddOn(int i){
	if(addOns[i]->getPositionY()>900){
		addOns[i]->getSprite().setPosition(-10,-10);
		return true;
	}
	return false;
}
bool Player::addOnCollision(int i){
	if((center_x-textureRadius) < (addOns[i]->getSprite().getGlobalBounds().left + addOns[i]->getSprite().getGlobalBounds().width) &&
		(center_x+textureRadius) > addOns[i]->getSprite().getGlobalBounds().left &&
		(center_y-textureRadius) < (addOns[i]->getSprite().getGlobalBounds().top + addOns[i]->getSprite().getGlobalBounds().height) &&
		(center_y+textureRadius) > addOns[i]->getSprite().getGlobalBounds().top){
		
		addOns[i]->getSprite().setPosition(-10,-10);
		if(i==3){
			playerLives++;
		}
		else if(i==1 || i==0){
			addOns[i]->setEquipped(true);
		}
		return true;
	}
	return false;
}

void Player::UnEquipAddOn(){
	addOns[0]->setEquipped(false);
	addOns[1]->setEquipped(false);
	addOns[2]->setEquipped(false);
	addOns[3]->setEquipped(false);
}

bool Player::isFireEquipped(){
	return addOns[1]->getEquipped();
}
bool Player::isPowerEquipped(){
	return addOns[0]->getEquipped();
}