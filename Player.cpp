#include "Player.hpp"

Player::Player(int m, int s) {
            this->x = 5;
            this->y = 5;
            this->money = m;
            this->life;
            this->maxLife = 10; 
            this->symbol = s;
            this->bullet = &fionda;
            this->direction = 1;
        };

// getters
int Player::getX() const {
    return this->x;
};        
int Player::getY() const {
    return this->y;
};        
int Player::getMoney() {
    return this->money;
};
int Player::getLife() {
    return this->life;
};
int Player::getMaxLife() {
    return this->maxLife;
};        
char Player::getSymbol() {
    return this->symbol;
};        
int Player::getLevel() {
    return this->level;
};        
int Player::getAtk() {
    return this->atk;
};        
int Player::getDef() {
    return this->def;
};
Bullet * Player::getBullet() {
    return this->bullet;
};

// setters
void Player::setX(int xPos) {
    this->x = xPos;
};        
void Player::setY(int yPos) {
    this->y = yPos;
};        
void Player::setMoney(int amount) {
    this->money = amount;
};
void Player::loadMaxLife(int amount) {
    this->maxLife = amount;
}
void Player::setMaxLife() {
    this->life = this->maxLife;
}
void Player::reduceLife(int damage) {
    this->life -= damage;
};    
void Player::setSymbol(char s) {
    this->symbol = s;
};        
void Player::setLevel(int l) {
    this->level = l;
};        
void Player::setAtk(int a) {
    this->atk = a;
};        
void Player::setDef(int d) {
    this->def = d;
};
void Player::setDirection(int d) {
    this->direction = d; 
};
void Player::setBullet(Bullet *W) {
    removeWeapon();
    this->bullet = W;
};        

// actions
Bullet Player::shoot() {
    // Creates a new bullet from this player with attack related to curent player attack and bullet
    this->bullet->setDirection(this->direction);
    this->bullet->setX(this->x);
    this->bullet->setY(this->y);
    // this->bullet->setDirection(this->direction);
    // switch (this->bullet->getDirection()) {
    //     case 0:
    //         this->bullet->setX(this->x + 1);
    //         this->bullet->setY(this->y);
    //         break;
    //     case 1:
    //         this->bullet->setX(this->x);
    //         this->bullet->setY(this->y + 1);
    //         break;
    //     case 2:
    //         this->bullet->setX(this->x - 1);
    //         this->bullet->setY(this->y);
    //         break;
    //     case 3:
    //         this->bullet->setX(this->x);
    //         this->bullet->setY(this->y - 1);
    //         break;
    //     default:
    //         break;
    // }
    return *this->bullet;
};

void Player::moveUp() {
    if (this->y > 1) this->y--;
    this->direction = 3;
};        
void Player::moveLeft() {
    if (this->x > 1) this->x--;
    this->direction = 2;
};        
void Player::moveRight() {
    if (this->x < WIDTH - 2) this->x++;
    this->direction = 0;
};        
void Player::moveDown() {
    if (this->y < HEIGHT - 2) this->y++;
    this->direction = 1;
};

void Player::levelUp() {
    this->level++;
    this->setAtk(this->getAtk() + 1);
    this->setDef(this->getDef() + 1);
};

void Player::addMaxLife(int amount) {
    this->maxLife = this->maxLife + amount;
};

void Player::addMoney(int amount) {
    this->money = this->money + amount;
};            
void Player::removeMoney(int amount) {
    this->money = this->money - amount;
};  

void Player::removeWeapon() {
    for (Bullet &b : playerWeapons) {
        b.setEquipped(false);
    }
}
