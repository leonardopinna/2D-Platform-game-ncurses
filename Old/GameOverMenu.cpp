#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu(char* menu[], int n) : Menu(menu, n) {};

void GameOverMenu::handleInput() {
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
                // Mercato
                setState(GameState::Home);
            } else if (getSelectedItem() == 2) {
                // Esci
                setState(GameState::MainMenu); 
            }
            break;
    }
};

void GameOverMenu::update()  {};
void GameOverMenu::render(int dist, int money, int life, char* name) { 
    mvprintw(1, 1, "GAME OVER: HAI PERSO!");
    // Print menu items
    for (int i = 0; i < numGameOverItems; ++i) {
        if (i == getSelectedItem()) {
            attron(A_REVERSE); // Highlight the selected item
        }
        mvprintw(1 + i + 1, 1, gameOverItems[i]);
        attroff(A_REVERSE);
    }
    renderPrompt(getNumItems() + 4, 1);
    renderStats();
};