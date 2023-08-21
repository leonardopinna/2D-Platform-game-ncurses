#include "Enemy.hpp"

#include "SuperHit.hpp"
#include "Bullet.hpp"

Enemy::Enemy(char symb, int sz, Bullet b) {
    this->x = 0;
    this->y = 0;
    this->symbol = symb;
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

// setters
void Enemy::setX(int xPos) {
    this->x = xPos;
};        
void Enemy::setY(int yPos) {
    this->y = yPos;
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
};

void Enemy::moveUp() {
    this->y--;
    this->direction = 3;
};        
void Enemy::moveLeft() {
    this->x--;
    this->direction = 2;
};        
void Enemy::moveRight() {
    this->x++;
    this->direction = 0;
};        
void Enemy::moveDown() {
    this->y++;
    this->direction = 1;
};

void Enemy::move() {
    int n = rand() % 6 + 1;
    switch (n)
    {
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
    case 5:
    case 6:
        break;
    
    default:
        break;
    }

}