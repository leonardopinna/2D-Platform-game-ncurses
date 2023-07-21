#include "SuperHit.cpp"
#include "Bullet.cpp"
#include "Weapon.cpp"

class Enemy {
    private: 
        int x; 
        int y; 
        char symbol;
        int level;
        int atk;
        int def; 
        int direction;
        int size;

    public: 
        Enemy(int m, int sy, int sz) {
            this->x = 0;
            this->y = 0;
            this->symbol = sy;
            this->direction = 1;
            this->size = sz;
        };

        // Getters
        int getX() {
            return this->x;
        };        
        int getY() {
            return this->y;
        };             
        char getSymbol() {
            return this->symbol;
        };        
        int getLevel() {
            return this->level;
        };        
        int getAtk() {
            return this->atk;
        };        
        int getDef() {
            return this->def;
        };

        // setters
        void setX(int xPos) {
            this->x = xPos;
        };        
        void setY(int yPos) {
            this->y = yPos;
        };            
        void setSymbol(char s) {
            this->symbol = s;
        };        
        void setLevel(int l) {
            this->level = l;
        };        
        void setAtk(int a) {
            this->atk = a;
        };        
        void setDef(int d) {
            this->def = d;
        };       

        // actions
        Bullet shoot() {
            // Creates a new bullet from this Enemy with attack related to curent Enemy attack and weapon
        };

        void moveUp() {
            this->y--;
            this->direction = 3;
        };        
        void moveLeft() {
            this->x--;
            this->direction = 2;
        };        
        void moveRight() {
            this->x++;
            this->direction = 0;
        };        
        void moveDown() {
            this->y++;
            this->direction = 1;
        };


};