#ifndef MARKET_MENU_HPP
#define MARKET_MENU_HPP

#include "Menu.hpp"

class MarketMenu : public Menu {
    private: 
         
    public:  
        MarketMenu(char* menu[], int n, PlayerManager * playerManager) : Menu(menu, n) {
            this->setPlayerManager(playerManager); 
        };

        void handleInput() override {
            switch (getch()) {
                case 'w':
                    selectUp();
                    break;
                case 's':
                    selectDown();
                    break;
                case 'l': // Enter key
                    // Handle weapon buy process
                    if (getSelectedItem() == playerWeapons.size() + 1) {
                        setState(GameState::Home);
                    } else if (getSelectedItem() == 0) {
                        if (getPlayerManager()->canBuy(getPlayerManager()->getMoney(), marketLifeCost)) {
                            getPlayerManager()->increaseMaxLife(marketLifeAmount);
                            getPlayerManager()->removeMoney(marketLifeCost);
                        }
                    }else {
                        if (playerWeapons[getSelectedItem() - 1].isBought()) {
                            getPlayerManager()->setWeapon(&playerWeapons[getSelectedItem() - 1]);
                        } else {
                            if (getPlayerManager()->canBuy(getPlayerManager()->getMoney(), playerWeapons[getSelectedItem() - 1].getCost())) {
                                getPlayerManager()->removeMoney(playerWeapons[getSelectedItem() - 1].getCost());
                                getPlayerManager()->unlockWeapon(&playerWeapons[getSelectedItem() - 1]);
                            }
                        }
                    }
            
                    break;
            }
        };

        void update() {};

        void render(int x, int money, int life, char* name) override {
            mvprintw(1, 1, "COMPRA ARMI O VITA");          

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
                    mvprintw(i + marketVerticalOffSet, 1, "%s", playerWeapons[i-1].getName());
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
            }
            renderBasePrompt(playerWeapons.size() + 5, 1);
            mvprintw(2, statsDistance, "MONETE    : %d", getPlayerManager()->getMoney());
            mvprintw(4, statsDistance, "VITA MAX  : %d", getPlayerManager()->getMaxLife());
            mvprintw(6, statsDistance, "ARMA      : %s", getPlayerManager()->getWeapon()->getName());
        };

};

#endif
