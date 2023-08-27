#include "Bullet.hpp"

Bullet::Bullet() {}; 
Bullet::Bullet(int id, const char* n, char s, double d, int m, bool b, int c, bool eq) : id(id), name(n), symbol(s), damage(d), maxDistance(m), speed(s), bought(b), cost(c), equipped(eq) {};

// getters
int Bullet::getId() {
    return this->id;
};        
const char* Bullet::getName() {
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
bool Bullet::isBought() {
    return this->bought;
}        
int Bullet::getMaxDistance() {
    return this->maxDistance;
}

int Bullet::getDirection() {
    return this->direction;
}
bool Bullet::isEquipped() {
    return this->equipped;
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
void Bullet::setEquipped(bool b) {
    this->equipped = b;
}      

// Actions
void Bullet::move() {
    this->maxDistance--;
    switch (this->direction) {
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


