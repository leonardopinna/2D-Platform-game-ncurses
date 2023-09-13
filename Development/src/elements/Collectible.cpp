#include "Collectible.hpp"

Collectible::Collectible(int v) : value(v) {};

// getters
int Collectible::getValue() {
    return this->value;
}

// setters
void Collectible::setValue(int amount) {
    this->value = amount;
}