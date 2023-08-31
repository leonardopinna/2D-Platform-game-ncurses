#include "Menu.hpp"

Menu::Menu(string title, vector<string> menu, vector<GameState> link, string msg, PlayerManager * p) : title(title), menu(menu), link(link), message(msg), playerManager(p) {
    this->selectedItem = 0;   
};

// getters
string Menu::getTitle() {
    return this->title;
};
string Menu::getMessage() {
    return this->message;
}
int Menu::getTimer() {
    return this->timer;
}
int Menu::getSelectedItem() {
    return this->selectedItem;
}

GameState Menu::getState() {
    return this->state; 
}
PlayerManager * Menu::getPlayerManager() {
    return this->playerManager; 
}

// setters
void Menu::setTimer(int x) {
    this->timer = x;
}
void Menu::setSelectedItem(int x) {
    this->selectedItem = x;
}
void Menu::setState(GameState g) {
    if (this->state != g) {
        this->selectedItem = 0;
    } 
    this->state = g; 
}
void Menu::setPlayerManager(PlayerManager * p) {
    this->playerManager = p;
}
void Menu::decreaseTimer() {
    this->timer--;
}

// actions
void Menu::selectUp() {
    this->selectedItem = (this->selectedItem - 1 +  menu.size()) %  menu.size(); 
}

void Menu::selectDown() {
    this->selectedItem = (this->selectedItem + 1) % menu.size();
}

void Menu::selectButton() {
    this->state = link[selectedItem];
}
GameState Menu::run(GameState gs) {

    this->state = gs; 

    handleInput();
     
    render();
        
    return this->state;  
}

// input handling
void Menu::handleInput() {
    switch (getch()) {
    case 'w':
        selectUp();
        break;
    case 's':
        selectDown();
        break;
    case 'l': // Enter key
        selectButton(); 
    default: 
        break;
    };
}

// rendering 
void Menu::render() {
    mvprintw(1, 1, title.c_str());
    renderMenu();
    renderPrompt(this->menu.size() + 3, 1);
    if (timer > 0) {
        mvprintw(3, statsDistance, message.c_str());
        timer--;
    } 
};

void Menu::renderMenu() {
    for (int i = 0; i < this->menu.size(); ++i) {
        if (i == this->selectedItem) {
            attron(A_REVERSE); // Highlight the selected item
        }
        mvprintw(1 + i + 1, 1, this->menu[i].c_str());
        attroff(A_REVERSE);
    }
};

void Menu::renderPrompt(int y, int x) {   
    mvprintw(y, x, "'w' : Muovi verso l'alto");
    mvprintw(y + 1, x, "'s' : Muovi verso il basso");
    mvprintw(y + 2, x, "'l' : Seleziona");
};

// void Menu::renderPlayPrompt(int y, int x) {
//     mvprintw(y + 0, x, "'w' : Muovi verso l'alto");
//     mvprintw(y + 1, x, "'s' : Muovi verso il basso");
//     mvprintw(y + 2, x, "'a' : Muovi verso sinistra");
//     mvprintw(y + 3, x, "'d' : Muovi verso destra");
//     mvprintw(y + 4, x, "'l' : Spara");
//     mvprintw(y + 5, x, "'q' : Termina partita");
// }

// void Menu::renderStats() {};

// void Menu::renderGameStats(int dist, int money, int life, string name) {
//     mvprintw(2, dist, "MONETE    : %d", money);
//     mvprintw(4, dist, "VITA      : %d", life);
//     mvprintw(6, dist, "ARMA      : %s", name);
// }