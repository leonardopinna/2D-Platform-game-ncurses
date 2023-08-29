#ifndef HOME_MENU_HPP
#define HOME_MENU_HPP

#include "Menu.hpp"

class HomeMenu : public Menu {

    private: 
        int saveMessageTimer = 0;
    public:  
        HomeMenu(char* menu[], int n, PlayerManager * playerManager) : Menu(menu, n) {
            this->setPlayerManager(playerManager); 
        };

        int getSaveMessageTimer() {
            return this->saveMessageTimer; 
        }

        void setSaveMessageTimer(int time) {
            this->saveMessageTimer = time;
        }


        void handleInput() override {
            switch (getch()) {
                case 'w':
                    selectUp();
                    break;
                case 's':
                    selectDown();
                    break;
                case 'l': // Enter key
                    // Handle menu item selection
                    if (getSelectedItem() == 0) {
                        // Nuova Partita
                        setState(GameState::Playing);
                    } else if (getSelectedItem() == 1) {
                        // Vai al mercato
                        setState(GameState::Market);
                    } else if (getSelectedItem() == 2) {
                        // Salva Partita
                        setState(GameState::SaveGame);
                    } else if (getSelectedItem() == 3) {
                        // Esci
                        setState(GameState::MainMenu);
                    }
                    break;
                default: 
                    break;
            }
        };

        void update() {};

        void render(int dist, int money, int life, char* name) override {
            mvprintw(1, 1, "BENVENUTO! INIZIA UNA PARTITA O VAI AL NEGOZIO!");
            renderMenu();
            renderBasePrompt(this->getNumItems() + 3, 1);
            mvprintw(2, statsDistance, "MONETE    : %d", getPlayerManager()->getMoney());
            mvprintw(4, statsDistance, "VITA MAX  : %d", getPlayerManager()->getMaxLife());
            mvprintw(6, statsDistance, "ARMA      : %s", getPlayerManager()->getWeapon()->getName());
            if (saveMessageTimer > 0) {
                mvprintw(8, statsDistance, "PARTITA SALVATA!");
                saveMessageTimer--;
            }   
        };

};

#endif
