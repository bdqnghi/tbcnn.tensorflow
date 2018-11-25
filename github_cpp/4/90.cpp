#include "towerofhanoi.h"

towerOfHanoi::towerOfHanoi()
{
    numDisks = 0;
    numRods = 0;
    startRod = 0;
    endRod = 0;
    rod = nullptr;
    auxRod = nullptr;
    state = PRE_GAME;
    focus = 0;
    moveInProgress = needConfirmation = doLargeValue = false;
    moveTime = sf::milliseconds(100);

    
    window.create(sf::VideoMode::getDesktopMode(), "Towers of Hanoi");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    
    runState[PRE_GAME] = &towerOfHanoi::preGame;
    runState[IN_GAME] = &towerOfHanoi::inGame;
    runState[POST_GAME] = &towerOfHanoi::postGame;

    
    processEvent[PRE_GAME] = &towerOfHanoi::preGameEvent;
    processEvent[IN_GAME] = &towerOfHanoi::inGameEvent;
    processEvent[POST_GAME] = &towerOfHanoi::postGameEvent;

    
    diskSprite = nullptr;
    for(int i = 0; i < 4; i++)
        diskTexture[i].loadFromFile("resources/disk/disk" + std::to_string(i+1) + ".png");

    
    backgroundTexture.loadFromFile("resources/background/background.png");
    backgroundSprite.setTexture(backgroundTexture);

    
    foregroundTexture.loadFromFile("resources/foreground/foreground.png");
    foregroundSprite.setTexture(foregroundTexture);
    foregroundSprite.setPosition(0, window.getSize().y - 350);

    
    for(int i = 0; i < 2; i++)
    {
        mistTexture[i].loadFromFile("resources/mist/mist" + std::to_string(i+1) + ".png");
        mistSprite[i].setTexture(mistTexture[i]);
    }
    mistMaxAlpha = 150;
    mistMinAlpha = 60;
    mistSpeed[0] = -2;
    mistSpeed[1] = -5;
    mistSprite[0].setPosition(0, 80);
    mistSprite[0].setColor(sf::Color(255, 255, 255, mistMaxAlpha));
    mistSprite[1].setPosition(0, 400);
    mistSprite[1].setColor(sf::Color(255, 255, 255, mistMinAlpha));

    
    sfxMoveBuffer.loadFromFile("resources/sound/sfxMove.wav");
    sfxMove.setBuffer(sfxMoveBuffer);
    for(int i = 0; i < 2; i++)
    {
        sfxTickBuffer[i].loadFromFile("resources/sound/sfxTick" + std::to_string(i+1) + ".wav");
        sfxTick[i].setBuffer(sfxTickBuffer[i]);
        sfxTick[i].setVolume(25);
    }

    
    font.loadFromFile("resources/font/hanoi.ttf");
    title.setFont(font);
    title.setCharacterSize(190);
    title.setString("Tower of Hanoi");
    title.setColor(sf::Color::White);
    title.setPosition(window.getSize().x/2 - title.getGlobalBounds().width/2, window.getSize().y/10);

    
    askEnter.setFont(font);
    askEnter.setCharacterSize(40);
    askEnter.setString("Press ENTER to start");
    askEnter.setColor(sf::Color::White);
    askEnter.setPosition(window.getSize().x/2 - askEnter.getGlobalBounds().width/2, window.getSize().y/1.2);

    
    for(int i = 0; i < 2; i++)
    {
        askInput[i].setFont(font);
        askInput[i].setCharacterSize(50);
        askInput[i].setColor(sf::Color::White);
        askInput[i].setPosition(window.getSize().x/2 - title.getGlobalBounds().width/4.9, window.getSize().y/2.5 + (i * 100));
    }
    askInput[0].setString("Number of disks:");
    askInput[1].setString("Number of rods:");

    
    askConfirm.setFont(font);
    askConfirm.setCharacterSize(70);
    askConfirm.setColor(sf::Color::White);
    askConfirm.setString("Please confirm: y / n");
    askConfirm.setPosition(window.getSize().x/2 - askConfirm.getGlobalBounds().width/2, window.getSize().y/1.25);

    
    inputStr[0] = "3";
    inputStr[1] = "3";

    
    for(int i = 0; i < 2; i++)
    {
        inputText[i].setFont(font);
        inputText[i].setCharacterSize(50);
        inputText[i].setString(inputStr[i]);
        inputText[i].setColor(sf::Color::White);
        inputText[i].setPosition(window.getSize().x/2 + 200, window.getSize().y/2.5 + (i * 100));
    }

    
    userMoveCount.setFont(font);
    userMoveCount.setCharacterSize(100);
    userMoveCount.setString("0");
    userMoveCount.setColor(sf::Color::White);
    userMoveCount.setPosition(30, 1);

    
    for(int i = 0; i < 3; i++)
    {
        endMsg[i].setFont(font);
        endMsg[i].setCharacterSize(70);
        endMsg[i].setColor(sf::Color::White);
    }
    endMsg[0].setString("Congratulations!");

    
    focusBox.setFillColor(sf::Color(255, 255, 255, 50));

    
    arrowTexture.loadFromFile("resources/menu/arrow.png");
    for(int i = 0; i < 2; i++)
    {
        arrowSprite[i].setTexture(arrowTexture);
        arrowSprite[i].setColor(focusBox.getFillColor());
        arrowSprite[i].setScale(1, 0.93);
    }
    arrowSprite[0].setPosition(inputText[0].getPosition().x - 57.2, inputText[0].getPosition().y + 1);
    arrowSprite[1].setScale(-1, 0.93);

    
    dimRGB[0] = 137;
    dimRGB[1] = 147;
    dimRGB[2] = 163;
    defaultDimColor = sf::Color(dimRGB[0], dimRGB[1], dimRGB[2], 0);
    dimRect.setFillColor(defaultDimColor);
    dimRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
}

towerOfHanoi::~towerOfHanoi()
{
    if(rod)
        delete[] rod;
    if(auxRod)
        delete[] auxRod;
    if(diskSprite)
        delete[] diskSprite;

    rod = nullptr;
    auxRod = nullptr;
    diskSprite = nullptr;
    numDisks = numRods = startRod = endRod = focus = NULL;
    moveInProgress = needConfirmation = doLargeValue = NULL;
}

void towerOfHanoi::run()
{
    while(window.isOpen())
    {
        
        sf::Event event;
        while(window.pollEvent(event))
            (this->*processEvent[state])(event);

        
        window.clear();
        (this->*runState[state])();
        window.display();
    }
}

void towerOfHanoi::createRods()
{
    
    rod = new std::stack<int>[numRods];

    
    if(numRods - 3)
    {
        auxRod = new int[numRods - 3];
        for(int i = 0; i < numRods - 3; i++)
            auxRod[i] = i+1;
    }

    
    for(int i = 0; i < numDisks; i++)
        rod[startRod].push(i+1);
}

void towerOfHanoi::solve()
{
    
    if(numRods == 3)
    {
        startRodToEndRod();
    }

    
    else if(numRods == numDisks)
    {
        sameNumStartRodToEndRod();
    }

    
    else if(numRods > numDisks)
    {
        trivialStartRodToEndRod();
    }

    
    else
    {
        startRodToAuxRod();
        std::cout.flush();
        startRodToEndRod();
        auxRodToEndRod();
    }

    
    while(!rod[endRod].empty())
        rod[endRod].pop();
    for(int i = 0; i < numDisks; i++)
        rod[startRod].push(i+1);

}

void towerOfHanoi::startRodToAuxRod()
{
    
    for(int i = 0; i < numRods - 3; i++)
    {
        
        for(int j = 0; j < numRods - auxRod[i]; j++)
        {
            
            if(rod[endRod].empty() && !rod[i].empty() && rod[startRod].size() < rod[i].size())
                return;

            
            for(int searching = true, k = endRod; searching; k--)
            {
                
                if(rod[k].empty())
                {
                    placeDisk(startRod, k);
                    searching = false;
                }
            }
        }

        
        for(int j = startRod; j < numRods; j++)
        {
            if(!rod[j].empty() && !rod[i].empty() && rod[j].top() == rod[auxRod[i]].top() + 1)
            {
                placeDisk(j, auxRod[i]);
            }
        }
    }
}

void towerOfHanoi::startRodToEndRod()
{
    int prevDisk, nextRod, originalStartSize = rod[startRod].size();

    
    for(int currRod = 0; rod[endRod].size() != originalStartSize; currRod == numRods - 1 ? currRod = 0 : currRod++)
    {
        
        if(isInvalidRod(currRod, prevDisk) || isAuxiliaryRod(currRod))
            continue;

        
        if((rod[currRod].top()%2))
        {
            nextRod = !currRod ? numRods - 1 : currRod - 1;
            while(isAuxiliaryRod(nextRod))
                nextRod--;
        }

        
        else
        {
            nextRod = (currRod+1)%numRods;
            while(isAuxiliaryRod(nextRod))
                nextRod++;
        }

        
        if(rod[nextRod].empty() || rod[currRod].size() && rod[currRod].top() > rod[nextRod].top())
        {
            
            prevDisk = rod[currRod].top();
            placeDisk(currRod, nextRod);
        }
    }
}

void towerOfHanoi::auxRodToEndRod()
{
    
    for(int i = numRods - 3; i > 0; i--)
    {
        int originalAuxSize = rod[auxRod[i-1]].size();

        
        while(rod[auxRod[i-1]].size() > 1)
        {
            
            for(int searching = true, j = 0; j < numRods && searching; j++)
            {
                
                if(rod[j].empty())
                {
                    placeDisk(auxRod[i-1], j);
                    searching = false;
                }
            }
        }

        
        for(int placed = 0, i = 0; placed < originalAuxSize; i = i == endRod ? 0 : i+1)
        {
            if(rod[i].size() == 1 && rod[i].top() == rod[endRod].top()+1)
            {
                placeDisk(i, endRod);
                placed++;
            }
        }
    }
}

void towerOfHanoi::sameNumStartRodToEndRod()
{
    
    for(int i = 1; rod[startRod].size() != 2; i++)
    {
        placeDisk(startRod, i + numRods - numDisks);
    }

    
    placeDisk(startRod+1, endRod-1);
    placeDisk(startRod, startRod+1);

    
    for(int i = 0; rod[endRod].size() != numDisks; i = i == endRod ? 0 : i+1)
    {
        
        if(rod[i].size() && ((rod[endRod].size() && rod[i].top() == rod[endRod].top() + 1) || rod[endRod].empty()))
            placeDisk(i, endRod);

        
        else if(rod[i].size() == 2 && rod[0].empty())
            placeDisk(i, 0);
    }
}

void towerOfHanoi::trivialStartRodToEndRod()
{
    
    for(int i = 0; !rod[startRod].empty(); i++)
    {
        placeDisk(startRod, i + numRods - numDisks);
    }

    
    for(int i = endRod - 1; !rod[i].empty(); i--)
    {
        placeDisk(i, endRod);

    }
}

bool towerOfHanoi::isInvalidRod(int rodNum, int prevDisk)
{
    
    if(rod[rodNum].empty() || (!rod[rodNum].empty() && rod[rodNum].top() == prevDisk))
        return true;
    return false;
}

bool towerOfHanoi::isAuxiliaryRod(int rodNum)
{
    for(int i = 0; (i < numRods - 3) && auxRod; i++)
        if(rodNum == auxRod[i])
            return true;
    return false;
}

void towerOfHanoi::placeDisk(int beginRod, int endRod, bool solving)
{
    
    int disk = rod[beginRod].top();
    rod[beginRod].pop();
    rod[endRod].push(disk);

    
    if(solving)
        solveData.push(std::pair<int, int>(disk, endRod));
}

void towerOfHanoi::preGame()
{
    
    animateMist();

    
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    
    setDim(true);
    window.draw(dimRect, sf::BlendMultiply);

    
    if(focus < 2)
    {
        
        focusBox.setPosition(inputText[0].getPosition().x/1.597 + askInput[0].getGlobalBounds().width/0.84,
                             askInput[0].getGlobalBounds().top - askInput[0].getGlobalBounds().height/2.5 + (focus * 100));

        
        focusBox.setSize(sf::Vector2f(47 + inputText[focus].getGlobalBounds().width, 70));

        
        arrowSprite[0].setPosition(arrowSprite[0].getPosition().x,
                                   inputText[focus].getPosition().y + 1 );

        arrowSprite[1].setPosition(inputText[0].getPosition().x + inputText[focus].getGlobalBounds().width + 55.8,
                                   inputText[focus].getPosition().y + 1);
    }
    else
    {
        focusBox.setSize(sf::Vector2f(60, 70));
        focusBox.setPosition(askConfirm.getGlobalBounds().width/0.57 + (!doLargeValue * 110.5),
                             askConfirm.getGlobalBounds().top - askConfirm.getGlobalBounds().height/5.5);
    }

    
    window.draw(focusBox);
    for(int i = 0; i < 2 && focus < 2; i++)
        window.draw(arrowSprite[i]);

    
    window.draw(title);

    
    for(int i = 0; i < 2; i++)
    {
        window.draw(askInput[i]);
        window.draw(inputText[i]);
    }

    
    if(needConfirmation)
        window.draw(askConfirm);

    
    else
    {
        window.draw(askEnter);
    }
}

void towerOfHanoi::inGame()
{
    
    if(rod[endRod].size() == numDisks && !moveInProgress)
    {
        setEndMessage();
        state = POST_GAME;
    }

    
    if(moveInProgress)
        moveDisk();

    
    animateMist();

    
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);

    
   for(int i = 0; i < numDisks; i++)
       window.draw(diskSprite[i]);

    
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    
    setDim(false);
    if(dimRect.getFillColor() != sf::Color(255, 255, 255, 0))
        window.draw(dimRect, sf::BlendMultiply);

    
    window.draw(userMoveCount);
}

void towerOfHanoi::postGame()
{
    
    animateMist();

    
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);

    
   for(int i = 0; i < numDisks; i++)
       window.draw(diskSprite[i]);

    
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    
    setDim(true);
    window.draw(dimRect, sf::BlendMultiply);

    
    for(int i = 0; i < 3; i++)
        window.draw(endMsg[i]);

    
    window.draw(askEnter);
}

void towerOfHanoi::preGameEvent(sf::Event event)
{
    
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            
            case sf::Keyboard::Tab:
            case sf::Keyboard::Down:
                if(focus != 2)
                {
                    focus = !focus;
                    if(sfxTick[1].getPlayingOffset() < sf::milliseconds(5))
                        sfxTick[1].play();
                }
                break;

            
            case sf::Keyboard::Up:
                if(focus != 2)
                {
                    focus = !focus;
                    if(sfxTick[1].getPlayingOffset() < sf::milliseconds(5))
                        sfxTick[1].play();
                }
                break;

            
            case sf::Keyboard::Left:

                
                if(focus == 2)
                    doLargeValue = true;
                else
                    decrementInputStr(focus);
                if(sfxTick[0].getPlayingOffset() < sf::milliseconds(5))
                    sfxTick[0].play();
                break;

            
            case sf::Keyboard::Right:

                
                if(focus == 2)
                    doLargeValue = false;
                else
                    incrementInputStr(focus);
                if(sfxTick[0].getPlayingOffset() < sf::milliseconds(5))
                    sfxTick[0].play();
                break;

            
            case sf::Keyboard::Y:
                if(focus == 2)
                    doLargeValue = true;
                break;

            
            case sf::Keyboard::N:
                if(focus == 2)
                    doLargeValue = false;
                break;

            
            case sf::Keyboard::Return:

                
                needConfirmation = false;

                
                if(focus == 2 && !doLargeValue)
                {
                    focus = 0;
                    return;
                }

                
                numDisks = std::stoi(inputStr[0].toAnsiString());
                numRods = std::stoi(inputStr[1].toAnsiString());
                endRod = numRods-1;

                
                if((numDisks >= 25 + ((numRods-3) * 5) && !doLargeValue))
                {
                    needConfirmation = true;
                    focus = 2;
                    return;
                }
                
                createRods();
                solve();
                loadDiskSprites();
                state = IN_GAME;
                break;

            default:
                break;
        }
    }

    
    else if(event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
    {
        arrowSprite[0].setColor(focusBox.getFillColor());
        arrowSprite[1].setColor(focusBox.getFillColor());
    }
}

void towerOfHanoi::inGameEvent(sf::Event event)
{
    
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            
            case sf::Keyboard::R:
                clearSettings();
                std::cout.flush();
                break;

            
            case sf::Keyboard::Space:
                if(!moveInProgress && rod[endRod].size() != numDisks)
                {
                    if(sfxMove.getPlayingOffset() < sf::milliseconds(5))
                        sfxMove.play();
                    getNextInstruction();
                    moveInProgress = true;
                    moveClock.restart();
                }
                break;

            default:
                break;
        }
    }
}

void towerOfHanoi::postGameEvent(sf::Event event)
{
    
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            
            case sf::Keyboard::Return:
                clearSettings();
                break;
            default:
                break;
        }
    }
}

void towerOfHanoi::loadDiskSprites()
{
    diskSprite = new sf::Sprite[numDisks];

    
    float multiplier = 0.5/(float)numDisks;
    for(int i = 0; i < numDisks; i++)
    {
        
        diskSprite[i].setTexture(diskTexture[i%4]);

        
        diskSprite[i].setOrigin(300, 88);

        
        diskSprite[i].setScale(1 - (i * multiplier), 1 - (i * multiplier));
        diskSprite[i].setScale(diskSprite[i].getScale().x * (3/((float)numRods)), diskSprite[i].getScale().y);

        
        diskSprite[i].setPosition(posX(startRod), posY(startRod));
    }
}

void towerOfHanoi::animateMist()
{
    for(int i = 0; i < 2; i++)
    {
        
        if(mistSprite[i].getPosition().x == -3840)
            mistSprite[i].setPosition(0, mistSprite[i].getPosition().y);
        mistSprite[i].move(mistSpeed[i], 0);

        
        int alpha = mistSprite[i].getColor().a;

        
        if(alpha > mistMaxAlpha)
            alpha--;

        
        else if(alpha < mistMinAlpha)
            alpha++;

        
        mistSprite[i].setColor(sf::Color(255, 255, 255, alpha));
    }
}

void towerOfHanoi::setDim(bool on)
{
    
    if(on)
    {
        if(dimRGB[0] > defaultDimColor.r)
            dimRGB[0]--;
        if(dimRGB[1] > defaultDimColor.g)
            dimRGB[1]--;
        if(dimRGB[2] > defaultDimColor.b)
            dimRGB[2]--;
        dimRect.setFillColor(sf::Color(dimRGB[0], dimRGB[1], dimRGB[2], 0));
    }

    
    else
    {
        if(dimRGB[0] < 255)
            dimRGB[0]++;
        if(dimRGB[1] < 255)
            dimRGB[1]++;
        if(dimRGB[2] < 255)
            dimRGB[2]++;
        dimRect.setFillColor(sf::Color(dimRGB[0], dimRGB[1], dimRGB[2], 0));
    }
}

void towerOfHanoi::incrementInputStr(int focus)
{
    if(inputStr[focus].getSize())
    {
        int num = stoi(inputStr[focus].toAnsiString());
        if(num < 100)
        {
            num++;
            inputStr[focus] = std::to_string(num);
            inputText[focus].setString(inputStr[focus]);
            arrowSprite[1].setColor(sf::Color(255, 255, 255, 200));
        }
    }
}

void towerOfHanoi::decrementInputStr(int focus)
{
    if(inputStr[focus].getSize())
    {
        int num = stoi(inputStr[focus].toAnsiString());
        if(num > 3)
        {
            num--;
            inputStr[focus] = std::to_string(num);
            inputText[focus].setString(inputStr[focus]);
            arrowSprite[0].setColor(sf::Color(255, 255, 255, 200));
        }
    }
}

void towerOfHanoi::setEndMessage()
{
    
    endMsg[1].setString("You did " + userMoveCount.getString() + " moves.");

    
    askEnter.setString("Press ENTER to restart");
    askEnter.setPosition(window.getSize().x/2 - askEnter.getGlobalBounds().width/2, window.getSize().y/1.2);

    
    for(int i = 0; i < 3; i++)
        endMsg[i].setPosition(window.getSize().x/2 - endMsg[i].getGlobalBounds().width/2, window.getSize().y/4 + (i * 100));

}

void towerOfHanoi::moveDisk()
{
    
    if(moveClock.getElapsedTime() < sf::milliseconds(30))
    {
        
        diskSprite[instruction.first-1].move(0, -5);
    }

    
    else if(moveClock.getElapsedTime() >= moveTime)
    {
        
        diskSprite[instruction.first-1].setPosition(posX(instruction.second), posY(instruction.second));

        
        moveInProgress = false;

        
        incrementMoveCount();
        return;
    }

    
    else if(moveClock.getElapsedTime() > sf::milliseconds(30))
    {
        
        diskSprite[instruction.first-1].move(0, 5);
    }
}

void towerOfHanoi::getNextInstruction()
{
    if(!solveData.empty() && !moveInProgress)
    {
        
        instruction = solveData.front();
        solveData.pop();

        
        for(int beginRod = 0; beginRod < numRods; beginRod++)
        {
            if(rod[beginRod].size() && rod[beginRod].top() == instruction.first)
                placeDisk(beginRod, instruction.second);
        }
    }
}

int towerOfHanoi::posX(int rodNum)
{
    float xPos = diskSprite[0].getGlobalBounds().width/2. + rodNum * (diskSprite[0].getGlobalBounds().width + (3/(numRods * 0.05)) - pow(0.5, numRods));
    float xPosFarthest = ((numRods-1) * (diskSprite[0].getGlobalBounds().width + (3/(numRods * 0.05)) - pow(0.5, numRods)));
    xPosFarthest += diskSprite[0].getGlobalBounds().width;
    float xDif = (window.getSize().x - xPosFarthest)/2.;
    xPos += xDif;
    return xPos;
}

int towerOfHanoi::posY(int rodNum)
{
    
    int yPosition = 950;

    
    std::stack<int> temp = rod[rodNum];
    for(int i = 0; i < rod[rodNum].size(); i++)
    {
        int disk = temp.top();
        temp.pop();
        yPosition -= diskSprite[disk-1].getGlobalBounds().height/2.25;

    }
    return yPosition;
}

void towerOfHanoi::clearSettings()
{
    if(auxRod)
        delete[] auxRod;
    if(rod)
        delete[] rod;
    if(diskSprite)
        delete[] diskSprite;
    while(!solveData.empty())
        solveData.pop();
    focus = 0;
    doLargeValue = false;
    userMoveCount.setString("0");
    state = PRE_GAME;
}
