#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Bullet.hpp"
#include "costants/WinSize.hpp"

class Enemy {
    private: 
        int x; 
        int y; 
        char symbol;
        int life; 
        int level;
        int money;
        int atk;
        int def; 
        int direction;
        int size;
        Bullet bullet;

    public: 
        Enemy(char symb, int l, int m, int sz, Bullet b);

        // Getters
        int getX();        
        int getY();
        int getLife();
        int getMoney();             
        char getSymbol();        
        int getLevel();        
        int getAtk();        
        int getDef();
        Bullet getBullet();

        // setters
        void setX(int xPos);        
        void setY(int yPos); 
        void reduceLife(int damage);          
        void setSymbol(char s);        
        void setLevel(int l);        
        void setAtk(int a);        
        void setDef(int d);       

        // actions
        Bullet shoot();

        void moveUp();        
        void moveLeft();        
        void moveRight();        
        void moveDown();

        void move();

};

#endif