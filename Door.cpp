#include "Door.hpp"

Door::Door(char s) : symbol(s) {};

// Getters
int Door::getX() const {
    return this->x;
};        
int Door::getY() const {
    return this->y;
};               
char Door::getSymbol() {
    return this->symbol;
};        

// setters
void Door::setX(int xPos) {
    this->x = xPos;
};        
void Door::setY(int yPos) {
    this->y = yPos;
};       
void Door::setSymbol(char s) {
    this->symbol = s;
};