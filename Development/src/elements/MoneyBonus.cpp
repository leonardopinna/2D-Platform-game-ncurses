#include "MoneyBonus.hpp"

MoneyBonus::MoneyBonus(int v, char ch) : Collectible(v), Element(ch) {};

// getters
int MoneyBonus::getValue() {
    return this->value;
}

// setters
void MoneyBonus::setValue(int amount) {
    this->value = amount;
}