#include "SuperHit.cpp"
#include "Bullet.cpp"
#include "GameData.cpp"

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
        Player(int m, int s) {
            this->x = 5;
            this->y = 5;
            this->money = m;
            this->symbol = s;
            this->bullet = fionda;
            this->direction = 1;
        };

        // Getters
        int getX() const {
            return this->x;
        };        
        int getY() const {
            return this->y;
        };        
        int getMoney() {
            return this->money;
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
        Bullet getBullet() {
            return this->bullet;
        };

        // setters
        void setX(int xPos) {
            this->x = xPos;
        };        
        void setY(int yPos) {
            this->y = yPos;
        };        
        void setMoney(int amount) {
            this->money = amount;
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
        void setbullet(Bullet W) {
            this->bullet = W;
        };        

        // actions
        Bullet shoot() {
            // Creates a new bullet from this player with attack related to curent player attack and bullet
            this->bullet.setX(this->x);
            this->bullet.setY(this->y); 
            this->bullet.setDirection(this->direction);
            return this->bullet;
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

        void levelUp() {
            this->level++;
            this->setAtk(this->getAtk() + 1);
            this->setDef(this->getDef() + 1);
        };

        void addMoney(int amount) {
            this->money = this->money + amount;
        };            
        void removeMoney(int amount) {
            this->money = this->money + amount;
        };     

};