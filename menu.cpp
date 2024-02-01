#include "menu.h"


Menu::Menu()
{
bg_texture.loadFromFile("img/menuBG.jpg");
Texplay.loadFromFile("img/MainMenuPlay.png");
TexplayS.loadFromFile("img/MainMenuPlaySel.png");
Texinstructions.loadFromFile("img/MainMenuInstructions.png");
TexinstructionsS.loadFromFile("img/MainMenuInstructionsSel.png");
Texhighscores.loadFromFile("img/MainMenuHighScores.png");
TexhighscoresS.loadFromFile("img/MainMenuHighScoresSel.png");
Texexit.loadFromFile("img/MainMenuExit.png");
TexexitS.loadFromFile("img/MainMenuExitSel.png");

TexResume.loadFromFile("img/MainMenuResume.png");
TexResumeS.loadFromFile("img/MainMenuResumeSel.png");
ResumeB.setTexture(TexResume);

InstrucTexture.loadFromFile("img/MenuInstr.png");
InstrucSprite.setTexture(InstrucTexture);
HsTexture.loadFromFile("img/MenuHigh.png");
HsSprite.setTexture(HsTexture);

PlayB.setTexture(Texplay);
InstructionsB.setTexture(Texinstructions);
HighscoresB.setTexture(Texhighscores);
ExitB.setTexture(Texexit);

background.setTexture(bg_texture);
PlayB.setPosition(0,0);
// InstructionsB.setPosition(0,200);
// HighscoresB.setPosition(0,400);
// ExitB.setPosition(0,600);



//constructors body
}

int Menu::display_menu()

{
    RenderWindow window(VideoMode(1000, 950), "SpaceShooter Main Menu");
    Clock clock;
    float timer=0;
    bool keyPressed =  false;
    PlayB.setTexture(TexplayS);
    short int choice=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; 

        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }


        if(Keyboard::isKeyPressed(Keyboard::Up) && !keyPressed)
        {
            if(choice == 3){
                ExitB.setTexture(Texexit);
                HighscoresB.setTexture(TexhighscoresS);
                choice--;
            }
            else if(choice==2){
                HighscoresB.setTexture(Texhighscores);
                InstructionsB.setTexture(TexinstructionsS);
                choice--;
            }
            else if(choice==1){
                InstructionsB.setTexture(Texinstructions);
                PlayB.setTexture(TexplayS);
                choice--;
            }
            keyPressed = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Down) && !keyPressed){
            if(choice==0){
                PlayB.setTexture(Texplay);
                InstructionsB.setTexture(TexinstructionsS);
                choice++;
            }
            else if(choice==1){
                InstructionsB.setTexture(Texinstructions);
                HighscoresB.setTexture(TexhighscoresS);
                choice++;
            }
            else if(choice==2){
                HighscoresB.setTexture(Texhighscores);
                ExitB.setTexture(TexexitS);
                choice++;
            }
            keyPressed = true;
        }

        timer = 0;
        while(keyPressed && timer<25000){
            timer+=0.001;
        }
        keyPressed = false;




        if(Keyboard::isKeyPressed(Keyboard::Enter)){
            InstructionsB.setTexture(Texinstructions);
            HighscoresB.setTexture(Texhighscores);
            ExitB.setTexture(Texexit);
            PlayB.setTexture(TexplayS); //all of this resets the selected glow button before exiting the main menu

            return choice;
        }

    
	    window.clear(Color::Black); //clears the screen
	    window.draw(background);  // setting background
        window.draw(PlayB);
        window.draw(InstructionsB);
        window.draw(HighscoresB);
        window.draw(ExitB);
        window.display();
    }
    
    return -1;
}

int Menu::display_ins(){

    RenderWindow window(VideoMode(1000, 950), "Instructions");
    Clock clock;
    float timer=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; 

        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }

        if(Keyboard::isKeyPressed(Keyboard::Enter))
            break;

	    window.clear(Color::Black); //clears the screen
	    window.draw(background);  // setting background
        window.draw(InstrucSprite);
        window.display();
    }

    return 5;
}
int Menu::display_hs(Font& font){
    Text first, second, third;
    first.setFont(font);
    second.setFont(font);
    third.setFont(font);
    first.setCharacterSize(50);
    first.setFillColor(sf::Color::White);
    first.setPosition(430, 300);
    second.setCharacterSize(50);
    second.setFillColor(sf::Color::White);
    second.setPosition(430, 500);
    third.setCharacterSize(50);
    third.setFillColor(sf::Color::White);
    third.setPosition(430, 700);

    std::fstream myFile, tempFile;
    myFile.open("highscores.txt", std::ios::in);

    std:: string fullLine;

    int times = 3;

    while (std::getline(myFile, fullLine) && times>0) {
       // std::cout<<"FullLine is: "<<fullLine<<std::endl;
        int i = 0;

        std::string storedName;
        std::string storedNum;

        for (; fullLine[i] != '%'; i++) {
            storedName += fullLine[i];
        }
        i++;

        for (; fullLine[i] != '%'; i++) {
            storedNum += fullLine[i];
        }

        if(times==3){
            first.setString(storedName + "-| " + storedNum);
            times--;
        }
        else if(times==2){
            second.setString(storedName + "-| " + storedNum);
            times--;
        }
        else if(times==1){
            third.setString(storedName + "-| " + storedNum);
            times--;
        }
        
    }
    myFile.close(); //closes the file

    RenderWindow window(VideoMode(1000, 950), "High Scores");
    Clock clock;
    float timer=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; 

        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }

        if(Keyboard::isKeyPressed(Keyboard::Enter))
            break;

	    window.clear(Color::Black); //clears the screen
	    window.draw(background);  // setting background
        window.draw(HsSprite);
        window.draw(first);
        window.draw(second);
        window.draw(third);
        window.display();
    }

    return 5;
}

int Menu::display_pause(RenderWindow &window, Font &font){
    Text first, second, third;
    first.setFont(font);
    second.setFont(font);
    third.setFont(font);
    first.setCharacterSize(50);
    first.setFillColor(sf::Color::White);
    first.setPosition(430, 300);
    second.setCharacterSize(50);
    second.setFillColor(sf::Color::White);
    second.setPosition(430, 500);
    third.setCharacterSize(50);
    third.setFillColor(sf::Color::White);
    third.setPosition(430, 700);

    std::fstream myFile;
    myFile.open("highscores.txt", std::ios::in);
    std:: string fullLine;
    int times = 3;
    while (std::getline(myFile, fullLine) && times>0) {
        int i = 0;
        std::string storedName;
        std::string storedNum;
        for (; fullLine[i] != '%'; i++) 
            storedName += fullLine[i];
        i++;

        for (; fullLine[i] != '%'; i++)
            storedNum += fullLine[i];

        if(times==3){
            first.setString(storedName + "-| " + storedNum);
            times--;
        }
        else if(times==2){
            second.setString(storedName + "-| " + storedNum);
            times--;
        }
        else if(times==1){
            third.setString(storedName + "-| " + storedNum);
            times--;
        }
    }
    myFile.close(); //closes the file 
    //================================ copy pasta-ed highscore from the main menu

    Clock clockk;
    float timer=0;
    float timer2=0;
    bool keyPressed =  false;
    ResumeB.setTexture(TexResumeS);
    short int choice=0;

    bool instructionOpened = false;
    bool highscoreOpened = false;
    while (window.isOpen())
    {
        float time = clockk.getElapsedTime().asSeconds(); 
        clockk.restart();
        timer += time; 
        timer2 += time;

        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
        //std::cout<<timer2<<std::endl;
        if(instructionOpened){
            window.clear(Color::Black);
            window.draw(background);
            window.draw(InstrucSprite);
            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Enter) && timer2>0.5){
                instructionOpened = false;
                timer2=0;
            }
        }
        else if(highscoreOpened){
            window.clear(Color::Black);
            window.draw(background);
            window.draw(HsSprite);
            window.draw(first);
            window.draw(second);
            window.draw(third);
            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Enter) && timer2>0.5){
                highscoreOpened = false;
                timer2 = 0;
            }   
        }
        else{
            if(Keyboard::isKeyPressed(Keyboard::Enter) && timer2>0.5){

                if(choice == 0)
                    break;
                else if(choice == 1){
                    instructionOpened = true;
                }
                else if(choice == 2){
                    highscoreOpened = true;
                }
                else if(choice == 3){
                    InstructionsB.setTexture(Texinstructions);
                    HighscoresB.setTexture(Texhighscores);
                    ExitB.setTexture(Texexit);
                    PlayB.setTexture(TexplayS); //all of this resets the selected glow button before exiting the main menu

                    // PlayB.setScale(1,1);
                    // ResumeB.setScale(1,1);
                    // InstructionsB.setScale(1,1);
                    // HighscoresB.setScale(1,1);
                    // ExitB.setScale(1,1);
                    // background.setScale(1,1);
                    return 0;
                }
                timer2 = 0;
                continue;
            }

            if(Keyboard::isKeyPressed(Keyboard::Up) && !keyPressed)
            {
                if(choice == 3){
                    ExitB.setTexture(Texexit);
                    HighscoresB.setTexture(TexhighscoresS);
                    choice--;
                }
                else if(choice==2){
                    HighscoresB.setTexture(Texhighscores);
                    InstructionsB.setTexture(TexinstructionsS);
                    choice--;
                }
                else if(choice==1){
                    InstructionsB.setTexture(Texinstructions);
                    ResumeB.setTexture(TexResumeS);
                    choice--;
                }
                keyPressed = true;
            }

            if(Keyboard::isKeyPressed(Keyboard::Down) && !keyPressed){
                if(choice==0){
                    ResumeB.setTexture(TexResume);
                    InstructionsB.setTexture(TexinstructionsS);
                    choice++;
                }
                else if(choice==1){
                    InstructionsB.setTexture(Texinstructions);
                    HighscoresB.setTexture(TexhighscoresS);
                    choice++;
                }
                else if(choice==2){
                    HighscoresB.setTexture(Texhighscores);
                    ExitB.setTexture(TexexitS);
                    choice++;
                }
                keyPressed = true;
            }

            timer = 0;
            while(keyPressed && timer<30000){
                timer+=0.001;
            }
            keyPressed = false;




        
            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background
            window.draw(ResumeB);
            window.draw(InstructionsB);
            window.draw(HighscoresB);
            window.draw(ExitB);
            window.display();
        }
    }
    window.clear(Color::Black);
    return -1;
}
std::string Menu::GetName(RenderWindow& window, Font &font) {
    Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setPosition(300, 400);
    text.setString("Name: ");

    std::string name;
    Texture tex;
    Sprite bg;
    tex.loadFromFile("img/menu/nameScreen.png");
    bg.setTexture(tex);

    bool isNameEntered = false;

    while (window.isOpen() && !isNameEntered) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            } else if (e.type == Event::TextEntered) {
                if (e.text.unicode == '\r') // Check if Enter key is pressed
                    isNameEntered = true;
                else if (e.text.unicode == '\b' && !name.empty()) {  // Check if Backspace key is pressed and name is not empty
                    name.pop_back();
                    text.setString("Name: " +name);
                }
                else if (e.text.unicode >= 32 && e.text.unicode <= 126 && name.length() < 10) {   //takes only 10 characters
                    name += static_cast<char>(e.text.unicode); 
                    text.setString("Name: "+name);
                }
            }
        }

        window.clear(Color::Black);
        window.draw(bg);
        window.draw(text);  // Draw the text displaying the name
        window.display();
    }

    return name;
}


std::string Menu::getBadge(std::string playerName,Font &font){

    std::fstream myFile;
    myFile.open("highscores.txt", std::ios::in);
    std:: string fullLine;
    int times = 3;

    while (std::getline(myFile, fullLine) && times>0) {
        int i = 0;
        std::string storedName;
        for (; fullLine[i] != '%'; i++) 
            storedName += fullLine[i];

        if(times==3){
            if(storedName==playerName)
                return "first";
            times--;
        }
        else if(times==2){
            if(storedName==playerName)
                return "second";
            times--;
        }
        else if(times==1){
            if(storedName==playerName)
                return "third";
            times--;
        }
    }
    myFile.close(); //closes the file 
    return "noBadge";
}