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

    // Window
    window.create(sf::VideoMode::getDesktopMode(), "Towers of Hanoi");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    // Pointers to game state run functions
    runState[PRE_GAME] = &towerOfHanoi::preGame;
    runState[IN_GAME] = &towerOfHanoi::inGame;
    runState[POST_GAME] = &towerOfHanoi::postGame;

    // Pointers to game state event functions
    processEvent[PRE_GAME] = &towerOfHanoi::preGameEvent;
    processEvent[IN_GAME] = &towerOfHanoi::inGameEvent;
    processEvent[POST_GAME] = &towerOfHanoi::postGameEvent;

    // Disk
    diskSprite = nullptr;
    for(int i = 0; i < 4; i++)
        diskTexture[i].loadFromFile("resources/disk/disk" + std::to_string(i+1) + ".png");

    // Background
    backgroundTexture.loadFromFile("resources/background/background.png");
    backgroundSprite.setTexture(backgroundTexture);

    // Foreground
    foregroundTexture.loadFromFile("resources/foreground/foreground.png");
    foregroundSprite.setTexture(foregroundTexture);
    foregroundSprite.setPosition(0, window.getSize().y - 350);

    // Mist
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

    // Sound
    sfxMoveBuffer.loadFromFile("resources/sound/sfxMove.wav");
    sfxMove.setBuffer(sfxMoveBuffer);
    for(int i = 0; i < 2; i++)
    {
        sfxTickBuffer[i].loadFromFile("resources/sound/sfxTick" + std::to_string(i+1) + ".wav");
        sfxTick[i].setBuffer(sfxTickBuffer[i]);
        sfxTick[i].setVolume(25);
    }

    // Title
    font.loadFromFile("resources/font/hanoi.ttf");
    title.setFont(font);
    title.setCharacterSize(190);
    title.setString("Tower of Hanoi");
    title.setColor(sf::Color::White);
    title.setPosition(window.getSize().x/2 - title.getGlobalBounds().width/2, window.getSize().y/10);

    // Prompt for enter
    askEnter.setFont(font);
    askEnter.setCharacterSize(40);
    askEnter.setString("Press ENTER to start");
    askEnter.setColor(sf::Color::White);
    askEnter.setPosition(window.getSize().x/2 - askEnter.getGlobalBounds().width/2, window.getSize().y/1.2);

    // Prompt for input text
    for(int i = 0; i < 2; i++)
    {
        askInput[i].setFont(font);
        askInput[i].setCharacterSize(50);
        askInput[i].setColor(sf::Color::White);
        askInput[i].setPosition(window.getSize().x/2 - title.getGlobalBounds().width/4.9, window.getSize().y/2.5 + (i * 100));
    }
    askInput[0].setString("Number of disks:");
    askInput[1].setString("Number of rods:");

    // Prompt for confirmation
    askConfirm.setFont(font);
    askConfirm.setCharacterSize(70);
    askConfirm.setColor(sf::Color::White);
    askConfirm.setString("Please confirm: y / n");
    askConfirm.setPosition(window.getSize().x/2 - askConfirm.getGlobalBounds().width/2, window.getSize().y/1.25);

    // Default input strings (number of disks, starting rod, ending rod)
    inputStr[0] = "3";
    inputStr[1] = "3";

    // Input text (number of disks, starting rod, ending rod)
    for(int i = 0; i < 2; i++)
    {
        inputText[i].setFont(font);
        inputText[i].setCharacterSize(50);
        inputText[i].setString(inputStr[i]);
        inputText[i].setColor(sf::Color::White);
        inputText[i].setPosition(window.getSize().x/2 + 200, window.getSize().y/2.5 + (i * 100));
    }

    // Move count
    userMoveCount.setFont(font);
    userMoveCount.setCharacterSize(100);
    userMoveCount.setString("0");
    userMoveCount.setColor(sf::Color::White);
    userMoveCount.setPosition(30, 1);

    // Ending message
    for(int i = 0; i < 3; i++)
    {
        endMsg[i].setFont(font);
        endMsg[i].setCharacterSize(70);
        endMsg[i].setColor(sf::Color::White);
    }
    endMsg[0].setString("Congratulations!");

    // Focus box
    focusBox.setFillColor(sf::Color(255, 255, 255, 50));

    // Focus box arrows
    arrowTexture.loadFromFile("resources/menu/arrow.png");
    for(int i = 0; i < 2; i++)
    {
        arrowSprite[i].setTexture(arrowTexture);
        arrowSprite[i].setColor(focusBox.getFillColor());
        arrowSprite[i].setScale(1, 0.93);
    }
    arrowSprite[0].setPosition(inputText[0].getPosition().x - 57.2, inputText[0].getPosition().y + 1);
    arrowSprite[1].setScale(-1, 0.93);

    // Dim screen
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
        // Handle keyboard events
        sf::Event event;
        while(window.pollEvent(event))
            (this->*processEvent[state])(event);

        // Render window
        window.clear();
        (this->*runState[state])();
        window.display();
    }
}

void towerOfHanoi::createRods()
{
    // Create rods
    rod = new std::stack<int>[numRods];

    // Create array to indicate auxiliary rods
    if(numRods - 3)
    {
        auxRod = new int[numRods - 3];
        for(int i = 0; i < numRods - 3; i++)
            auxRod[i] = i+1;
    }

    // Fill starting rod with disks
    for(int i = 0; i < numDisks; i++)
        rod[startRod].push(i+1);
}

void towerOfHanoi::solve()
{
    // Traditional case
    if(numRods == 3)
    {
        startRodToEndRod();
    }

    // Same number case
    else if(numRods == numDisks)
    {
        sameNumStartRodToEndRod();
    }

    // Trivial case
    else if(numRods > numDisks)
    {
        trivialStartRodToEndRod();
    }

    // Generic case
    else
    {
        startRodToAuxRod();
        std::cout.flush();
        startRodToEndRod();
        auxRodToEndRod();
    }

    // Reset rods for user input
    while(!rod[endRod].empty())
        rod[endRod].pop();
    for(int i = 0; i < numDisks; i++)
        rod[startRod].push(i+1);

}

void towerOfHanoi::startRodToAuxRod()
{
    // Lay out disks across remaining empty rods
    for(int i = 0; i < numRods - 3; i++)
    {
        // The number of disks laid out decrement with each iteration from (NUM_RODS - 1) downward
        for(int j = 0; j < numRods - auxRod[i]; j++)
        {
            // No need to create anymore auxiliary rods
            if(rod[endRod].empty() && !rod[i].empty() && rod[startRod].size() < rod[i].size())
                return;

            // Search for an empty rod starting from the end rod downwards
            for(int searching = true, k = endRod; searching; k--)
            {
                // Pop the top of the start rod onto an empty rod
                if(rod[k].empty())
                {
                    placeDisk(startRod, k);
                    searching = false;
                }
            }
        }

        // Place disks back onto auxiliary rod
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

    // Loop through the rods from left to right until the puzzle is solved
    for(int currRod = 0; rod[endRod].size() != originalStartSize; currRod == numRods - 1 ? currRod = 0 : currRod++)
    {
        // Cannot perform actions
        if(isInvalidRod(currRod, prevDisk) || isAuxiliaryRod(currRod))
            continue;

        // Even number disk -> attempt move left
        if((rod[currRod].top()%2))
        {
            nextRod = !currRod ? numRods - 1 : currRod - 1;
            while(isAuxiliaryRod(nextRod))
                nextRod--;
        }

        // Odd numbered disk -> attempt move right
        else
        {
            nextRod = (currRod+1)%numRods;
            while(isAuxiliaryRod(nextRod))
                nextRod++;
        }

        // Next rod is empty OR is disk to move is a greater disk number
        if(rod[nextRod].empty() || rod[currRod].size() && rod[currRod].top() > rod[nextRod].top())
        {
            // Identify the disk as the prev, and move it.
            prevDisk = rod[currRod].top();
            placeDisk(currRod, nextRod);
        }
    }
}

void towerOfHanoi::auxRodToEndRod()
{
    // Lay out disks across remaining empty rods
    for(int i = numRods - 3; i > 0; i--)
    {
        int originalAuxSize = rod[auxRod[i-1]].size();

        // Lay out disks across remaining empty rods
        while(rod[auxRod[i-1]].size() > 1)
        {
            // Search for empty rod
            for(int searching = true, j = 0; j < numRods && searching; j++)
            {
                // Place disk on empty rod
                if(rod[j].empty())
                {
                    placeDisk(auxRod[i-1], j);
                    searching = false;
                }
            }
        }

        // Place disks back onto end rod
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
    // Lay disks across empty rods until the start rod has 2 disks
    for(int i = 1; rod[startRod].size() != 2; i++)
    {
        placeDisk(startRod, i + numRods - numDisks);
    }

    // Temporarily stack two disks to make room for the start rod's top disk
    placeDisk(startRod+1, endRod-1);
    placeDisk(startRod, startRod+1);

    // Place disks onto the end rod
    for(int i = 0; rod[endRod].size() != numDisks; i = i == endRod ? 0 : i+1)
    {
        // Current rod has a disk and is one unit greater than the end rod's top disk OR the end rod is empty
        if(rod[i].size() && ((rod[endRod].size() && rod[i].top() == rod[endRod].top() + 1) || rod[endRod].empty()))
            placeDisk(i, endRod);

        // Displace the temporary stacked tower made earlier
        else if(rod[i].size() == 2 && rod[0].empty())
            placeDisk(i, 0);
    }
}

void towerOfHanoi::trivialStartRodToEndRod()
{
    // Lay out disks across the empty rods with the last disk being on the end rod
    for(int i = 0; !rod[startRod].empty(); i++)
    {
        placeDisk(startRod, i + numRods - numDisks);
    }

    // Place disks back onto end rod
    for(int i = endRod - 1; !rod[i].empty(); i--)
    {
        placeDisk(i, endRod);

    }
}

bool towerOfHanoi::isInvalidRod(int rodNum, int prevDisk)
{
    // Current rod is empty OR on the previous disk moved
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
    // Place disk from top of beginning rod to end rod
    int disk = rod[beginRod].top();
    rod[beginRod].pop();
    rod[endRod].push(disk);

    // If solving, record instruction into solveData
    if(solving)
        solveData.push(std::pair<int, int>(disk, endRod));
}

void towerOfHanoi::preGame()
{
    // Mist animation
    animateMist();

    // Draw background, foreground, and mist
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    // Dim screen
    setDim(true);
    window.draw(dimRect, sf::BlendMultiply);

    // Set focus box position
    if(focus < 2)
    {
        // Set position relative to focus
        focusBox.setPosition(inputText[0].getPosition().x/1.597 + askInput[0].getGlobalBounds().width/0.84,
                             askInput[0].getGlobalBounds().top - askInput[0].getGlobalBounds().height/2.5 + (focus * 100));

        // Set size relative to width of input text being focused
        focusBox.setSize(sf::Vector2f(47 + inputText[focus].getGlobalBounds().width, 70));

        // Set position of arrows relative to focus
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

    // Draw focus box and arrows
    window.draw(focusBox);
    for(int i = 0; i < 2 && focus < 2; i++)
        window.draw(arrowSprite[i]);

    // Draw title
    window.draw(title);

    // Draw input text
    for(int i = 0; i < 2; i++)
    {
        window.draw(askInput[i]);
        window.draw(inputText[i]);
    }

    // Draw confirmation if necessary
    if(needConfirmation)
        window.draw(askConfirm);

    // Draw prompt enter message
    else
    {
        window.draw(askEnter);
    }
}

void towerOfHanoi::inGame()
{
    // Check for win condition
    if(rod[endRod].size() == numDisks && !moveInProgress)
    {
        setEndMessage();
        state = POST_GAME;
    }

    // Disk animation
    if(moveInProgress)
        moveDisk();

    // Mist animation
    animateMist();

    // Draw background and background mist
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);

    // Draw disks
   for(int i = 0; i < numDisks; i++)
       window.draw(diskSprite[i]);

    // Draw foreground and foreground mist
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    // Turn off dim
    setDim(false);
    if(dimRect.getFillColor() != sf::Color(255, 255, 255, 0))
        window.draw(dimRect, sf::BlendMultiply);

    // Draw move count
    window.draw(userMoveCount);
}

void towerOfHanoi::postGame()
{
    // Mist animation
    animateMist();

    // Draw background and background mist
    window.draw(backgroundSprite);
    window.draw(mistSprite[0]);

    // Draw disks
   for(int i = 0; i < numDisks; i++)
       window.draw(diskSprite[i]);

    // Draw foreground and foreground mist
    window.draw(foregroundSprite);
    window.draw(mistSprite[1]);

    // Dim screen
    setDim(true);
    window.draw(dimRect, sf::BlendMultiply);

    // Draw end message
    for(int i = 0; i < 3; i++)
        window.draw(endMsg[i]);

    // Prompt for enter
    window.draw(askEnter);
}

void towerOfHanoi::preGameEvent(sf::Event event)
{
    // Keyboard
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            // Quit
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            // Increment focus
            case sf::Keyboard::Tab:
            case sf::Keyboard::Down:
                if(focus != 2)
                {
                    focus = !focus;
                    if(sfxTick[1].getPlayingOffset() < sf::milliseconds(5))
                        sfxTick[1].play();
                }
                break;

            // Decrement focus
            case sf::Keyboard::Up:
                if(focus != 2)
                {
                    focus = !focus;
                    if(sfxTick[1].getPlayingOffset() < sf::milliseconds(5))
                        sfxTick[1].play();
                }
                break;

            // Decrement focused value
            case sf::Keyboard::Left:

                // Set to confirm large value
                if(focus == 2)
                    doLargeValue = true;
                else
                    decrementInputStr(focus);
                if(sfxTick[0].getPlayingOffset() < sf::milliseconds(5))
                    sfxTick[0].play();
                break;

            // Increment focused value or set to confirm large value
            case sf::Keyboard::Right:

                // Set to unconfirm large value or set to unconfirm large value
                if(focus == 2)
                    doLargeValue = false;
                else
                    incrementInputStr(focus);
                if(sfxTick[0].getPlayingOffset() < sf::milliseconds(5))
                    sfxTick[0].play();
                break;

            // Set to confirm large value
            case sf::Keyboard::Y:
                if(focus == 2)
                    doLargeValue = true;
                break;

            // Set to unconfirm large value
            case sf::Keyboard::N:
                if(focus == 2)
                    doLargeValue = false;
                break;

            // Set the board and proceed to ingame
            case sf::Keyboard::Return:

                // Reset error status
                needConfirmation = false;

                // Unconfirm large value and clear number of disks
                if(focus == 2 && !doLargeValue)
                {
                    focus = 0;
                    return;
                }

                // Set the board based off of input
                numDisks = std::stoi(inputStr[0].toAnsiString());
                numRods = std::stoi(inputStr[1].toAnsiString());
                endRod = numRods-1;

                // Large processing warning
                if((numDisks >= 25 + ((numRods-3) * 5) && !doLargeValue))
                {
                    needConfirmation = true;
                    focus = 2;
                    return;
                }
                // No errors! Proceed to game
                createRods();
                solve();
                loadDiskSprites();
                state = IN_GAME;
                break;

            default:
                break;
        }
    }

    // Dim arrow graphic upon key or mouse button release
    else if(event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
    {
        arrowSprite[0].setColor(focusBox.getFillColor());
        arrowSprite[1].setColor(focusBox.getFillColor());
    }
}

void towerOfHanoi::inGameEvent(sf::Event event)
{
    // Keyboard
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            // Quit
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            // Restart
            case sf::Keyboard::R:
                clearSettings();
                std::cout.flush();
                break;

            // Trigger a move
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
    // Keyboard
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            // Quit
            case sf::Keyboard::Q:
                window.close();
                std::cout.flush();
                break;

            // Returns to title screen
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

    // Each disk is (100 - diskNum*(0.5/totalDisks)) % smaller than the next, capping at a 50 % scale of the original
    float multiplier = 0.5/(float)numDisks;
    for(int i = 0; i < numDisks; i++)
    {
        // Set the texture, iterating from 1-4 repeatedly
        diskSprite[i].setTexture(diskTexture[i%4]);

        // Set the origin as the middle of the first disk's dimensions
        diskSprite[i].setOrigin(300, 88);

        // Make the disks smaller in size for each disk made
        diskSprite[i].setScale(1 - (i * multiplier), 1 - (i * multiplier));
        diskSprite[i].setScale(diskSprite[i].getScale().x * (3/((float)numRods)), diskSprite[i].getScale().y);

        // Set the position of the disk onto the start rod
        diskSprite[i].setPosition(posX(startRod), posY(startRod));
    }
}

void towerOfHanoi::animateMist()
{
    for(int i = 0; i < 2; i++)
    {
        // "Loop" back to beginning of image if end of image size reached
        if(mistSprite[i].getPosition().x == -3840)
            mistSprite[i].setPosition(0, mistSprite[i].getPosition().y);
        mistSprite[i].move(mistSpeed[i], 0);

        // Get alpha of current mist sprite
        int alpha = mistSprite[i].getColor().a;

        // Decrement alpha if above maximum alpha
        if(alpha > mistMaxAlpha)
            alpha--;

        // Increment alpha if below minimum alpha
        else if(alpha < mistMinAlpha)
            alpha++;

        // Set alpha
        mistSprite[i].setColor(sf::Color(255, 255, 255, alpha));
    }
}

void towerOfHanoi::setDim(bool on)
{
    // Increase dim intensity
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

    // Decrease dim intensity
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
    // Set end message strings
    endMsg[1].setString("You did " + userMoveCount.getString() + " moves.");

    // Set prompt enter string
    askEnter.setString("Press ENTER to restart");
    askEnter.setPosition(window.getSize().x/2 - askEnter.getGlobalBounds().width/2, window.getSize().y/1.2);

    // Set position
    for(int i = 0; i < 3; i++)
        endMsg[i].setPosition(window.getSize().x/2 - endMsg[i].getGlobalBounds().width/2, window.getSize().y/4 + (i * 100));

}

void towerOfHanoi::moveDisk()
{
    // Pick up
    if(moveClock.getElapsedTime() < sf::milliseconds(30))
    {
        // Move disk upwards
        diskSprite[instruction.first-1].move(0, -5);
    }

    // Done
    else if(moveClock.getElapsedTime() >= moveTime)
    {
        // Set disk to designated end position
        diskSprite[instruction.first-1].setPosition(posX(instruction.second), posY(instruction.second));

        // Move finished
        moveInProgress = false;

        // Increment user move count
        incrementMoveCount();
        return;
    }

    // Put down
    else if(moveClock.getElapsedTime() > sf::milliseconds(30))
    {
        // Move disk downwards
        diskSprite[instruction.first-1].move(0, 5);
    }
}

void towerOfHanoi::getNextInstruction()
{
    if(!solveData.empty() && !moveInProgress)
    {
        // Obtain next instruction in moveData
        instruction = solveData.front();
        solveData.pop();

        // Apply instruction to game stack
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
    // Default position (no disks)
    int yPosition = 950;

    // Find the heights of all disks in the rod and add to y position
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
