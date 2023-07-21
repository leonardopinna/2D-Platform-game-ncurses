#include <string>

using namespace std;

#ifndef BULLET_CPP
#define BULLET_CPP

class Bullet {
    private:
        int id;
        char symbol; 
        int x; 
        int y; 
        double damage;
        string name;
        int direction;
        int maxDistance;
        int cost;
        bool bought;
        int speed;

    public: 
        Bullet() {};
        Bullet(int id, string n, char s, double d, int m, int sp, bool b, int c) : id(id), name(n), symbol(s), damage(d), maxDistance(m), speed(s), bought(b), cost(c) {};

        // getters
        int getId() {
            return this->id;
        };        
        string getName() {
            return this->name;
        };        
        char getSymbol() {
            return this->symbol;
        }
        int getCost() {
            return this->cost;
        };              
        int getDamage() {
            return this->damage;
        };        
        int getSpeed() {
            return this->speed;
        };
        bool isBought() {
            return this->bought;
        }        
        int getMaxDistance() {
            return this->maxDistance;
        }

        int getDirection() {
            return this->direction;
        }

        // setters            
        void setCost(int c) {
            this->cost = c;
        };              
        void setAtk(int a) {
            this->damage = a;
        };        
        void setSpeed(int s) {
            this->speed = s;
        };
        void setIsBought(bool b) {
            this->bought = b;
        } 
        void setX(int xPos) {
            this->x = xPos;
        };        
        void setY(int yPos) {
            this->y = yPos;
        };
        void setDirection(int dir) {
            this->direction = dir;
        }       

        // Actions
        void move() {
            switch (direction)
            {
            case 0: // right
                this->x = this->x + 1;
                break;
            case 1: // down
                this->y = this->y + 1;
                break;
            case 2: // left
                this->x = this->x - 1;
                break;
            case 3: // up
                this->y = this->y - 1;
                break;
            
            default:
                break;
            }
        }
};

#endif // BULLET_CPP