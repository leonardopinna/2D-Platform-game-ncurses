#include "SuperHit.cpp"
#include "Bullet.cpp"

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
        Bullet bullet;

    public: 
        Enemy(int sy, int sz, Bullet b) {
            this->x = 0;
            this->y = 0;
            this->symbol = sy;
            this->direction = 1;
            this->size = sz;
            this->bullet = b; 
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

        void move() {
            int n = rand() % 6 + 1;
            switch (n)
            {
            case 1:
                moveUp();
                break;
            case 2:
                moveLeft();
                break;
            case 3:
                moveRight();
                break;
            case 4:
                moveDown();
                break;
            case 5:
            case 6:
                break;
            
            default:
                break;
            }

        }

};