#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SuperHit.hpp"
#include "Bullet.hpp"
#include "GameData.hpp"

class Player {
    private: 
        int x; 
        int y; 
        int money;
        char symbol;
        int level;
        int atk;
        int def; 
        Bullet bullet; 
        SuperHit special;
        int direction;

    public: 
        Player(int m, int s);

        // Getters
        int getX() const;        
        int getY() const;        
        int getMoney();        
        char getSymbol();        
        int getLevel();        
        int getAtk();        
        int getDef();
        Bullet getBullet();

        // setters
        void setX(int xPos);        
        void setY(int yPos);        
        void setMoney(int amount);    
        void setSymbol(char s);        
        void setLevel(int l);        
        void setAtk(int a);        
        void setDef(int d);
        void setbullet(Bullet W);        

        // actions
        Bullet shoot();

        void moveUp();        
        void moveLeft();        
        void moveRight();        
        void moveDown();

        void levelUp();

        void addMoney(int amount);            
        void removeMoney(int amount);     

};

#endif