#include <string>

using namespace std;

#ifndef BULLET_CPP
#define BULLET_CPP

class Bullet {
    private:
        static int id;
        char symbol; 
        int x; 
        int y; 
        double damage;
        string name;
        int direction;

    public: 
        Bullet() {};

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