
#include "Game.hpp"

int main() {

    Game* game = new Game();
    game->run();
    delete game;

    return 0;
    
}

// initialize player
// Player player = Player(0, '&');
// vector<Bullet> playerBulletVector; 
// vector<Bullet> enemyBulletVector; 
// vector<Enemy> enemyVector;
// vector<Wall> wallVector;
// vector<Door> doorVector;
// vector<Level> levelVector;

// int selectedItem = 0;

// bool gameStarted = false;

// int center_y;
// int center_x;


// GameState currentState = GameState::MainMenu;

// template <typename T>
// bool outOfBounds(T& t) {
//     return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
// }

// template <typename T1, typename T2>
// bool collision(T1& a, T2& b) {
//     return a.getX() == b.getX() && a.getY() == b.getY();
// }

// void initializeGame();
// void gameOver();


// int oldmain() {
//         // Initialize ncurses
//         initscr();
//         cbreak();
//         noecho();
//         curs_set(0);
//         keypad(stdscr, true);
//         nodelay(stdscr, true);

//         // Create a 30x30 window
//         refresh();
//         WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);
//         keypad(win, TRUE);
//         wrefresh(win);

//         auto startTime = std::chrono::steady_clock::now();
//         const double bulletUpdateTime = 0.1; // Bullet update interval in seconds
//         double timeSinceLastBulletUpdate = 0.0;


//         // Game loop
//         while (true) {
         
//             // Calculate time elapsed since last iteration
//             auto currentTime = std::chrono::steady_clock::now();
//             std::chrono::duration<double> elapsedTime = currentTime - startTime;
//             startTime = currentTime;

//             // Update bullet and enemy movement based on time elapsed
//             timeSinceLastBulletUpdate += elapsedTime.count();
//             while (timeSinceLastBulletUpdate >= bulletUpdateTime) {
//                 for (auto it = playerBulletVector.begin() ; it != playerBulletVector.end(); ) {
//                     it->move();
//                     if (outOfBounds(*it) || it->getMaxDistance()==0) {
//                         it = playerBulletVector.erase(it);
//                     } else {
//                         ++it;
//                     }
//                 }
//                 for (auto it = enemyBulletVector.begin() ; it != enemyBulletVector.end(); ) {
//                     it->move();
//                     if (outOfBounds(*it) || it->getMaxDistance()==0) {
//                         it = enemyBulletVector.erase(it);
//                     } else {
//                         ++it;
//                     }
//                 }
//                 for (auto it = enemyVector.begin() ; it != enemyVector.end(); it++) {
//                     it->move();
//                     if (rand() % 10 == 0) enemyBulletVector.push_back(it->shoot());
//                 }

//                 timeSinceLastBulletUpdate -= bulletUpdateTime;
//             }

//             // Check collision of elements
//             // Enemy bullet - Player collision
//             for (auto b = enemyBulletVector.begin() ; b != enemyBulletVector.end(); ) {
//                 bool collided = false;
//                 if (collision(*b, player)) {
//                     player.reduceLife(b->getDamage());
//                     collided = true;
//                 }
//                 if (collided) {
//                     b = enemyBulletVector.erase(b);
//                 } else {
//                     ++b;
//                 }
//             }
//             // Enemy - Player collision
//             for (auto b = enemyVector.begin() ; b != enemyVector.end(); b++) {
//                 if (collision(*b, player)) {
//                     player.reduceLife(b->getBullet().getDamage());                         
//                 }
//             }
//             // Player bullet - Enemies collision
//             for (auto b = playerBulletVector.begin() ; b != playerBulletVector.end(); ) {
//                 bool collided = false;
//                 for (auto enemyIt = enemyVector.begin() ; enemyIt != enemyVector.end(); ) {
//                     // collision check
//                     if (collision(*b, *enemyIt)) {
//                         enemyIt->reduceLife(b->getDamage());
//                         // if life to zero, delete enemy
//                         if (enemyIt->getLife() <= 0) {
//                             enemyIt = enemyVector.erase(enemyIt);
//                             player.addMoney(enemyIt->getMoney());
//                         } 
//                         collided = true;
//                         break;
//                     } else {
//                         ++enemyIt;
//                     }
//                 }   
//                 if (collided) {
//                     b = playerBulletVector.erase(b);
//                 } else {
//                     ++b;
//                 }
//             }

//             // Gameover trigger
//             if (player.getLife() <= 0) {
//                 gameOver();
//             }


//             switch (currentState) {
//                 case GameState::Market:

//                     clear(); 
//                     mvprintw(1, 1, "BENVENUTO NEL MERCATO, COMPRA ARMI O ACCESSORI!");
//                     // Print menu items
//                     for (int i = 0; i < numMarketItems; ++i) {
//                         if (i == selectedItem) {
//                             attron(A_REVERSE); // Highlight the selected item
//                         }
//                         mvprintw(i + 2, 1, marketItems[i]);
//                         attroff(A_REVERSE);
//                     }
                    
//                     // Get user input
//                     switch (getch()) {
//                         case 'w':
//                             selectedItem = (selectedItem - 1 + numMarketItems) % numMarketItems;
//                             break;
//                         case 's':
//                             selectedItem = (selectedItem + 1) % numMarketItems;
//                             break;
//                         case 10: // Enter key
//                             // Handle menu item selection
//                             if (selectedItem == 0) {
//                                 // Nuova partita
//                                 currentState = GameState::Playing;
//                             } else if (selectedItem == 1) {
//                                 // Compra arma
//                                 selectedItem = 0;
//                                 currentState = GameState::WeaponMenu;
//                             }  else if (selectedItem == 2) {
//                                 // Salva
                                
//                             }  else if (selectedItem == 3) {
//                                 // Esci
//                                 endwin(); // Cleanup ncurses
//                                 return 0;
//                             }
//                             break;
//                     }
                    
//                     break;

//                 case GameState::WeaponMenu:
//                     clear(); 
//                     // Print menu items
//                     mvprintw(1, 1, "SELEZIONA O COMPRA ARMA");
//                     for (int i = 0; i < numWeapons + 1; ++i) {
//                         if (i == selectedItem) {
//                             attron(A_REVERSE); // Highlight the selected item
//                         }
//                         if (!(i == numWeapons)) {
//                             mvprintw(i + 2, 1, "%s", playerWeapons[i].getName());
//                             mvprintw(i + 2, weaponsCostDistance + 5, "%c%", playerWeapons[i].getSymbol());
//                             if (!playerWeapons[i].isBought()) {
//                                 mvprintw(i + 2, weaponsCostDistance, "%d%", playerWeapons[i].getCost());
//                             }
//                         } else {
//                             mvprintw(numWeapons + 2, 1, "Torna al Mercato");
//                         }
//                         attroff(A_REVERSE);
//                     }
                    
//                     // Get user input
//                     switch (getch()) {
//                         case 'w':
//                             selectedItem = (selectedItem - 1 + numWeapons + 1) % (numWeapons + 1);
//                             break;
//                         case 's':
//                             selectedItem = (selectedItem + 1) % (numWeapons + 1);
//                             break;
//                         case 10: // Enter key
//                             // Handle weapon buy process
//                             if (selectedItem == numWeapons) {
//                                 selectedItem = 0;
//                                 currentState = GameState::Market;
//                             } else {
//                                 if (player.getMoney() >= playerWeapons[selectedItem].getCost()) {
//                                 player.removeMoney(playerWeapons[selectedItem].getCost());
//                                 player.setBullet(playerWeapons[selectedItem]);
//                                 playerWeapons[selectedItem].setIsBought(true);
//                                 }
//                             }
                            
//                             break;
//                     }

//                     break;

//                 case GameState::MainMenu:

//                     clear();
                    
//                     // Print menu items
//                     mvprintw(1, 1, "WARRIOR GAME by Leonardo Pinna");
//                     for (int i = 0; i < numMainMenuItems; ++i) {
//                         if (i == selectedItem) {
//                             attron(A_REVERSE); // Highlight the selected item
//                         }
//                         mvprintw(1 + i + 1, 1, mainMenuItems[i]);
//                         attroff(A_REVERSE);
//                     }
                    
//                     // Get user input
//                     switch (getch()) {
//                         case 'w':
//                             selectedItem = (selectedItem - 1 + numMainMenuItems) % numMainMenuItems;
//                             break;
//                         case 's':
//                             selectedItem = (selectedItem + 1) % numMainMenuItems;
//                             break;
//                         case 10: // Enter key
//                             // Handle menu item selection
//                             if (selectedItem == 0) {
//                                 // Nuova Partita
//                                 gameStarted = false;
//                                 currentState = GameState::Market;
//                             } else if (selectedItem == 1) {
//                                 // Carica Partita
//                             } else if (selectedItem == 2) {
//                                 // Esci
//                                 endwin(); // Cleanup ncurses
//                                 return 0;
//                             }
//                             break;
//                     }

//                     refresh();
//                     wrefresh(win);
                    
//                     break;

//                 case GameState::Playing:

//                     initializeGame();

//                     // Handle user input
//                     switch (getch()) {
//                         case 'w':
//                             if (player.getY() > 1) player.moveUp();
//                             break;

//                         case 's':
//                             if (player.getY() < HEIGHT - 2) player.moveDown();
//                             break;

//                         case 'a':
//                             if (player.getX() > 1) player.moveLeft();
//                             break;

//                         case 'd':
//                             if (player.getX() < WIDTH - 2) player.moveRight();
//                             break;

//                         case 'l':
//                             playerBulletVector.push_back(player.shoot());
//                             break;

//                         case 'q':
//                         case 'Q':
//                             currentState = GameState::MainMenu;
//                             gameStarted = false;
//                             break;

//                         default:
//                             // Handle other keys or do nothing
//                             break;
//                     }

//                     // DRAW THE GAME
//                     clear();
//                     wclear(win);


//                     box(win, 0, 0);

//                     int win_height, win_width;
//                     getmaxyx(win, win_height, win_width);

//                     // Calculate the center position
//                     center_y = win_height / 2;
//                     center_x = win_width / 2;

//                     // Draw the '&' in the center of the window
//                     mvwaddch(win, player.getY(), player.getX(), '&');
//                     for (Bullet b : playerBulletVector) {
//                         mvwaddch(win, b.getY(), b.getX(), b.getSymbol());
//                     }
//                     for (Bullet b : enemyBulletVector) {
//                         mvwaddch(win, b.getY(), b.getX(), b.getSymbol());
//                     }
//                     for (Enemy e : enemyVector) {
//                         mvwaddch(win, e.getY(), e.getX(), e.getSymbol());
//                     }
//                     for (Wall w : wallVector) {
//                         mvwaddch(win, w.getY(), w.getX(), w.getSymbol());
//                     }
//                     for (Door d : doorVector) {
//                         mvwaddch(win, d.getY(), d.getX(), d.getSymbol());
//                     }
//                     mvprintw(1, WIDTH + 3, "VITA RESIDUA : %d", player.getLife());
//                     mvprintw(3, WIDTH + 3, "MONETE : %d", player.getMoney());

//                     break;

            
//                 case GameState::GameOver:
//                     // Handle game over logic

//                     mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 5, "GAME OVER"); 
//                     mvprintw(HEIGHT + 2, 1, "GAME OVER: HAI PERSO!");
//                     // Print menu items
//                     for (int i = 0; i < numGameOverItems; ++i) {
//                         if (i == selectedItem) {
//                             attron(A_REVERSE); // Highlight the selected item
//                         }
//                         mvprintw(HEIGHT + 2 + i + 1, 1, gameOverItems[i]);
//                         attroff(A_REVERSE);
//                     }
                    
//                     // Get user input
//                     switch (getch()) {
//                         case 'w':
//                             selectedItem = (selectedItem - 1 + numGameOverItems) % numGameOverItems;
//                             break;
//                         case 's':
//                             selectedItem = (selectedItem + 1) % numGameOverItems;
//                             break;
//                         case 10: // Enter key
//                             // Handle menu item selection
//                             if (selectedItem == 0) {
//                                 // Gioca
//                                 currentState = GameState::Playing;
//                             } else if (selectedItem == 1) {
//                                 // Mercato
//                                 selectedItem = 0;
//                                 currentState = GameState::Market;
//                             } else if (selectedItem == 2) {
//                                 // Esci
//                                 endwin(); // Cleanup ncurses
//                                 return 0;
//                             }
//                             break;
//                     }

//                     break;
//             }
                       
//             refresh();
//             wrefresh(win);
//             // Add a delay to control the loop speed
//             napms(1000/60); 

//         }

//         // Clean up ncurses
//         endwin();
//         return 0;
//     }

// void initializeGame() {
//     if (!gameStarted) {
//         selectedItem = 0;
//         wallVector.clear();
//         player.setX(5);
//         player.setY(5);
 

//         // Generate enemies
//         for (int i = 0; i < 3; i++) {
//             enemyVector.push_back(goblin);
//             enemyVector[i].setX(rand() % WIDTH / 2 + WIDTH / 2 - 1);
//             enemyVector[i].setY(rand() % (HEIGHT - 2) + 1);
//         }

//         // Generates walls 
//         for (int i = 0; i < 3; i++) {
//             wallVector.push_back(baseWall);
//             wallVector[i].setX(rand() % WIDTH / 2 + WIDTH / 2 - 1);
//             wallVector[i].setY(rand() % (HEIGHT - 2) + 1);
//         }

//         // Generate doors
//         doorVector.push_back(door);
//         doorVector[0].setX(WIDTH - 2);
//         doorVector[0].setY(rand() % (HEIGHT - 2) + 1);

//         gameStarted = true;
//     }
// }

// void gameOver() {
//     enemyVector.clear();
//     enemyBulletVector.clear();
//     playerBulletVector.clear();

//     player.setMaxLife();

//     currentState = GameState::GameOver;
//     gameStarted = false;
// }