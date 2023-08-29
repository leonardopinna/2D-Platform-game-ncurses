#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP 

#include <vector>
#include <ncurses.h>

#include "../gameElements/Player.hpp"
#include "../gameElements/Level.hpp"

#include "Menu.hpp"

using namespace std;

class LevelManager : public Menu {
    private:
        double timeSinceLastBulletUpdate;
        chrono::time_point<chrono::steady_clock> currentTime;
        chrono::time_point<chrono::steady_clock> startTime;
        chrono::duration<double> elapsedTime;

    public:
        template <typename T>
        bool outOfBounds(T& t) {
            return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
        }

        template <typename T1, typename T2>
        bool collision(T1& a, T2& b) {
            return a.getX() == b.getX() && a.getY() == b.getY();
        }

        vector<Level*> levelVector;
        Level* currentLevel;
        int level;
        
        Player * player; 
        int maxLife; 
        Bullet * weapon;

        bool gameStarted;  

    LevelManager(WINDOW * wdw, PlayerManager * playerManager) : Menu({}, 0) {
        this->maxLife = playerManager->getMaxLife();
        this->player = new Player('&', playerManager->getMaxLife(), Direction::RIGHT, playerManager->getWeapon());
        this->weapon = playerManager->getWeapon();
        this->setPlayerManager(playerManager);
        this->level = 0;
        this->gameStarted = false; 
    }


    void initializeGame() {

        level = 0;
        if (levelVector.size() > 0) {
            levelVector[0] = new Level(level);
        } else {
            levelVector.push_back(new Level(level));
        }
            
        currentLevel = levelVector[0];
            
        player->setLife(this->getPlayerManager()->getMaxLife());
        player->setBullet(this->getPlayerManager()->getWeapon());

        player->setX(5);
        player->setY(5);

        gameStarted = true;
    }

    void gameOver() {
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

    void handleInput() override {
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

                // case 'Q':
                //     stopGame();
                //     break; 

                default:
                    // Handle other keys or do nothing
                    break;
            }
        }
    

    void update() override {
        if (!gameStarted) {
            initializeGame();
        }
        currentTime = chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        startTime = currentTime;

        // Update bullet and enemy movement based on time elapsed
        timeSinceLastBulletUpdate += elapsedTime.count();
        while (timeSinceLastBulletUpdate >= bulletSpeed) {
            for (auto it = currentLevel->playerBulletVector.begin() ; it != currentLevel->playerBulletVector.end(); ) {
                it->move();
                if (outOfBounds(*it) || it->getMaxDistance()==0) {
                    it = currentLevel->playerBulletVector.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = currentLevel->enemyBulletVector.begin() ; it != currentLevel->enemyBulletVector.end(); ) {
                it->move();
                if (outOfBounds(*it) || it->getMaxDistance()==0) {
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
            if (collision(*b, *player)) {
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
            if (collision(*b, *player)) {
                player->reduceLife(b->getBullet()->getDamage());                         
            }
        }
        // Player bullet - Enemies collision
        for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
            bool collided = false;
            for (auto enemyIt = currentLevel->enemyVector.begin() ; enemyIt != currentLevel->enemyVector.end(); ) {
                // collision check
                if (collision(*b, *enemyIt)) {
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
        // Player bullet - Wall collision
        for (auto b = currentLevel->playerBulletVector.begin() ; b != currentLevel->playerBulletVector.end(); ) {
            bool collided = false;
            for (auto wallIt = currentLevel->wallVector.begin() ; wallIt != currentLevel->wallVector.end(); ) {
                // collision check
                if (collision(*b, *wallIt)) {
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
            if (collision(*b, *player)) {
                getPlayerManager()->addMoney(moneyBonus);
                collided = true;                        
            }
            if (collided) {
                b = currentLevel->moneyVector.erase(b);
            } else {
                ++b;
            }
        } 
        

        // Player - Money Bonus collision
        for (auto b = currentLevel->moneyVector.begin() ; b != currentLevel->moneyVector.end();) {
            bool collided = false;
            if (collision(*b, *player)) {
                getPlayerManager()->addMoney(moneyBonus);
                collided = true;                        
            }
            if (collided) {
                b = currentLevel->moneyVector.erase(b);
            } else {
                ++b;
            }
        }
        // TO DO: CREARE CLASSE GAME MANAGER CHE GESTISCE LA LOGICA DEI LIVELLI DI GIOCO
        // Gameover trigger
        if (player->getLife() <= 0) {
            gameOver();
        }

        // Change Level trigger
        
        if (collision(*player, currentLevel->doorVector[0])) {
            
            if (level != 0) {
                level--;
                 currentLevel = levelVector[level];
                player->setX(currentLevel->doorVector[1].getX()-1);
                player->setY(currentLevel->doorVector[1].getY());
            }
        }

        if (collision(*player, currentLevel->doorVector[1])) {
            level++;
            if (level == levelVector.size()) {
                levelVector.push_back(new Level(level + 1));
            }
            currentLevel = levelVector[level];
            player->setX(currentLevel->doorVector[0].getX()+1);
            player->setY(currentLevel->doorVector[0].getY());

        }
    }

    void draw(WINDOW * wdw) {
            for (Bullet b : currentLevel->playerBulletVector) {
                mvwaddch(wdw, b.getY(), b.getX(), b.getSymbol());
            }
            for (Bullet b : currentLevel->enemyBulletVector) {
                mvwaddch(wdw, b.getY(), b.getX(), b.getSymbol());
            }
            for (Wall w : currentLevel->wallVector) {
                mvwaddch(wdw, w.getY(), w.getX(), w.getSymbol());
            }
            for (Wall w : currentLevel->moneyVector) {
                mvwaddch(wdw, w.getY(), w.getX(), w.getSymbol());
            }
            for (Door d : currentLevel->doorVector) {
                mvwaddch(wdw, d.getY(), d.getX(), d.getSymbol());
            }
            for (Enemy e : currentLevel->enemyVector) {
                mvwaddch(wdw, e.getY(), e.getX(), e.getSymbol());
            }
            mvwaddch(wdw, this->player->getY(), this->player->getX(), this->player->getSymbol());
            box(wdw, 0, 0);
            mvprintw(HEIGHT + 2, 1, "'w' : Muovi verso l'alto");
            mvprintw(HEIGHT + 3, 1, "'s' : Muovi verso il basso");
            mvprintw(HEIGHT + 4, 1, "'a' : Muovi verso sinistra");
            mvprintw(HEIGHT + 5, 1, "'d' : Muovi verso destra");
            mvprintw(HEIGHT + 6, 1, "'l' : Spara");
            mvprintw(HEIGHT + 7, 1, "'q' : Termina partita");
            renderGameStats(statsDistance, getPlayerManager()->getMoney(), player->getLife(), player->getBullet()->getName());
    }

    void render(int dist, int money, int life, char* name) {

            // draw();
            // box(this->wdw, 0, 0);
            mvprintw(HEIGHT + 2, 1, "'w' : Muovi verso l'alto");
            mvprintw(HEIGHT + 3, 1, "'s' : Muovi verso il basso");
            mvprintw(HEIGHT + 4, 1, "'a' : Muovi verso sinistra");
            mvprintw(HEIGHT + 5, 1, "'d' : Muovi verso destra");
            mvprintw(HEIGHT + 6, 1, "'l' : Spara");
            mvprintw(HEIGHT + 7, 1, "'q' : Termina partita");
            renderGameStats(statsDistance, getPlayerManager()->getMoney(), player->getLife(), player->getBullet()->getName());
            
    }
    
};

#endif