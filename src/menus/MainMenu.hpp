#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "Menu.hpp"

class MainMenu : public Menu {
    private: 
        int loadMessageTimer;

    public:  
        MainMenu(char* menu[], int n) : Menu(menu, n) {
            this->loadMessageTimer = 0; 
        };

        int getLoadMessageTimer() {
            return this->loadMessageTimer;
        }

        void setLoadMessageTimer(int time) {
            this->loadMessageTimer = time;
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
                        setState(GameState::Home);
                    } else if (getSelectedItem() == 1) {
                        // Carica Partita
                        setState(GameState::LoadGame);
                    } else if (getSelectedItem() == 2) {
                        // Esci
                        setState(GameState::ExitGame);
                    }
                    break;
                default: 
                break; 
            }
        };

        void update() override {};

        void render(int dist, int money, int life, char* name) override {
            clear();
            mvprintw(1, 1, "WARRIOR GAME by Leonardo Pinna");
            renderMenu();
            renderBasePrompt(this->getNumItems() + 3, 1);
            if (loadMessageTimer > 0) {
                mvprintw(3, statsDistance - 10, "NESSUNA PARTITA SALVATA!");
                loadMessageTimer--;
            }   
        };

};

#endif
