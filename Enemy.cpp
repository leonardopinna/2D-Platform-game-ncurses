#include <cstdlib>

#include "Enemy.hpp"

Enemy::Enemy(char symb, int l, int m, int sz, Bullet b) {
    this->x = 0;
    this->y = 0;
    this->symbol = symb;
    this->money = m;
    this->life = l;
    this->direction = 1;
    this->size = sz;
    this->bullet = b; 
};

// Getters
int Enemy::getX() {
    return this->x;
};        
int Enemy::getY() {
    return this->y;
};             
int Enemy::getLife() {
    return this->life;
}
int Enemy::getMoney() {
    return this->money;
}
char Enemy::getSymbol() {
    return this->symbol;
};        
int Enemy::getLevel() {
    return this->level;
};        
int Enemy::getAtk() {
    return this->atk;
};        
int Enemy::getDef() {
    return this->def;
};
Bullet Enemy::getBullet() {
    return this->bullet;
}

// setters
void Enemy::setX(int xPos) {
    this->x = xPos;
};        
void Enemy::setY(int yPos) {
    this->y = yPos;
};            
void Enemy::reduceLife(int damage) {
    this->life -= damage;
};
void Enemy::setSymbol(char s) {
    this->symbol = s;
};        
void Enemy::setLevel(int l) {
    this->level = l;
};        
void Enemy::setAtk(int a) {
    this->atk = a;
};        
void Enemy::setDef(int d) {
    this->def = d;
};       

// actions
Bullet Enemy::shoot() {
    // Creates a new bullet from this Enemy with attack related to curent Enemy attack and weapon
    this->bullet.setDirection(this->direction);
    switch (this->bullet.getDirection()) {
        case 0:
            this->bullet.setX(this->x + 1);
            this->bullet.setY(this->y);
            break;
        case 1:
            this->bullet.setX(this->x);
            this->bullet.setY(this->y + 1);
            break;
        case 2:
            this->bullet.setX(this->x - 1);
            this->bullet.setY(this->y);
            break;
        case 3:
            this->bullet.setX(this->x);
            this->bullet.setY(this->y - 1);
            break;
        default:
            break;
    }
    return this->bullet;
};

void Enemy::moveUp() {
    if (this->y > 1) this->y--;
    this->direction = 3;
};        
void Enemy::moveLeft() {
    if (this->x > 1) this->x--;
    this->direction = 2;
};        
void Enemy::moveRight() {
    if (this->x < WIDTH - 2) this->x++;
    this->direction = 0;
};        
void Enemy::moveDown() {
    if (this->y < HEIGHT - 2) this->y++;
    this->direction = 1;
};

void Enemy::move() {
    int n = rand() % 15 + 1;
    switch (n) {
        case 1:
            moveUp();
            break;
        case 2:
            moveLeft();
            break;
        case 3:
            moveRight();
            break;
        case 4:
            moveDown();
            break;
        default:
            break;
    }

}