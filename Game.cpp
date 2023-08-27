#include "Game.hpp"

using namespace std;

Game::Game() {};

void Game::loadGame(){
    ifstream inputFile;
    inputFile.open("saveFile.txt");
    if (!inputFile) {
        loadMessageTimer = 100;
    } else {
        string line;
        getline(inputFile, line);
        player.setMoney(stoi(line.substr(line.find('=') + 1)));
        getline(inputFile, line);
        player.loadMaxLife(stoi(line.substr(line.find('=') + 1)));
        int i = 0;
        while (i < playerWeapons.size()) {
            getline(inputFile, line);
            size_t pos = line.find('=');
            playerWeapons[i].setIsBought(line[pos+1] - '0');
            if (line[pos+3] - '0') {
                player.setBullet(&playerWeapons[i]);
                player.getBullet()->setEquipped(true);
            };
            i++;
        }   
        currentState = GameState::Market;
        selectedItem = 0; 
    }
    inputFile.close();
};

void Game::saveGame(){
    ofstream outputFile;
    outputFile.open("saveFile.txt"); 
    outputFile << "money=" << player.getMoney() << endl;
    outputFile << "maxlife=" << player.getMaxLife() << endl;
    for (int i = 0; i < playerWeapons.size(); i++) {
        outputFile << i << "=" << playerWeapons[i].isBought() << ":" << playerWeapons[i].isEquipped() << endl;
    }
    outputFile.close();
    saveMessageTimer = 100;
};


void Game::createLevel(){};

void Game::initializeGame() {
        currLevelInt = 0;
        levelVector.push_back(new Level(currLevelInt));
        levelVector.push_back(new Level(currLevelInt + 1));
        currentLevel = levelVector[0];
         
        selectedItem = 0;
        player.setMaxLife();
        player.setX(5);
        player.setY(5);

        gameStarted = true;
}

void Game::gameOver() {
    for (Level* L : levelVector) {
            L->enemyVector.clear();
            L->enemyBulletVector.clear();
            L->playerBulletVector.clear();
            L->wallVector.clear();
            L->doorVector.clear();
        }
        levelVector.clear();

        currentState = GameState::GameOver;
        gameStarted = false;
}

void Game::stopGame() {
    running = false;
}

void Game::run() {
    initilizeScreen();
    while (running) { 
        if (!gameStarted) {
            initializeGame();
        }
        handleInput();
        update();
        render();
    }

    endwin();

}

void Game::initilizeScreen() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    // Create a 30x30 window
    refresh();
    this->win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(win, TRUE);

    this->running = true;
};


void Game::handleInput() {
    switch (currentState) {
        case GameState::MainMenu:
            switch (getch()) {
                case 'w':
                    selectedItem = (selectedItem - 1 + numMainMenuItems) % numMainMenuItems;
                    break;
                case 's':
                    selectedItem = (selectedItem + 1) % numMainMenuItems;
                    break;
                case 'l': // Enter key
                    // Handle menu item selection
                    if (selectedItem == 0) {
                        // Nuova Partita
                        currentState = GameState::Market;
                    } else if (selectedItem == 1) {
                        // Carica Partita
                        loadGame();
                    } else if (selectedItem == 2) {
                        // Esci
                        stopGame();
                    }
                    break;
            }
            
            break;

        case GameState::Market:
            switch (getch()) {
                case 'w':
                    selectedItem = (selectedItem - 1 + numMarketItems) % numMarketItems;
                    break;
                case 's':
                    selectedItem = (selectedItem + 1) % numMarketItems;
                    break;
                case 'l': // Enter key
                    // Handle menu item selection
                    if (selectedItem == 0) {
                        // Nuova partita
                        currentState = GameState::Playing;
                    } else if (selectedItem == 1) {
                        // Compra arma
                        selectedItem = 0;
                        currentState = GameState::WeaponMenu;
                    }  else if (selectedItem == 2) {
                        // Salva
                        saveGame();
                    }  else if (selectedItem == 3) {
                        // Esci
                        stopGame();

                    }
                    break;
            }
            break;

        case GameState::WeaponMenu:
            switch (getch()) {
                case 'w':
                    selectedItem = (selectedItem - 1 + playerWeapons.size() + 2) % (playerWeapons.size() + 2);
                    break;
                case 's':
                    selectedItem = (selectedItem + 1) % (playerWeapons.size() + 2);
                    break;
                case 'l': // Enter key
                    // Handle weapon buy process
                    if (selectedItem == playerWeapons.size() + 1) {
                        selectedItem = 0;
                        currentState = GameState::Market;
                    } else if (selectedItem == 0) {
                        if (player.getMoney() >= marketLifeCost) {
                            player.addMaxLife(marketLifeAmount);
                            player.removeMoney(marketLifeCost);
                        }
                    }else {
                        if (playerWeapons[selectedItem - 1].isBought()) {
                            player.setBullet(&playerWeapons[selectedItem - 1]);
                            player.getBullet()->setEquipped(true);
                        } else {
                            if (player.getMoney() >= playerWeapons[selectedItem - 1].getCost()) {
                                player.removeMoney(playerWeapons[selectedItem - 1].getCost());
                                playerWeapons[selectedItem - 1].setIsBought(true);
                            }
                        }
                    }
            
                    break;
            }

            break;
        case GameState::Playing:
            switch (getch()) {
                case 'w':
                    if (currentLevel->isFreePositionToGo(player.getX(), player.getY() - 1)) player.moveUp(); else player.setDirection(3);
                    break;

                case 's':
                    if (currentLevel->isFreePositionToGo(player.getX(), player.getY() + 1)) player.moveDown(); else player.setDirection(1);
                    break;

                case 'a':
                    if (currentLevel->isFreePositionToGo(player.getX() - 1, player.getY())) player.moveLeft(); else player.setDirection(2);
                    break;

                case 'd':
                    if (currentLevel->isFreePositionToGo(player.getX() + 1, player.getY())) player.moveRight(); else player.setDirection(0);
                    break;

                case 'l':
                    currentLevel->playerBulletVector.push_back(player.shoot());
                    break;

                case 'q':
                    gameOver();
                    break;

                // case 'Q':
                //     stopGame();
                //     break; 

                default:
                    // Handle other keys or do nothing
                    break;
            }
            break;
        case GameState::GameOver:
            switch (getch()) {
                case 'w':
                    selectedItem = (selectedItem - 1 + numGameOverItems) % numGameOverItems;
                    break;
                case 's':
                    selectedItem = (selectedItem + 1) % numGameOverItems;
                    break;
                case 'l': // Enter key
                    // Handle menu item selection
                    if (selectedItem == 0) {
                        // Nuova Partita
                        currentState = GameState::Playing;
                    } else if (selectedItem == 1) {
                        // Mercato
                        selectedItem = 0;
                        currentState = GameState::Market;
                    } else if (selectedItem == 2) {
                        // Esci
                        stopGame(); 
                    }
                    break;
            }
            break;
    }
}

void Game::update() {
    switch (currentState) {
        case GameState::MainMenu:
            break;
        case GameState::Market:
            break;
        case GameState::WeaponMenu:
            break;
        case GameState::Playing:
            currentTime = chrono::steady_clock::now();
            elapsedTime = currentTime - startTime;
            startTime = currentTime;

            // Update bullet and enemy movement based on time elapsed
            timeSinceLastBulletUpdate += elapsedTime.count();
            while (timeSinceLastBulletUpdate >= bulletSpeed) {
                for (auto it = currentLevel->playerBulletVector.begin() ; it != currentLevel->playerBulletVector.end(); ) {
                    it->move();
                    if (currentLevel->outOfBounds(*it) || it->getMaxDistance()==0) {
                        it = currentLevel->playerBulletVector.erase(it);
                    } else {
                        ++it;
                    }
                }
                for (auto it = currentLevel->enemyBulletVector.begin() ; it != currentLevel->enemyBulletVector.end(); ) {
                    it->move();
                    if (currentLevel->outOfBounds(*it) || it->getMaxDistance()==0) {
                        it = currentLevel->enemyBulletVector.erase(it);
                    } else {
                        ++it;
                    }
                }
                for (auto it = currentLevel->enemyVector.begin() ; it != currentLevel->enemyVector.end(); it++) {
                    int n = rand() % 15 + 1;
                    switch (n) {
                        case 1:
                            if (currentLevel->isFreePositionToGo(it->getX(), it->getY() - 1)) it->moveUp();
                            break;
                        case 2:
                            if (currentLevel->isFreePositionToGo(it->getX() - 1, it->getY())) it->moveLeft();
                            break;
                        case 3:
                            if (currentLevel->isFreePositionToGo(it->getX() + 1, it->getY())) it->moveRight();
                            break;
                        case 4:
                            if (currentLevel->isFreePositionToGo(it->getX(), it->getY() + 1)) it->moveDown();
                            break;
                        default:
                            break;
                    }
                    if (rand() % 10 == 0) currentLevel->enemyBulletVector.push_back(it->shoot());
                }

                timeSinceLastBulletUpdate -= bulletSpeed;
            }

            // Check collision of elements
            // Enemy bullet - Player collision
            for (auto b = currentLevel->enemyBulletVector.begin() ; b != currentLevel->enemyBulletVector.end(); ) {
                bool collided = false;
                if (currentLevel->collision(*b, player)) {
                    player.reduceLife(b->getDamage());
                    collided = true;
                }
                if (collided) {
                    b = currentLevel->enemyBulletVector.erase(b);
                } else {
                    ++b;
                }
            }
            // Enemy - Player collision
            for (auto b = currentLevel->enemyVector.begin() ; b != currentLevel->enemyVector.end(); b++) {
                if (currentLevel->collision(*b, player)) {
                    player.reduceLife(b->getBullet()->getDamage());                         
                }
            }
            // Player bullet - Enemies collision
            for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
                bool collided = false;
                for (auto enemyIt = currentLevel->enemyVector.begin() ; enemyIt != currentLevel->enemyVector.end(); ) {
                    // collision check
                    if (currentLevel->collision(*b, *enemyIt)) {
                        enemyIt->reduceLife(b->getDamage());
                        // if life to zero, delete enemy
                        if (enemyIt->getLife() <= 0) {
                            enemyIt = currentLevel->enemyVector.erase(enemyIt);
                            player.addMoney(enemyIt->getMoney());
                        } 
                        collided = true;
                        break;
                    } else {
                        ++enemyIt;
                    }
                }   
                if (collided) {
                    b = currentLevel->playerBulletVector.erase(b);
                } else {
                    ++b;
                }
            }
            // Player bullet - Wall collision
            for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
                bool collided = false;
                for (auto wallIt = currentLevel->wallVector.begin() ; wallIt != currentLevel->wallVector.end(); ) {
                    // collision check
                    if (currentLevel->collision(*b, *wallIt)) {
                        wallIt->reduceLife(b->getDamage());
                        // if life to zero, delete enemy
                        if (wallIt->getLife() <= 0) {
                            wallIt = currentLevel->wallVector.erase(wallIt);
                        } 
                        collided = true;
                        break;
                    } else {
                        ++wallIt;
                    }
                }   
                if (collided) {
                    b = currentLevel->playerBulletVector.erase(b);
                } else {
                    ++b;
                }
            }

            // Player - Money Bonus collision
            for (auto b = currentLevel->moneyVector.begin() ; b != currentLevel->moneyVector.end();) {
                bool collided = false;
                if (currentLevel->collision(*b, player)) {
                    player.addMoney(moneyBonus); collided = true;                        
                }
                if (collided) {
                    b = currentLevel->moneyVector.erase(b);
                } else {
                    ++b;
                }
            }

            // Gameover trigger
            if (player.getLife() <= 0) {
                gameOver();
            }

            // Change Level trigger
            if (currentLevel->collision(player, currentLevel->doorVector[0])) {
                
                if (currLevelInt != 0) {
                    currLevelInt--;
                    currentLevel = levelVector[currLevelInt];
                    player.setX(currentLevel->doorVector[1].getX()-1);
                    player.setY(currentLevel->doorVector[1].getY());
                }
            }

            if (currentLevel->collision(player, currentLevel->doorVector[1])) {
                currLevelInt++;
                if (currLevelInt - 1 == levelVector.size() - 2) {
                    levelVector.push_back(new Level(currLevelInt + 1));
                }
                currentLevel = levelVector[currLevelInt];
                player.setX(currentLevel->doorVector[0].getX()+1);
                player.setY(currentLevel->doorVector[0].getY());
    
            }

            break;
        case GameState::GameOver:
            break;
    }
}

void Game::render() {
    // Clear the screen and render game elements based on the current state
    clear();

    switch (currentState) {
        case GameState::MainMenu:
            
            // Print menu items
            mvprintw(1, 1, "WARRIOR GAME by Leonardo Pinna");
            for (int i = 0; i < numMainMenuItems; ++i) {
                if (i == selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                mvprintw(1 + i + 1, 1, mainMenuItems[i]);
                attroff(A_REVERSE);
            }

            break;

        case GameState::Market: 
                mvprintw(1, 1, "BENVENUTO NEL MERCATO: INIZIA UNA PARTITA O VAI AL NEGOZIO!");
                // Print menu items
                for (int i = 0; i < numMarketItems; ++i) {
                    if (i == selectedItem) {
                        attron(A_REVERSE); // Highlight the selected item
                    }
                    mvprintw(i + 2, 1, marketItems[i]);
                    attroff(A_REVERSE);
                }
            break;

        case GameState::WeaponMenu:
            // Print menu items
            mvprintw(1, 1, "COMPRA ARMI O VITA");          

            for (int i = 0; i < playerWeapons.size() + 2; ++i) {
                if (i == selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                if (i == 0) {
                    mvprintw(marketVerticalOffSet, 1, "Aumenta Vita Max");
                    mvprintw(marketVerticalOffSet, marketCostDistance, "%d", marketLifeCost);
                    mvprintw(marketVerticalOffSet, marketCostDistance + marketLifeAmountOffset, "+%d", marketLifeAmount);
                } else {
                if (!(i == playerWeapons.size() + 1)) {
                    mvprintw(i + marketVerticalOffSet, 1, "%s", playerWeapons[i-1].getName());
                    mvprintw(i + marketVerticalOffSet, marketCostDistance + marketSymbolOffSet, "%c%", playerWeapons[i-1].getSymbol());
                    if (!playerWeapons[i-1].isBought()) {
                        mvprintw(i + marketVerticalOffSet, marketCostDistance, "%d%", playerWeapons[i-1].getCost());
                    } else {
                        if (playerWeapons[i-1].isEquipped()) {
                            mvprintw(i + marketVerticalOffSet, marketCostDistance, "EQ");
                        }
                    }
                    
                } else {
                    mvprintw(playerWeapons.size() + marketVerticalOffSet + 1, 1, "Torna al Mercato");
                }
                }
                attroff(A_REVERSE);
            }
            break;

        case GameState::Playing:

            wclear(win);

            currentLevel->draw(win, player);
            box(win, 0, 0);

            break;

        case GameState::GameOver:
            mvprintw(1, 1, "GAME OVER: HAI PERSO!");
            // Print menu items
            for (int i = 0; i < numGameOverItems; ++i) {
                if (i == selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                mvprintw(1 + i + 1, 1, gameOverItems[i]);
                attroff(A_REVERSE);
            }
            break;
    }
    drawPrompt();
    drawStats();
    refresh();
    wrefresh(win);
    // Add a delay to control the loop speed
    napms(1000/30);

}

void Game::drawPrompt() {
    switch(currentState) {
        case GameState::MainMenu:
            mvprintw(numMainMenuItems + 3, 1, "'w' : Muovi verso l'alto");
            mvprintw(numMainMenuItems + 4, 1, "'s' : Muovi verso il basso");
            mvprintw(numMainMenuItems + 5, 1, "'l' : Seleziona");
            break;
        
        case GameState::Market:
            mvprintw(numMarketItems + 3, 1, "'w' : Muovi verso l'alto");
            mvprintw(numMarketItems + 4, 1, "'s' : Muovi verso il basso");
            mvprintw(numMarketItems + 5, 1, "'l' : Seleziona");
            break;
        
        case GameState::WeaponMenu:
            mvprintw(playerWeapons.size() + 5, 1, "'w' : Muovi verso l'alto");
            mvprintw(playerWeapons.size() + 6, 1, "'s' : Muovi verso il basso");
            mvprintw(playerWeapons.size() + 7, 1, "'l' : Seleziona");
            break;

        case GameState::Playing:
            mvprintw(HEIGHT + 2, 1, "'w' : Muovi verso l'alto");
            mvprintw(HEIGHT + 3, 1, "'s' : Muovi verso il basso");
            mvprintw(HEIGHT + 4, 1, "'a' : Muovi verso sinistra");
            mvprintw(HEIGHT + 5, 1, "'d' : Muovi verso destra");
            mvprintw(HEIGHT + 6, 1, "'l' : Spara");
            mvprintw(HEIGHT + 7, 1, "'q' : Termina partita");
            break;

        case GameState::GameOver:
            mvprintw(numGameOverItems + 3, 1, "'w' : Muovi verso l'alto");
            mvprintw(numGameOverItems + 4, 1, "'s' : Muovi verso il basso");
            mvprintw(numGameOverItems + 5, 1, "'l' : Seleziona");
            break;
    }
}

void Game::drawStats() {
    switch (currentState) {
        case GameState::MainMenu:
            if (loadMessageTimer > 0) {
                mvprintw(3, statsDistance - 10, "NESSUNA PARTITA SALVATA!");
                loadMessageTimer--;
            }
            break;

        case GameState::Market:
        case GameState::WeaponMenu:
            mvprintw(4, statsDistance, "VITA MAX : %d", player.getMaxLife());
            mvprintw(2, statsDistance, "MONETE :   %d", player.getMoney());
            if (saveMessageTimer > 0) {
                mvprintw(6, statsDistance, "PARTITA SALVATA!");
                saveMessageTimer--;
            }
            break;

        case GameState::Playing:
            mvprintw(4, statsDistance, "VITA :     %d", player.getLife());
            mvprintw(2, statsDistance, "MONETE :   %d", player.getMoney());
            mvprintw(6, statsDistance, "LIVELLO :  %d /  %d", currLevelInt + 1, levelVector.size() - 1);
            break;

        
        default:
            break;
    }
}

