#include "Destructible.hpp"

Destructible::Destructible(int l) : life(l) {};

// Getters       
int Destructible::getLife() {
    return this->life;
};               

// setters        
void Destructible::setLife(int amount) {
    this->life = amount;
};   

// actions 
void Destructible::reduceLife(int amount) {
    this->life -= amount; 
};