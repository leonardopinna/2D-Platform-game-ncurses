#include "PlayerManager.hpp"

PlayerManager::PlayerManager() : money(0), maxLife(10), weapon(&sasso) {
    this->weapon->setEquipped(true);
};

// getters
int PlayerManager::getMoney() {
    return this->money;
};
int PlayerManager::getMaxLife() {
    return this->maxLife;
}
Bullet * PlayerManager::getWeapon() {
    return this->weapon;
}
int PlayerManager::getRecord() {
    return this->record; 
} 

// setters
void PlayerManager::setMoney(int amount) {
    this->money = amount;
};
void PlayerManager::setMaxLife(int amount) {
    this->maxLife = amount;
}
void PlayerManager::setWeapon(Bullet * bullet) {
    this->weapon->setEquipped(false);
    this->weapon = bullet; 
    this->weapon->setEquipped(true);
}
void PlayerManager::setRecord(int r) {
    this->record = r; 
}

// actions
void PlayerManager::addMoney(int amount) {
    this->money += amount;
};
void PlayerManager::removeMoney(int amount) {
    this->money -= amount;
};

void PlayerManager::increaseMaxLife(int amount) {
    this->maxLife += amount;
};
void PlayerManager::unlockWeapon(Bullet * bullet) {
    bullet->setIsBought(true); 
};

// equipment
void PlayerManager::equipWeapon(Bullet * b) {
    b->setEquipped(true);
};
void PlayerManager::removeWeapon(Bullet * b) {
    b->setEquipped(false);
};


// purchases
void PlayerManager::buyWeapon(Bullet * b) {
    b->setIsBought(true);
};
bool PlayerManager::canBuy(int coins, int cost) {
    return coins >= cost;
};

bool PlayerManager::bought(Bullet * b) {
    return b->isBought(); 
}
