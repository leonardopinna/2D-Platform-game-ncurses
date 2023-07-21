
class SuperHit {
private:
    int recoverTime; 
    int timeRemaining;
    double damage;
    bool usable;

public:
    SuperHit() {
        this->recoverTime = 10;
        this->timeRemaining = 0;
        this->damage = 50; 
        this->usable = true;
    };

    void launch() {
        if (this->usable) {
            this->timeRemaining = this->recoverTime;
            this->usable = false;
        } else {
        }
    }

    void update() {
        if (this->timeRemaining > 0) {
            this->timeRemaining--;
            if (this->timeRemaining == 0) {
                this->usable = true;
            }
        }
    }
};