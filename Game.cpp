#include "Game.hpp"

using namespace std;

Game::Game() {};

void Game::loadGame(){};
void Game::saveGame(){};
void Game::createLevel(){};

void Game::initializeGame() {
        
        levelVector.push_back(new Level(3, 3));
        currentLevel = levelVector[0];
        currLevelInt = 0; 

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
                case 10: // Enter key
                    // Handle menu item selection
                    if (selectedItem == 0) {
                        // Nuova Partita
                        currentState = GameState::Market;
                    } else if (selectedItem == 1) {
                        // Carica Partita

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
                case 10: // Enter key
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
                    selectedItem = (selectedItem - 1 + numWeapons + 1) % (numWeapons + 1);
                    break;
                case 's':
                    selectedItem = (selectedItem + 1) % (numWeapons + 1);
                    break;
                case 10: // Enter key
                    // Handle weapon buy process
                    if (selectedItem == numWeapons) {
                        selectedItem = 0;
                        currentState = GameState::Market;
                    } else {
                        if (player.getMoney() >= playerWeapons[selectedItem].getCost()) {
                        player.removeMoney(playerWeapons[selectedItem].getCost());
                        player.setBullet(playerWeapons[selectedItem]);
                        playerWeapons[selectedItem].setIsBought(true);
                        }
                    }
            
                    break;
            }

            break;
        case GameState::Playing:
            switch (getch()) {
                case 'w':
                    if (player.getY() > 1) player.moveUp();
                    break;

                case 's':
                    if (player.getY() < HEIGHT - 2) player.moveDown();
                    break;

                case 'a':
                    if (player.getX() > 1) player.moveLeft();
                    break;

                case 'd':
                    if (player.getX() < WIDTH - 2) player.moveRight();
                    break;

                case 'l':
                    currentLevel->playerBulletVector.push_back(player.shoot());
                    break;

                case 'q':
                    gameOver();
                    break;

                case 'Q':
                    stopGame();
                    break; 

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
                case 10: // Enter key
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
                    it->move();
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
                    player.reduceLife(b->getBullet().getDamage());                         
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
                if (currLevelInt == levelVector.size() - 1) {
                    Level* nextLevel = new Level(3, 3);
                    levelVector.push_back(nextLevel);
                    currLevelInt++;
                    currentLevel = levelVector[currLevelInt];
                    player.setX(currentLevel->doorVector[0].getX()+1);
                    player.setY(currentLevel->doorVector[0].getY());
                } else {
                    currLevelInt++;
                    currentLevel = levelVector[currLevelInt];
                    player.setX(currentLevel->doorVector[0].getX()+1);
                    player.setY(currentLevel->doorVector[0].getY());
                }
    
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
                mvprintw(1, 1, "BENVENUTO NEL MERCATO, COMPRA ARMI O ACCESSORI!");
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
            mvprintw(1, 1, "SELEZIONA O COMPRA ARMA");
            for (int i = 0; i < numWeapons + 1; ++i) {
                if (i == selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                if (!(i == numWeapons)) {
                    mvprintw(i + 2, 1, "%s", playerWeapons[i].getName());
                    mvprintw(i + 2, weaponsCostDistance + 5, "%c%", playerWeapons[i].getSymbol());
                    if (!playerWeapons[i].isBought()) {
                        mvprintw(i + 2, weaponsCostDistance, "%d%", playerWeapons[i].getCost());
                    }
                } else {
                    mvprintw(numWeapons + 2, 1, "Torna al Mercato");
                }
                attroff(A_REVERSE);
            }
            break;

        case GameState::Playing:
            wclear(win);
            box(this->win, 0, 0);

            int win_height, win_width;
            getmaxyx(this->win, win_height, win_width);

            // Calculate the center position
            currentLevel->center_y = win_height / 2;
            currentLevel->center_x = win_width / 2;

            // Draw the '&' in the center of the window
            mvwaddch(win, player.getY(), player.getX(), '&');
            for (Bullet b : currentLevel->playerBulletVector) {
                printf("%d", b.getY());
                mvwaddch(this->win, b.getY(), b.getX(), b.getSymbol());
            }
            for (Bullet b : currentLevel->enemyBulletVector) {
                mvwaddch(this->win, b.getY(), b.getX(), b.getSymbol());
            }
            for (Enemy e : currentLevel->enemyVector) {
                mvwaddch(this->win, e.getY(), e.getX(), e.getSymbol());
            }
            for (Wall w : currentLevel->wallVector) {
                mvwaddch(this->win, w.getY(), w.getX(), w.getSymbol());
            }
            for (Door d : currentLevel->doorVector) {
                mvwaddch(this->win, d.getY(), d.getX(), d.getSymbol());
            }
            mvprintw(1, WIDTH + 3, "VITA RESIDUA : %d", player.getLife());
            mvprintw(3, WIDTH + 3, "MONETE : %d", player.getMoney());

            refresh();
            wrefresh(this->win);
            break;

        case GameState::GameOver:
            mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 5, "GAME OVER"); 
            mvprintw(HEIGHT + 2, 1, "GAME OVER: HAI PERSO!");
            // Print menu items
            for (int i = 0; i < numGameOverItems; ++i) {
                if (i == selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                mvprintw(HEIGHT + 2 + i + 1, 1, gameOverItems[i]);
                attroff(A_REVERSE);
            }
            break;
    }
    
    refresh();
    // Add a delay to control the loop speed
    napms(1000/60);

}

