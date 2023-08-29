#include "Game.hpp"

using namespace std;

Game::Game() {
    playerManager = new PlayerManager();
    // marketManager = new MarketManager();
    win = newwin(HEIGHT, WIDTH, 0, 0);

    char* marketItems[] = {
        "Aumenta Vita Max",
    };

    levelManager = new LevelManager(win, playerManager);
    mainMenu = new MainMenu(mainMenuItems, numMainMenuItems); 
    homeMenu = new HomeMenu(homeItems, numHomeItems, playerManager); 
    marketMenu = new MarketMenu(marketItems, playerWeapons.size() + 2, playerManager); 
    gameOverMenu = new GameOverMenu(gameOverItems, numGameOverItems); 

    currentState = GameState::MainMenu;
       
};

void Game::run() {
    initilizeScreen();
    while (running) {

        clear(); 
        wclear(win); 

        switch (currentState) {
            case GameState::MainMenu:
                currentState = mainMenu->run(currentState, 0, playerManager->getMoney(), playerManager->getMaxLife(), playerManager->getWeapon()->getName());
                break;

            case GameState::Market:
                currentState = marketMenu->run(currentState, statsDistance,  playerManager->getMoney(), playerManager->getMaxLife(), playerManager->getWeapon()->getName());
                break;

            case GameState::Home:
                currentState = homeMenu->run(currentState, statsDistance, playerManager->getMoney(), playerManager->getMaxLife(), playerManager->getWeapon()->getName()); 
                break;

            case GameState::Playing:
                currentState = levelManager->run(currentState, statsDistance, playerManager->getMoney(), playerManager->getMaxLife(), playerManager->getWeapon()->getName());
                levelManager->draw(win);   
                break;

            case GameState::GameOver:
                levelManager->gameStarted = false; 
                currentState = gameOverMenu->run(currentState, statsDistance, playerManager->getMoney(), playerManager->getMaxLife(), playerManager->getWeapon()->getName()); 
                break;
            case GameState::LoadGame:
                this->loadGame();
                break;
            case GameState::SaveGame:
                this->saveGame(); 
                break;
            case GameState::ExitGame:
                this->stopGame();
                break;

            default:
                break;
        } 

        // DEBUGGING PRINTING
        mvprintw(HEIGHT + 8, 1, "Game started: %d", levelManager->gameStarted);
        mvprintw(HEIGHT + 9, 1, "LevelVectorSize: %d", levelManager->levelVector.size());
         
        wrefresh(win);
        refresh();

        napms(1000/30);
    }

    endwin();

}

void Game::loadGame(){
    ifstream inputFile;
    inputFile.open("saveFile.txt");
    if (!inputFile) {
        mainMenu->setLoadMessageTimer(100);
        currentState = GameState::MainMenu;
    } else {
        string line;
        getline(inputFile, line);
        playerManager->setMoney(stoi(line));
        getline(inputFile, line);
        playerManager->setMaxLife(stoi(line));
        int i = 0;
        while (i < playerWeapons.size()) {
            getline(inputFile, line);
            playerWeapons[i].setIsBought(line[0] - '0');
            playerWeapons[i].setEquipped(line[2] - '0');
            if (playerWeapons[i].isEquipped()) {
                playerManager->setWeapon(&playerWeapons[i]);   
            };
            i++;
        }   
        currentState = GameState::Home; 
    }
    inputFile.close();
};

void Game::saveGame(){
    ofstream outputFile;
    outputFile.open("saveFile.txt"); 
    outputFile << playerManager->getMoney() << endl;
    outputFile << playerManager->getMaxLife() << endl;
    for (int i = 0; i < playerWeapons.size(); i++) {
        outputFile << playerWeapons[i].isBought() << ":" << playerWeapons[i].isEquipped() << endl;
    }
    outputFile.close();
    homeMenu->setSaveMessageTimer(100);

    currentState = GameState::Home;
};

void Game::stopGame() {
    running = false;
}

// TO DO: METTERE IN LEVEL CLASS


void Game::initilizeScreen() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    this->win = newwin(HEIGHT, WIDTH, 0, 0);

    keypad(win, true);

    running = true;
};



