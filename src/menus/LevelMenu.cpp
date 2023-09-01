#include "LevelMenu.hpp"

LevelMenu:: LevelMenu(PlayerManager * playerManager) : Menu("", {}, {}, "", playerManager) {
    this->player = new Shooter('&', playerManager->getMaxLife(), Direction::RIGHT, playerManager->getWeapon()); 
    this->gameStarted = false; 
}

void LevelMenu::initializeGame() {

    this->level = 0;
    this->startingLevel = getPlayerManager()->getMaxLife() / startingLevelIncreaseDelta;
    levelVector.push_back(new Level(startingLevel + 1, availableLevels[rand() % availableLevels.size()]));
        
    currentLevel = levelVector[0];
        
    player->setLife(getPlayerManager()->getMaxLife());
    player->setBullet(getPlayerManager()->getWeapon());

    player->setX(currentLevel->doorVector[0].getX()+1);
    player->setY(currentLevel->doorVector[0].getY());

    gameStarted = true;
}

GameState LevelMenu::run(GameState gs, WINDOW * wdw) {
    this->setState(gs);
    LevelMenu::handleInput(); 
    update(); 
    draw(wdw); 
    return this->getState();
}

void LevelMenu::gameOver() {
    for (Level* L : levelVector) {
        L->enemyVector.clear();
        L->enemyBulletVector.clear();
        L->playerBulletVector.clear();
        L->wallVector.clear();
        L->doorVector.clear();
    }
    levelVector.clear();

    gameStarted = false; 

    setState(GameState::GameOver);
}; 

void LevelMenu::handleInput() {
    switch (getch()) {
            case 'w':
                if (currentLevel->isFreePositionToGo(player->getX(), player->getY() - 1)) player->moveUp(); else player->setDirection(Direction::UP);
                break;

            case 's':
                if (currentLevel->isFreePositionToGo(player->getX(), player->getY() + 1)) player->moveDown(); else player->setDirection(Direction::DOWN);
                break;

            case 'a':
                if (currentLevel->isFreePositionToGo(player->getX() - 1, player->getY())) player->moveLeft(); else player->setDirection(Direction::LEFT);
                break;

            case 'd':
                if (currentLevel->isFreePositionToGo(player->getX() + 1, player->getY())) player->moveRight(); else player->setDirection(Direction::RIGHT);
                break;

            case 'l':
                currentLevel->playerBulletVector.push_back(player->shoot());
                break;

            case 'q':
            gameStarted = false;
                gameOver(); 
                break; 

            default:
                break;
        }
    }

void LevelMenu::update() {
    if (!gameStarted) {
        initializeGame();
    }
    currentTime = chrono::steady_clock::now();
    elapsedTime = currentTime - startTime;
    startTime = currentTime;

    // Update bullet and enemy movement
    deltaTime += elapsedTime.count();
    while (deltaTime >= gameSpeed) {
        for (auto it = currentLevel->playerBulletVector.begin() ; it != currentLevel->playerBulletVector.end(); ) {
            it->move();
            if (it->outOfBounds() || it->getMaxDistance()==0) {
                it = currentLevel->playerBulletVector.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = currentLevel->enemyBulletVector.begin() ; it != currentLevel->enemyBulletVector.end(); ) {
            it->move();
            if (it->outOfBounds() || it->getMaxDistance()==0) {
                it = currentLevel->enemyBulletVector.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = currentLevel->enemyVector.begin() ; it != currentLevel->enemyVector.end(); it++) {
            int n = rand() % it->getMoveProb() + 1;
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
            if (rand() % it->getShootProb() == 0) currentLevel->enemyBulletVector.push_back(it->shoot());
        }

        deltaTime -= gameSpeed;
    }

    // CHECK COLLISION OF PLAYER WITH ELEMENTS
    // Enemy bullet - Player collision
    for (auto b = currentLevel->enemyBulletVector.begin() ; b != currentLevel->enemyBulletVector.end(); ) {
        bool collided = false;
        if (b->collision(*player)) {
            player->reduceLife(b->getDamage());
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
        if (b->collision(*player)) {
            player->reduceLife(b->getBullet()->getDamage());                         
        }
    }

    // Player - Money Bonus collision
    for (auto b = currentLevel->moneyVector.begin() ; b != currentLevel->moneyVector.end();) {
        bool collided = false;
        if (b->collision(*player)) {
            getPlayerManager()->addMoney(moneyBonus);
            collided = true;                        
        }
        if (collided) {
            b = currentLevel->moneyVector.erase(b);
        } else {
            ++b;
        }
    } 

    // CHECK COLLISION OF PLAYER BULLETS WITH ELEMENTS
    // Player bullet - Enemies collision
    for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
        bool collided = false;
        for (auto enemyIt = currentLevel->enemyVector.begin() ; enemyIt != currentLevel->enemyVector.end(); ) {
            // collision check
            if (b->collision(*enemyIt)) {
                enemyIt->reduceLife(b->getDamage());
                // if life to zero, delete enemy
                if (enemyIt->getLife() <= 0) {
                    enemyIt = currentLevel->enemyVector.erase(enemyIt);
                    getPlayerManager()->addMoney(enemyIt->getValue());
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
    // Player bullet - Wall collision (Wall damage)
    for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
        bool collided = false;
        for (auto wallIt = currentLevel->wallVector.begin() ; wallIt != currentLevel->wallVector.end(); ) {
            // collision check
            if (b->collision(*wallIt)) {
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
    
    // OTHER COLLISIONS
    // Enemy bullet - Wall collision (No wall damage)
    for (auto b = currentLevel->enemyBulletVector.begin() ; b != currentLevel->enemyBulletVector.end(); ) {
        bool collided = false;
        for (auto wallIt = currentLevel->wallVector.begin() ; wallIt != currentLevel->wallVector.end(); ) {
            if (b->collision(*wallIt)) { 
                collided = true;
                break;
            } else {
                ++wallIt;
            }
        }   
        if (collided) {
            b = currentLevel->enemyBulletVector.erase(b);
        } else {
            ++b;
        }
    }
    
    // Change Level trigger
    if (player->collision(currentLevel->doorVector[0])) {
        
        if (level != 0) {
            level--;
            startingLevel--;
                currentLevel = levelVector[level];
            player->setX(currentLevel->doorVector[1].getX()-1);
            player->setY(currentLevel->doorVector[1].getY());
        }
    }

    if (player->collision(currentLevel->doorVector[1])) {
        level++; startingLevel++;
        if (level == levelVector.size()) {
            levelVector.push_back(new Level(startingLevel + 1, availableLevels[rand() % availableLevels.size()]));
        }
        currentLevel = levelVector[level];
        player->setX(currentLevel->doorVector[0].getX()+1);
        player->setY(currentLevel->doorVector[0].getY());

    }

    // Gameover trigger
    if (player->getLife() <= 0) {
        gameOver();
    }
}

void LevelMenu::draw(WINDOW * wdw) {
        for (Bullet b : currentLevel->playerBulletVector) {
            mvwaddch(wdw, b.getY(), b.getX(), b.getSymbol());
        }
        for (Bullet b : currentLevel->enemyBulletVector) {
            mvwaddch(wdw, b.getY(), b.getX(), b.getSymbol());
        }
        for (Wall w : currentLevel->wallVector) {
            mvwaddch(wdw, w.getY(), w.getX(), w.getSymbol());
        }
        for (MoneyBonus w : currentLevel->moneyVector) {
            mvwaddch(wdw, w.getY(), w.getX(), w.getSymbol());
        }
        for (Element d : currentLevel->doorVector) {
            mvwaddch(wdw, d.getY(), d.getX(), d.getSymbol());
        }
        for (Enemy e : currentLevel->enemyVector) {
            mvwaddch(wdw, e.getY(), e.getX(), e.getSymbol());
        }
        mvwaddch(wdw, this->player->getY(), this->player->getX(), this->player->getSymbol());
        box(wdw, 0, 0);
        mvprintw(11, statsDistance, "'w' : Muovi verso l'alto");
        mvprintw(12, statsDistance, "'s' : Muovi verso il basso");
        mvprintw(13, statsDistance, "'a' : Muovi verso sinistra");
        mvprintw(14, statsDistance, "'d' : Muovi verso destra");
        mvprintw(15, statsDistance, "'l' : Spara");
        mvprintw(16, statsDistance, "'q' : Termina partita");
        mvprintw(2, statsDistance, "MONETE    : %d", this->getPlayerManager()->getMoney());
        mvprintw(4, statsDistance, "VITA      : %d / %d", player->getLife(), this->getPlayerManager()->getMaxLife());
        mvprintw(6, statsDistance, "ARMA      : %s", this->getPlayerManager()->getWeapon()->getName().c_str());
        mvprintw(8, statsDistance, "LIVELLO   : %d / %d", this->level + 1, this->levelVector.size());
}
