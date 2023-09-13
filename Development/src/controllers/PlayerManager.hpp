#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include "../datas/PlayerWeapons.hpp"

class PlayerManager {
    private:
        int money;
        int maxLife;
        Bullet * weapon; 
        int record; 

    public: 
        PlayerManager(); 

        // getters
        int getMoney(); 
        int getMaxLife();
        Bullet * getWeapon(); 
        int getRecord();  

        // setters
        void setMoney(int amount);
        void setMaxLife(int amount);
        void setWeapon(Bullet * bullet);
        void setRecord(int r); 

        // actions
        void addMoney(int amount); 
        void removeMoney(int amount);
        void increaseMaxLife(int amount);
        void unlockWeapon(Bullet * bullet);

        // equipment
        void equipWeapon(Bullet * b);
        void removeWeapon(Bullet * b);

        void buyWeapon(Bullet * b);
        bool canBuy(int coins, int cost);
        bool bought(Bullet * b);
};

#endif