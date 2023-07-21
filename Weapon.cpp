#include <string>
#include "Bullet.cpp"

using namespace std;

const int NAME_LENGTH = 20;

class Weapon {
    private: 
        int id;
        char name[NAME_LENGTH];
        int cost;
        double atk;
        bool bought;
        bool unlocked;
        int speed;
        Bullet bullet;
        
    public: 
        Weapon() {};
        Weapon(int idNum, char n[NAME_LENGTH], int c, double a, int s) {
            this->id = idNum;
            strcpy(this->name, n);
            this->atk = a;
            this->speed = s;
            this->bought = false;
            this->unlocked = false;
            // this->bullet = b;
        };

        // getters
        int getId() {
            return this->id;
        };        
        string getName() {
            return this->name;
        };        
        int getCost() {
            return this->cost;
        };              
        int getAtk() {
            return this->atk;
        };        
        int getSpeed() {
            return this->speed;
        };
        bool isBought() {
            return this->bought;
        }        
        bool isUnlocked() {
            return this->unlocked;
        }

        // setters            
        void setCost(int c) {
            this->cost = c;
        };              
        void setAtk(int a) {
            this->atk = a;
        };        
        void setSpeed(int s) {
            this->speed = s;
        };
        void setIsBought(bool b) {
            this->bought = b;
        }        
        void setIsUnlocked(bool b) {
            this->unlocked = b;
        }
};

