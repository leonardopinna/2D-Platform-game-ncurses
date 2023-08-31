#include "Bullet.hpp"

Bullet::Bullet(string n, char s, double d, int m, bool b, int c, bool eq) :
    name(n),
    Movable(s, Direction::RIGHT),
    damage(d),
    maxDistance(m),
    bought(b),
    cost(c),
    equipped(eq) {};

// getters
        
string Bullet::getName() {
    return this->name;
};
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
bool Bullet::isEquipped() {
    return this->equipped;
}

// setters            
void Bullet::setCost(int c) {
    this->cost = c;
};              
void Bullet::setDamage(int a) {
    this->damage = a;
};
void Bullet::setIsBought(bool b) {
    this->bought = b;
} 
void Bullet::setEquipped(bool b) {
    this->equipped = b;
}
void Bullet::reduceDistance() {
    this->maxDistance--;
}      

// Actions
void Bullet::move() {
    this->reduceDistance();
    switch (this->getDirection()) {
        case Direction::RIGHT:
            this->setX(this->getX() + 1);
            break;
        case Direction::DOWN:
            this->setY(this->getY() + 1);
            break;
        case Direction::LEFT:
            this->setX(this->getX() - 1);
            break;
        case Direction::UP:
            this->setY(this->getY() - 1);
            break;
        
        default:
            break;
    }
}


