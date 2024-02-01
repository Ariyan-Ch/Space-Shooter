#include "game.h"




//============================================== constructor
Game::Game(){
addOns = new AddOn*[4];
addOns[0] = new PowerUp("img/AddOnPowerUp.png");
addOns[1] = new Fire("img/AddOnFire.png");
addOns[2] = new Danger("img/AddOnDanger.png");
addOns[3] = new Lives("img/AddOnLives.png");

p=new Player("img/player_ship.png", b, addOns); //passing the bullets to player
bg_texture.loadFromFile("img/BG.jpg");
bg_over.loadFromFile("img/BG_over2.png");
background_over.setTexture(bg_over);
background.setTexture(bg_texture);

enemy = new Enemy*[totalEnemies];   //creates an array of Enemy pointers. Each of that pointer will have Alpha,beta,& gamma dynammically allocated
activeEnemies = new Enemy*[totalEnemies];

int a = 0;
for(int i=0;i<totalAlpha;i++){
    enemy[i] = new Alpha("img/alpha.png",bomba+a);
    enemy[i]->setPos(1200,1200);
    a+=10;
}
for(int i=totalAlpha;i<totalAlpha+totalBeta;i++){
    enemy[i] = new Beta("img/beta.png",bomba+a);
    enemy[i]->setPos(1200,1200);
    a+=10;
}
for(int i=totalAlpha+totalBeta;i<totalEnemies;i++){
    enemy[i] = new Gamma("img/gamma.png",bomba+a);
    enemy[i]->setPos(1200,1200);
    a+=10;
}


lvl1_1.loadFromFile("img/lvls/lvlScreen11.png");
lvl1_2.loadFromFile("img/lvls/lvlScreen12.png");
lvl1_3.loadFromFile("img/lvls/lvlScreen13.png");
lvl2_1.loadFromFile("img/lvls/lvlScreen21.png");
lvl2_2.loadFromFile("img/lvls/lvlScreen22.png");
lvl2_3.loadFromFile("img/lvls/lvlScreen23.png");
lvl3_1.loadFromFile("img/lvls/lvlScreen31.png");
lvl3_2.loadFromFile("img/lvls/lvlScreen32.png");
lvl3_3.loadFromFile("img/lvls/lvlScreen33.png");
endScreen.loadFromFile("img/menu/endMenu.png");

font.loadFromFile("font/EvilEmpire.ttf");
currentScoreObject.setFont(font);
highScoreObject.setFont(font);
highScoreObject.setFillColor(sf::Color::White);
currentScoreObject.setFillColor(sf::Color::White);
currentScoreObject.setCharacterSize(50);
currentScoreObject.setPosition(15,880);  

noBadge.loadFromFile("img/noBadge.png");
badge1.loadFromFile("img/firstBadge.png");
badge2.loadFromFile("img/secondBadge.png");
badge3.loadFromFile("img/thirdBadge.png");
badgeSprite.setTexture(noBadge);

monsterEnemy = new Monster("img/monster1.png");
dragonEnemy = new Dragon("img/dragon.png",bombDragon);

bufferPewPew.loadFromFile("sound/pewpew.wav");
bufferOof.loadFromFile("sound/oof.wav");
PewPew.setBuffer(bufferPewPew);
Oof.setBuffer(bufferOof);

}

//============================================== constructor

//============================================== main game
int Game::start_game()
{
    srand(time(0));
    level=0;
    activeEnemyCount = 0;
    RenderWindow window(VideoMode(1000, 950), title);
    std::string playerName = m.GetName(window,font);        //gets name from the user
    std::string badgeStatus = m.getBadge(playerName,font);  //checks if playername matches the top rankers
    if(badgeStatus=="first")
        badgeSprite.setTexture(badge1);
    else if(badgeStatus=="second")
        badgeSprite.setTexture(badge2);
    else if(badgeStatus=="third")
        badgeSprite.setTexture(badge3);
    else
        badgeSprite.setTexture(noBadge);
        
    Clock clock;
    p->setLives(3); //will give it three lives at the start everytime.
    resetFormation();
    bool scoreChanged = true;
    int currentScore = 0;

    
    bool canAddOnFall = true;
    float addOnTimer = 0;
    int chosenAddOn = -1;
    bool addOnFalling = false;

    float *timers = new float[totalEnemies]{0}; //timers for enemy shooting
    float playerHitCoolDown = 0;

    bool isGameEnd = false; //ends the game
    float timer=0;  //counter for player bullets
    float monsterTimer = 0, dragonTimer =0;
    float levelAniTimer=0;  //level screen timer.
    bool levelAnimation = false;
    bool isNewLevel = false;    //helps the new level conditions
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; ;
        playerHitCoolDown += time;
        for(int i=0;i<totalEnemies;i++){
            timers[i]+=time;
        }
        levelAniTimer += time;
        addOnTimer +=time;
        monsterTimer += time;
        dragonTimer += time;

        string rotation = "no"; //rotation checking variable

 	    Event e;
        while (window.pollEvent(e))
        {  
        if (e.type == Event::Closed) // If cross/close is clicked/pressed
            window.close(); //close the game                        	    
        }

        if(Keyboard::isKeyPressed(Keyboard::P)){    //pauses the game
            if(m.display_pause(window, font)==0)
                break;
        }

    //=================================================== 
    //----------this code changes level and adds the screen before each level

    if(p->getLives()==0)
        break;
    if(activeEnemyCount==0 && !isNewLevel){
        level++;
        isNewLevel = true;
        levelAnimation = true;
        levelAniTimer = 0;
    }
    if(activeEnemyCount>0){ isNewLevel =false;}

    if(levelAnimation){ //shows the level screens
        switch(level){  case 1: lvlScreen.setTexture(lvl1_1);break;case 2: lvlScreen.setTexture(lvl1_2);break;case 3:lvlScreen.setTexture(lvl1_3);break;
                        case 4: lvlScreen.setTexture(lvl2_1);break;case 5: lvlScreen.setTexture(lvl2_2);break;case 6:lvlScreen.setTexture(lvl2_3);break;
                        case 7: lvlScreen.setTexture(lvl3_1);break;case 8: lvlScreen.setTexture(lvl3_2);break;case 9:lvlScreen.setTexture(lvl3_3);break;
                        case 10: isGameEnd = true; break;
                    }
        if(isGameEnd)
            break;
        window.clear(Color::Black);
        window.draw(lvlScreen);
        window.display();
        if(levelAniTimer > 2){
            levelAnimation = false;
        }
    }
    //=========================================================
    else{ 
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards


	////////////////////////////////////////////////
	/////  Call your functions here            ////
    
    //====================================wraps around the screen
    if(p->getCenter_x()+p->getTextureRadius()<0)
        p->wrap("left");
    else if(p->getCenter_x()-p->getTextureRadius()>1000)
        p->wrap("right");
    if(p->getCenter_y()+p->getTextureRadius()<0)
        p->wrap("up");
    else if(p->getCenter_y()-p->getTextureRadius()>855)
        p->wrap("down");

    //====================================Rotates spaceship when moving diagonally
    if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Up))
        rotation = "L";
    else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Up))
        rotation = "R";
    else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Down))
        rotation = "RB";
    else if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Down))
        rotation = "LB";
    else
        rotation = "no";

    p->rotate(rotation);    

    //------------------------------------------------------------- firing of byllets
    if(timer>0.3 && Keyboard::isKeyPressed(Keyboard::V)){ 
        if(rotation == "L"){
            p->fire(-0.8,-0.8);
        }
        else if(rotation == "R"){
            p->fire(0.8,-0.8);
        }
        else if(rotation == "RB"){
            p->fire(0.8,0.8);
        }
        else if(rotation == "LB"){
            p->fire(-0.8,0.8);
        }
        else{
            p->fire(0,-1);
        }
        PewPew.play();
        timer=0;
    } 
        if(monsterTimer>15){   //randomizing monster
            int rndm = rand()%10;
            std::cout<<"tried"<<std::endl;
            if(true){
                if(monsterSpawn(window) == 1){
                    return 5;
                }
                currentScore += 40;
                scoreChanged = true;
                clock.restart();
                playerHitCoolDown = 0;
            }
            monsterTimer =0;
        }
        if(dragonTimer>15){
        int rndm = rand()%10;
       // std::cout<<"tried"<<std::endl;
        if(rndm==5){
            if(dragonSpawn(window) == 1){
                return 5;
            }
            currentScore += 50;
            scoreChanged = true;
            clock.restart();
            playerHitCoolDown = 0;
        }
         dragonTimer =0;
        }
    //================================================================== Levels

        
        //========Level 1

        if(level==1 && activeEnemyCount==0){    //phase 1
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;  //resets timer for all enemies so their bombs are randomized
            }
            resetFormation();   //resets enemy formations
            setFormationTriangle(); //sets new formation
            p->setPlayerPos(500,770);   //resets player's starting point.
            playerHitCoolDown=0;    //resets protection counter.
            p->UnEquipAddOn();  //the fire or powerUp addOn as well
            adjustDifficulty(level);    //increases or decreases the delay of enemies based on level
        }
        else if(level==2 && activeEnemyCount==0){ //phase 2
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationRectangle();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }

        else if(level==3 && activeEnemyCount==0){ //phase 3
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationCross();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
         //========Level 2
        else if(level ==4 && activeEnemyCount==0){ //phase 1
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationCircle();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
        else if(level ==5 && activeEnemyCount==0){ //phase 2
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationDiamond();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
        else if(level ==6 && activeEnemyCount==0){  //phase 3
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationHeart();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
         //========Level 3
        else if(level==7 && activeEnemyCount==0){   //phase 1
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationTriangleFill();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
        else if(level==8 && activeEnemyCount==0){   //phase 2
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationCircleFill();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }
        else if(level==9 && activeEnemyCount==0){   //phase 3
            for(int i=0;i<totalEnemies;i++){
                timers[i] = (float)(rand()%50)/10;
            }
            resetFormation();
            setFormationRectangleFill();
            p->setPlayerPos(500,770);
            playerHitCoolDown=0;
            p->UnEquipAddOn();
            adjustDifficulty(level);
        }

    //================================================================== Levels

    if(canAddOnFall && addOnTimer>=1){
        if(rand()%9==5){
            addOnFalling = true;
            canAddOnFall = false;
            chosenAddOn = rand()%4;
            p->setAddOnPosition(chosenAddOn,rand()%1000,10);
        }
        p->UnEquipAddOn();
        //std::cout<<"didn't work\n"<<std::endl;
        addOnTimer = 0;
    }   //addon randomization

	/////  Call your functions here            ////
	//////////////////////////////////////////////

	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background

    if(addOnFalling){
        if(p->unFallAddOn(chosenAddOn)){
            addOnFalling = false;
            canAddOnFall = true;
            addOnTimer = 0;
            if(chosenAddOn==2){ //danger addOn
                scoreChanged=true;  //score increase
                currentScore+=5;
            }
        }
        else if(p->addOnCollision(chosenAddOn)){
            addOnFalling = false;
            canAddOnFall = true;
            addOnTimer = 0;
            if(chosenAddOn==2 && playerHitCoolDown > p->getHitCoolDown()){ //danger AddOn
                p->setPlayerPos(500,750);   //death
                p->setLives(p->getLives()-1);
                playerHitCoolDown=0;
                Oof.play();
            }
            else if(chosenAddOn==1 || chosenAddOn == 0){
                if(chosenAddOn==0)
                    playerHitCoolDown = -2;
                addOnTimer = -4;
            }
        }

        p->moveAddOn(chosenAddOn);
        window.draw(p->getAddOnSprite(chosenAddOn));
    }

    for(int i=0;i<p->getbulletSize();i++){   // draws bullets and moves them
        
        if(p->getBulletPos_X(i)<-30 || p->getBulletPos_X(i)>1010 || p->getBulletPos_Y(i)<-30|| p->getBulletPos_Y(i)>870){
            p->unfire(i);
        }
        else{
            p->moveBullet(i);
            window.draw(p->getSpriteBullet(i));
        }
        for(int j=0;j<activeEnemyCount;j++){    //for enemy remover
            float left = activeEnemies[j]->getSprite().getGlobalBounds().left - 10;
            float right = left+activeEnemies[j]->getSprite().getGlobalBounds().width + 20;
            float top = activeEnemies[j]->getSprite().getGlobalBounds().top;
            float bottom = top+activeEnemies[j]->getSprite().getGlobalBounds().height-15;

            if( (p->getBulletPos_X(i) + 5) >= left && (p->getBulletPos_X(i)+20) <= right && p->getBulletPos_Y(i) <= bottom && p->getBulletPos_Y(i) >= top){
                if(activeEnemies[j]->getType()==0)//increments the score accoridng to the level.
                    currentScore += (level<=3)? 10: ((level<=6)? 10*2: 10*3);
                else if(activeEnemies[j]->getType()==1)
                    currentScore += (level<=3)? 20: ((level<=6)? 20*2: 20*3);
                else if(activeEnemies[j]->getType()==2)
                    currentScore += (level<=3)? 30: ((level<=6)? 30*2: 30*3);
                if(!p->isFireEquipped())
                    p->unfire(i);
                scoreChanged = true;
                removeEnemy(j);
            }
        }
    }   //==================================================== ^^^bullets.

    for(int i=0;i<activeEnemyCount;i++){
        for(int j=0;j<activeEnemies[i]->getbombSize();j++){
            if(activeEnemies[i]->getBombPos_Y(j) > 850) //bombs disappear at (x,850)
                activeEnemies[i]->unfire(j);
            else{
                activeEnemies[i]->moveBomb(j);
                window.draw(activeEnemies[i]->getSpriteBomb(j));
            }
            if(p->getCenter_x()-p->getTextureRadius()-5 < (activeEnemies[i]->getBombPos_X(j) + 15) && //player bomb collision
            p->getCenter_x()+p->getTextureRadius() > activeEnemies[i]->getBombPos_X(j) &&
            p->getCenter_y()-p->getTextureRadius() < (activeEnemies[i]->getBombPos_Y(j) + 20) &&
            p->getCenter_y()+p->getTextureRadius() > activeEnemies[i]->getBombPos_Y(j)){
                if(playerHitCoolDown > p->getHitCoolDown()){
                    p->setPlayerPos(500,750);
                    p->setLives(p->getLives()-1);
                    playerHitCoolDown=0;
                    Oof.play();
                }
            }
        }
    }
    for(int i=0;i<activeEnemyCount;i++){
        activeEnemies[i]->fire(timers[i]);
        window.draw(activeEnemies[i]->getSprite());

        //checks if the player collided with one of the enemies.
        if (p->getCenter_x()-p->getTextureRadius() < (activeEnemies[i]->getSprite().getGlobalBounds().left + activeEnemies[i]->getSprite().getGlobalBounds().width) &&
            p->getCenter_x()+p->getTextureRadius() > activeEnemies[i]->getSprite().getGlobalBounds().left &&
            p->getCenter_y()-p->getTextureRadius() < (activeEnemies[i]->getSprite().getGlobalBounds().top + activeEnemies[i]->getSprite().getGlobalBounds().height) &&
            p->getCenter_y()+p->getTextureRadius() > activeEnemies[i]->getSprite().getGlobalBounds().top){
                if(playerHitCoolDown > p->getHitCoolDown()){
                    p->setPlayerPos(500,750);
                    p->setLives(p->getLives()-1);
                    playerHitCoolDown=0;
                    Oof.play();
                }
        }
    }
    if(playerHitCoolDown <= p->getHitCoolDown()){
        p->getProtectionSprite().setPosition(p->getSprite().getPosition().x-20,p->getSprite().getPosition().y-20);    //sets position of protection bubble according to player's spaceship.
        window.draw(p->getProtectionSprite());
    }

	window.draw(p->getSprite());   // setting player on screen
    window.draw(background_over);
    window.draw(badgeSprite);

    for(int i=0;i<p->getLives();i++){   //lives icon show up on the pannel
        window.draw(p->getLiveSprite(i));
    }
    if(scoreChanged){
        scoreChanged = false;
        std:: stringstream SS;
        std:: string currentScoreString;
        SS << currentScore;
        currentScoreString = SS.str();
        currentScoreObject.setString("Current Score: "+currentScoreString);
    }
    window.draw(currentScoreObject);

//    if(Keyboard::isKeyPressed(Keyboard::Space))
  //      break;
	window.display();  //Displying all the sprites

   // std::cout<<window.mapPixelToCoords(Mouse::getPosition(window)).x<<" "<<window.mapPixelToCoords(Mouse::getPosition(window)).y<<std::endl;    
    }
    }

    updateScores(currentScore,playerName);
    std:: string highScore = findHighScore();
    std:: stringstream SS;
    std:: string currentScoreString;

    lvlScreen.setTexture(endScreen);
    SS << currentScore;
    currentScoreString = SS.str();

    currentScoreObject.setPosition(510,355);
    currentScoreObject.setString(currentScoreString);
    currentScoreObject.setCharacterSize(70);

    highScoreObject.setPosition(510,520);
    highScoreObject.setString(highScore);
    highScoreObject.setCharacterSize(70);

    while(window.isOpen()){
        Event e;
        while (window.pollEvent(e))
        {  
        if (e.type == Event::Closed) // If cross/close is clicked/pressed
            window.close(); //close the game                        	    
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Enter))
            break;

        window.clear(Color::Black);
        window.draw(lvlScreen);
        window.draw(currentScoreObject);    //shows current score of the player.
        window.draw(highScoreObject);
        window.display();

    }
    currentScoreObject.setCharacterSize(50);    //resets the scoring text location and size
    currentScoreObject.setPosition(15,880);  

    return 5;
}
//----------------------------------------------------------------------------------------
//======================================================================================== main game

//============================================== Enemy Hitter
void Game::removeEnemy(int j){
   // Enemy* temp = activeEnemies[j];
    activeEnemies[j] = activeEnemies[activeEnemyCount-1];
   // activeEnemies[activeEnemyCount-1] = temp;
    activeEnemyCount--;
}

//============================================== Enemy Hitter


//============================================== level formation functions
void Game::resetFormation(){
    for(int i=0;i<totalEnemies;i++){
        enemy[i]->setPos(1200,1200);
    }
}
void Game::setFormationRectangle(){   //empty Rectangle Formation

    activeEnemyCount = 16;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(150,50);
    activeEnemies[1]->setPos(250,50);
    activeEnemies[2]->setPos(350,50);
    activeEnemies[3]->setPos(450,50);
    activeEnemies[4]->setPos(550,50);
    activeEnemies[5]->setPos(650,50);
    activeEnemies[6]->setPos(750,50);
    activeEnemies[7]->setPos(150,160);
    activeEnemies[8]->setPos(750,160);
    activeEnemies[9]->setPos(150,270);
    activeEnemies[10]->setPos(750,270);
    activeEnemies[11]->setPos(250,270);
    activeEnemies[12]->setPos(650,270);
    activeEnemies[13]->setPos(350,270);
    activeEnemies[14]->setPos(450,270);
    activeEnemies[15]->setPos(550,270);

    //side distance from eachother is kept at 100 px while vertical distance is 110 px
}

void Game::setFormationTriangle(){    //empty Triangle Formation

    activeEnemyCount = 12;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(140,50);
    activeEnemies[1]->setPos(250,50);
    activeEnemies[2]->setPos(360,50);
    activeEnemies[3]->setPos(470,50);
    activeEnemies[4]->setPos(580,50);
    activeEnemies[5]->setPos(690,50);
    activeEnemies[6]->setPos(800,50);

    activeEnemies[7]->setPos(250,160);
    activeEnemies[8]->setPos(690,160);

    activeEnemies[9]->setPos(360,270);
    activeEnemies[10]->setPos(580,270);
    activeEnemies[11]->setPos(470,380);
    
    //side distance from eachother is kept at 110 px while vertical distance is 110 px
}
void Game::setFormationCross(){       //1st level, cross

    activeEnemyCount = 13;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(140,50);
    activeEnemies[1]->setPos(800,50);
    activeEnemies[2]->setPos(250,110);
    activeEnemies[3]->setPos(690,110);
    activeEnemies[4]->setPos(360,170);
    activeEnemies[5]->setPos(580,170);
    activeEnemies[6]->setPos(470,230);
    activeEnemies[7]->setPos(360,290);
    activeEnemies[8]->setPos(580,290);
    activeEnemies[9]->setPos(250,350);
    activeEnemies[10]->setPos(690,350);
    activeEnemies[11]->setPos(140,410);
    activeEnemies[12]->setPos(800,410);
    
}
void Game::setFormationCircle(){
    activeEnemyCount = 10;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(300,50);
    activeEnemies[1]->setPos(450,20);
    activeEnemies[2]->setPos(600,50);

    activeEnemies[3]->setPos(200,160);
    activeEnemies[4]->setPos(700,160);

    activeEnemies[5]->setPos(200,270);
    activeEnemies[6]->setPos(700,270);

    activeEnemies[7]->setPos(300,380);
    activeEnemies[8]->setPos(450,410);
    activeEnemies[9]->setPos(600,380);
}
void Game::setFormationDiamond(){

    activeEnemyCount = 11;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(300,30);
    activeEnemies[1]->setPos(415,30);
    activeEnemies[2]->setPos(530,30);
    activeEnemies[3]->setPos(645,30);

    activeEnemies[4]->setPos(150,120);
    activeEnemies[5]->setPos(770,120);

    activeEnemies[6]->setPos(250,210);
    activeEnemies[7]->setPos(690,210);

    activeEnemies[8]->setPos(360,300);
    activeEnemies[9]->setPos(580,300);
    activeEnemies[10]->setPos(470,390); 
}

void Game::setFormationHeart(){
    activeEnemyCount = 12;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(270,20);
    activeEnemies[1]->setPos(390,40);
    activeEnemies[2]->setPos(555,40);
    activeEnemies[3]->setPos(665,20);
    activeEnemies[4]->setPos(480,130);

    activeEnemies[5]->setPos(170,130);
    activeEnemies[6]->setPos(750,130);

    activeEnemies[7]->setPos(250,220);
    activeEnemies[8]->setPos(690,220);

    activeEnemies[9]->setPos(360,310);
    activeEnemies[10]->setPos(580,310);
    activeEnemies[11]->setPos(470,400); 
}
void Game::setFormationTriangleFill(){
    activeEnemyCount = 16;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(140,50);
    activeEnemies[1]->setPos(250,50);
    activeEnemies[2]->setPos(360,50);
    activeEnemies[3]->setPos(470,50);
    activeEnemies[4]->setPos(580,50);
    activeEnemies[5]->setPos(690,50);
    activeEnemies[6]->setPos(800,50);

    activeEnemies[7]->setPos(250,160);
    activeEnemies[8]->setPos(690,160);

    activeEnemies[9]->setPos(360,270);
    activeEnemies[10]->setPos(580,270);
    activeEnemies[11]->setPos(470,380);

    activeEnemies[12]->setPos(360,160);
    activeEnemies[13]->setPos(470,160);
    activeEnemies[14]->setPos(580,160);

    activeEnemies[15]->setPos(470,270);

}
void Game::setFormationCircleFill(){
    activeEnemyCount = 16;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(300,50);
    activeEnemies[1]->setPos(450,20);
    activeEnemies[2]->setPos(600,50);

    activeEnemies[3]->setPos(200,160);
    activeEnemies[4]->setPos(700,160);

    activeEnemies[5]->setPos(200,270);
    activeEnemies[6]->setPos(700,270);

    activeEnemies[7]->setPos(300,380);
    activeEnemies[8]->setPos(450,410);
    activeEnemies[9]->setPos(600,380);

    activeEnemies[10]->setPos(320,160);
    activeEnemies[11]->setPos(450,140);
    activeEnemies[12]->setPos(580,160);

    activeEnemies[13]->setPos(320,270);
    activeEnemies[14]->setPos(450,290);
    activeEnemies[15]->setPos(580,270);
}
void Game::setFormationRectangleFill(){   //empty Rectangle Formation

    activeEnemyCount = 21;
    int alphaC = 0, betaC = 0, gammaC = 0;
    int random;
    for(int i=0;i<activeEnemyCount;i++){
        random = rand()%3;
        if(random==0){
            activeEnemies[i] = enemy[alphaC];
            alphaC++;
        }
        else if(random==1){
            activeEnemies[i] = enemy[totalAlpha+betaC];
            betaC++;
        }
        else{
            activeEnemies[i] = enemy[totalAlpha+totalBeta+gammaC];
            gammaC++;
        }
    }

    activeEnemies[0]->setPos(150,50);
    activeEnemies[1]->setPos(250,50);
    activeEnemies[2]->setPos(350,50);
    activeEnemies[3]->setPos(450,50);
    activeEnemies[4]->setPos(550,50);
    activeEnemies[5]->setPos(650,50);
    activeEnemies[6]->setPos(750,50);
    activeEnemies[7]->setPos(150,160);
    activeEnemies[8]->setPos(750,160);
    activeEnemies[9]->setPos(150,270);
    activeEnemies[10]->setPos(750,270);
    activeEnemies[11]->setPos(250,270);
    activeEnemies[12]->setPos(650,270);
    activeEnemies[13]->setPos(350,270);
    activeEnemies[14]->setPos(450,270);
    activeEnemies[15]->setPos(550,270);

    activeEnemies[16]->setPos(250,160);
    activeEnemies[17]->setPos(350,160);
    activeEnemies[18]->setPos(450,160);
    activeEnemies[19]->setPos(550,160);
    activeEnemies[20]->setPos(650,160);
}
//============================================== level formation functions

//============================================== File Handling
void Game::updateScores(int currentScore, std::string name) {
    std::fstream myFile, tempFile;
    myFile.open("highscores.txt", std::ios::in);
    tempFile.open("temp.txt", std::ios::out);

    std:: string fullLine;
    int times = 3;
    bool scoreUpdated = false;  // Flag to track if the score has been updated

    while (std::getline(myFile, fullLine) && times>0) {
        std:: string storedName;
        std:: string storedNum;
        int i = 0;

        for (; fullLine[i] != '%'; i++) {
            storedName += fullLine[i];
        }
        i++;

        for (; fullLine[i] != '%'; i++) {
            storedNum  += fullLine[i];
        }

       // std::cout<<storedNum<<std::endl;
        std::stringstream S;
        S << storedNum;
        int storedNumInt;
        S >> storedNumInt;
        
        if(currentScore > storedNumInt && !scoreUpdated){            // Write the new score and name to the temporary file
            tempFile <<name<<"%"<<currentScore<<"%\n";
            times--;
            if(times!=0)
                tempFile << storedName<<"%"<<storedNum<<"%\n";
            times--;
            scoreUpdated = true;
        }
        else{
            tempFile << storedName<<"%"<<storedNum<<"%\n";
            times--;
        }

    }

    myFile.close();
    tempFile.close();

    std::remove("highscores.txt");  //removes the previous file
    std::rename("temp.txt", "highscores.txt");  //changes the temp file to the new highscores
}
std::string Game::findHighScore() {
    std::fstream myFile;
    myFile.open("highscores.txt", std::ios::in);
    std:: string fullLine;
    std:: string storedName;
    std:: string storedNum;
    std::getline(myFile, fullLine);
    int i=0;    
    for (; fullLine[i] != '%'; i++)
        storedName += fullLine[i];
    i++;
    for (; fullLine[i] != '%'; i++)
        storedNum  += fullLine[i];
    myFile.close();
    return storedNum;
}
//============================================== File Handling

//============================================== startMenu
void Game::startMenu(){
    short int choice = -1;

    choice = m.display_menu();
    while(choice!=-1){
        if(choice==0)
            choice = start_game();
        else if(choice==5)
            choice = m.display_menu();
        else if(choice==1)
            choice = m.display_ins();
        else if(choice==2)
            choice = m.display_hs(font);
        else if(choice==3)
            return;
    }
}
//============================================== startMenu
void Game::adjustDifficulty(int i){
    if(i <= 3){
        for(int i=0;i<activeEnemyCount;i++){
            if(activeEnemies[i]->getType() == 0)
                activeEnemies[i]->setDelay(5);
            else if(activeEnemies[i]->getType() == 1)
                activeEnemies[i]->setDelay(3);
            else if(activeEnemies[i]->getType() == 2)
                activeEnemies[i]->setDelay(2);
        }
    }
    else if(i <= 6){
        for(int i=0;i<activeEnemyCount;i++){
            if(activeEnemies[i]->getType() == 0)
                activeEnemies[i]->setDelay(4.5);
            else if(activeEnemies[i]->getType() == 1)
                activeEnemies[i]->setDelay(2.8);
            else if(activeEnemies[i]->getType() == 2)
                activeEnemies[i]->setDelay(1.9);
        }
    }
    else if(i <= 9){
        for(int i=0;i<activeEnemyCount;i++){
            if(activeEnemies[i]->getType() == 0)
                activeEnemies[i]->setDelay(4);
            else if(activeEnemies[i]->getType() == 1)
                activeEnemies[i]->setDelay(2.6);
            else if(activeEnemies[i]->getType() == 2)
                activeEnemies[i]->setDelay(1.7);
        }
    }

}
//--------------------------------------------------------------------------MONSTER SPAWN CODE
int Game::monsterSpawn(RenderWindow& window){
    currentScoreObject.setCharacterSize(50);
    currentScoreObject.setPosition(15,880); 

    Clock clockk;
    float timer = 0;
    float shootTimer1 = 0, shootTimer = 0, shootingAnimationTimer = 0, playerHitCoolDown = 1.5;
    bool shooting = false;
    std::string rotation;

    while(window.isOpen() && timer<20){

        float time = clockk.getElapsedTime().asSeconds(); 
        clockk.restart();
        timer += time;
        shootingAnimationTimer+=time;
        playerHitCoolDown +=time;
        shootTimer1 += time;
        shootTimer += time;

     	Event e;
        while (window.pollEvent(e))
        {  
        if (e.type == Event::Closed) // If cross/close is clicked/pressed
            window.close(); //close the game                        	    
        }

        if(Keyboard::isKeyPressed(Keyboard::P)){    //pauses the game
            if(m.display_pause(window, font)==0)
                return 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
        if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                p->move("u");    //playet will move upwards
        if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards


        //====================================wraps around the screen
        if(p->getCenter_x()+p->getTextureRadius()<0)
            p->wrap("left");
        else if(p->getCenter_x()-p->getTextureRadius()>1000)
            p->wrap("right");
        if(p->getCenter_y()+p->getTextureRadius()<0)
            p->wrap("up");
        else if(p->getCenter_y()-p->getTextureRadius()>855)
            p->wrap("down");

        //====================================Rotates spaceship when moving diagonally
        if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Up))
            rotation = "L";
        else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Up))
            rotation = "R";
        else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Down))
            rotation = "RB";
        else if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Down))
            rotation = "LB";
        else
            rotation = "no";

        p->rotate(rotation);    

        monsterEnemy->monsterMovement();    //moves the monster continuously



        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(p->getSprite());
        if(playerHitCoolDown <= p->getHitCoolDown()){
        p->getProtectionSprite().setPosition(p->getSprite().getPosition().x-20,p->getSprite().getPosition().y-20);    //sets position of protection bubble according to player's spaceship.
        window.draw(p->getProtectionSprite());
    }

        if(shooting){
            monsterEnemy->fire(shootingAnimationTimer);
            window.draw(monsterEnemy->getSpriteBomb());
            if((p->getCenter_x()-p->getTextureRadius() < (monsterEnemy->getX() + 180) && //player lightning collision
                p->getCenter_x()+p->getTextureRadius() > monsterEnemy->getX()+100 &&
                p->getCenter_y()-p->getTextureRadius() < (monsterEnemy->getY() + 800) &&
                p->getCenter_y()+p->getTextureRadius() > monsterEnemy->getY()+200) || 
                (p->getCenter_x()-p->getTextureRadius() < (monsterEnemy->getX() + 200) && //player monster collision
                p->getCenter_x()+p->getTextureRadius() > monsterEnemy->getX()+30 &&
                p->getCenter_y()-p->getTextureRadius() < (monsterEnemy->getY() + 400) &&
                p->getCenter_y()+p->getTextureRadius() > monsterEnemy->getY()+30)){

                    if(playerHitCoolDown > p->getHitCoolDown()){
                        p->setPlayerPos(500,750);
                        p->setLives(p->getLives()-1);
                        playerHitCoolDown=0;
                        Oof.play();
                    }
                }
        }
        if(p->getLives()==0)
            break;
        if(shootTimer>5 && shooting){
            shooting = false;
            shootTimer1 = 0;
        }
        if(!shooting && shootTimer1>2){
            shootTimer = 0;
            shooting = true;
        }
        window.draw(monsterEnemy->getSprite());
        window.draw(background_over);

        //player stuff, like health points, badge, and score
        window.draw(badgeSprite);

        for(int i=0;i<p->getLives();i++){   //lives icon show up on the pannel
            window.draw(p->getLiveSprite(i));
        }

        window.draw(currentScoreObject);

        window.display();
    }
    return 0;
}


//--------------------------------------------------------------------------DRAGON SPAWN CODE
int Game::dragonSpawn(RenderWindow& window){
    currentScoreObject.setCharacterSize(50);
    currentScoreObject.setPosition(15,880); 

    Clock clockk;
    float timer = 0;
    float shootTimer = 0, shootTimer1 = 0, shootingAnimationTimer = 0, playerHitCoolDown = 1.5;
    bool shooting = false;
    std::string rotation;

    while(window.isOpen() && timer<20){

        float time = clockk.getElapsedTime().asSeconds(); 
        clockk.restart();
        timer += time;
        shootingAnimationTimer+=time;
        playerHitCoolDown +=time;
        shootTimer1 += time;
        shootTimer += time;

     	Event e;
        while (window.pollEvent(e))
        {  
        if (e.type == Event::Closed) // If cross/close is clicked/pressed
            window.close(); //close the game                        	    
        }

        if(Keyboard::isKeyPressed(Keyboard::P)){    //pauses the game
            if(m.display_pause(window, font)==0)
                return 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
        if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                p->move("u");    //playet will move upwards
        if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards


        //====================================wraps around the screen
        if(p->getCenter_x()+p->getTextureRadius()<0)
            p->wrap("left");
        else if(p->getCenter_x()-p->getTextureRadius()>1000)
            p->wrap("right");
        if(p->getCenter_y()+p->getTextureRadius()<0)
            p->wrap("up");
        else if(p->getCenter_y()-p->getTextureRadius()>855)
            p->wrap("down");

        //====================================Rotates spaceship when moving diagonally
        if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Up))
            rotation = "L";
        else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Up))
            rotation = "R";
        else if (Keyboard::isKeyPressed(Keyboard::Right)&&Keyboard::isKeyPressed(Keyboard::Down))
            rotation = "RB";
        else if (Keyboard::isKeyPressed(Keyboard::Left)&&Keyboard::isKeyPressed(Keyboard::Down))
            rotation = "LB";
        else
            rotation = "no";

        p->rotate(rotation);    

        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(p->getSprite());

        if(playerHitCoolDown <= p->getHitCoolDown()){
        p->getProtectionSprite().setPosition(p->getSprite().getPosition().x-20,p->getSprite().getPosition().y-20);    //sets position of protection bubble according to player's spaceship.
        window.draw(p->getProtectionSprite());
    }

        if(p->getLives()==0)
            break;

        window.draw(dragonEnemy->getSprite());
        int b;
        if(p->getCenter_x()<333)
            b=1;
        else if(p->getCenter_x()<666)
            b=0;
        else if(p->getCenter_x()<1000)
            b=2;
        dragonEnemy->fire(shootTimer,b);

        float playerLeft= p->getCenter_x()-p->getTextureRadius();
        float playerRight=playerLeft + 2*p->getTextureRadius();
        float playerTop= p->getCenter_y() - p->getTextureRadius();
        float playerBottom = playerTop + 2*p->getTextureRadius();
        if((playerLeft < (dragonEnemy->getX() + 300) && playerRight > dragonEnemy->getX()-20 && playerTop < (dragonEnemy->getY() + 400) && playerBottom > dragonEnemy->getY()-10))
        {
            p->setPlayerPos(500,750);   //death
            p->setLives(p->getLives()-1);
            playerHitCoolDown=0; 
            Oof.play();
        }
        
        for(int i=0;i<dragonEnemy->getbombSize();i++){
            if(dragonEnemy->getBombPos_Y(i)>750)
                dragonEnemy->unfire(i);
            else if((playerLeft < (dragonEnemy->getBombPos_X(i) + 120) && playerRight > dragonEnemy->getBombPos_X(i)+20 && playerTop < (dragonEnemy->getBombPos_Y(i) + 120) && playerBottom > dragonEnemy->getBombPos_Y(i)+10))
            {
                p->setPlayerPos(500,750);   //death
                p->setLives(p->getLives()-1);
                playerHitCoolDown=0;   
                dragonEnemy->unfire(i);
            }
            else
                window.draw(dragonEnemy->getSpriteBomb(i));
        }

        window.draw(background_over);

        //player stuff, like health points, badge, and score
        window.draw(badgeSprite);

        for(int i=0;i<p->getLives();i++){   //lives icon show up on the pannel
            window.draw(p->getLiveSprite(i));
        }

        window.draw(currentScoreObject);

        window.display();
    }
    return 0;
}
