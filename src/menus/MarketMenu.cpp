#include "MarketMenu.hpp" 

MarketMenu::MarketMenu(string title, string msg, PlayerManager * p) : Menu(title, {}, {}, msg, p) {};

void MarketMenu::handleInput() {
    switch (getch()) {
        case 'w':
            this->setSelectedItem((this->getSelectedItem() - 1 + playerWeapons.size() + 2) %  (playerWeapons.size() + 2)); 
            break;

        case 's':
            this->setSelectedItem((this->getSelectedItem() + 1) % (playerWeapons.size() + 2));
            break;

        case 'l': // Enter key
            // Handle weapon buy process
            if (getSelectedItem() == playerWeapons.size() + 1) {
                setState(GameState::Home);
            } else if (getSelectedItem() == 0) {
                if (getPlayerManager()->canBuy(getPlayerManager()->getMoney(), marketLifeCost)) {
                    getPlayerManager()->increaseMaxLife(marketLifeAmount);
                    getPlayerManager()->removeMoney(marketLifeCost);
                } else {
                    setTimer(150);
                }
            }else {
                if (playerWeapons[getSelectedItem() - 1].isBought()) {
                    getPlayerManager()->setWeapon(&playerWeapons[getSelectedItem() - 1]);
                } else {
                    if (getPlayerManager()->canBuy(getPlayerManager()->getMoney(), playerWeapons[getSelectedItem() - 1].getCost())) {
                        getPlayerManager()->removeMoney(playerWeapons[getSelectedItem() - 1].getCost());
                        getPlayerManager()->unlockWeapon(&playerWeapons[getSelectedItem() - 1]);
                    } else {
                        setTimer(messageTime);
                    }
                }
            }
    
            break;
    }
};

GameState MarketMenu::run(GameState gs) {
    this->setState(gs); 
    handleInput(); 
    render();  
    return this->getState();
};

void MarketMenu::render() {
    mvprintw(1, 1, this->getTitle().c_str());          

    for (int i = 0; i < playerWeapons.size() + 2; ++i) {
        if (i == getSelectedItem()) {
            attron(A_REVERSE); // Highlight the selected item
        }
        if (i == 0) {
            mvprintw(marketVerticalOffSet, 1, "Aumenta Vita Max");
            mvprintw(marketVerticalOffSet, marketCostDistance, "%d", marketLifeCost);
            mvprintw(marketVerticalOffSet, marketCostDistance + marketLifeAmountOffset, "+%d", marketLifeAmount);
        } else {
            if (!(i == playerWeapons.size() + 1)) {
                mvprintw(i + marketVerticalOffSet, 1, "%s", playerWeapons[i-1].getName().c_str());
                mvprintw(i + marketVerticalOffSet, marketCostDistance + marketSymbolOffSet, "%c%", playerWeapons[i-1].getSymbol());
                if (!playerWeapons[i-1].isBought()) {
                    mvprintw(i + marketVerticalOffSet, marketCostDistance, "%d%", playerWeapons[i-1].getCost());
                } else {
                    if (playerWeapons[i-1].isEquipped()) {
                        mvprintw(i + marketVerticalOffSet, marketCostDistance, "EQ");
                    }
                }
                
            } else {
                mvprintw(playerWeapons.size() + marketVerticalOffSet + 1, 1, "Torna al Mercato");
            }
        }
        attroff(A_REVERSE);

        mvprintw(2, statsDistance, "MONETE    : %d", getPlayerManager()->getMoney());
        mvprintw(4, statsDistance, "VITA MAX  : %d", getPlayerManager()->getMaxLife());
        mvprintw(6, statsDistance, "ARMA      : %s", getPlayerManager()->getWeapon()->getName().c_str());
        if (getTimer() > 0) {
            mvprintw(8, statsDistance, getMessage().c_str());
            decreaseTimer();
        }
    }    
};

