#include "Wall.hpp"

Wall::Wall(int l, char s) : life(l), symbol(s) {};

// Getters
int Wall::getX() const {
    return this->x;
};        
int Wall::getY() const {
    return this->y;
};        
int Wall::getLife() {
    return this->life;
};        
char Wall::getSymbol() {
    return this->symbol;
};        

// setters
void Wall::setX(int xPos) {
    this->x = xPos;
};        
void Wall::setY(int yPos) {
    this->y = yPos;
};;        
void Wall::setLife(int amount) {
    this->life = amount;
};;    
void Wall::setSymbol(char s) {
    this->symbol = s;
};;          

