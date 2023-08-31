#include "Element.hpp"

Element::Element(char s) : symbol(s) {};

// Getters
int Element::getX() const {
    return this->x;
};        
int Element::getY() const {
    return this->y;
};               
char Element::getSymbol() {
    return this->symbol;
};        

// setters
void Element::setX(int xPos) {
    this->x = xPos;
};        
void Element::setY(int yPos) {
    this->y = yPos;
};       
void Element::setSymbol(char s) {
    this->symbol = s;
};

bool Element::outOfBounds(Element t) {
    return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
};

bool Element::collision(Element a, Element b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}