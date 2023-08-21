#include "Bullet.hpp"

Bullet::Bullet() {};
Bullet::Bullet(int id, string n, char s, double d, int m, int sp, bool b, int c) : id(id), name(n), symbol(s), damage(d), maxDistance(m), speed(s), bought(b), cost(c) {};

// getters
int Bullet::getId() {
    return this->id;
};        
string Bullet::getName() {
    return this->name;
};
int Bullet::getX() {
    return this->x;
};        
int Bullet::getY() {
    return this->y;
};
char Bullet::getSymbol() {
    return this->symbol;
}
int Bullet::getCost() {
    return this->cost;
};              
int Bullet::getDamage() {
    return this->damage;
};        
int Bullet::getSpeed() {
    return this->speed;
};
bool Bullet::isBought() {
    return this->bought;
}        
int Bullet::getMaxDistance() {
    return this->maxDistance;
}

int Bullet::getDirection() {
    return this->direction;
}

// setters            
void Bullet::setCost(int c) {
    this->cost = c;
};              
void Bullet::setAtk(int a) {
    this->damage = a;
};        
void Bullet::setSpeed(int s) {
    this->speed = s;
};
void Bullet::setIsBought(bool b) {
    this->bought = b;
} 
void Bullet::setX(int xPos) {
    this->x = xPos;
};        
void Bullet::setY(int yPos) {
    this->y = yPos;
};
void Bullet::setDirection(int dir) {
    this->direction = dir;
}       

// Actions
void Bullet::move() {
    this->maxDistance--;
    switch (direction)
    {
    case 0: // right
        this->x = this->x + 1;
        break;
    case 1: // down
        this->y = this->y + 1;
        break;
    case 2: // left
        this->x = this->x - 1;
        break;
    case 3: // up
        this->y = this->y - 1;
        break;
    
    default:
        break;
    }
}