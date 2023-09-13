#ifndef PARAMETER_HPP
#define PARAMETER_HPP

// Level Window Dimensions
const int HEIGHT = 10;
const int WIDTH = 40;

// Game Speed
const double gameSpeed = 0.1;

// Max enemies per type on screen
const int maxEnemiesPerType = 5; 

// Max money bonus per level
const int maxMoneyBonusElementsPerLevel = 5; 

// Starting Level Increment every this maxLife
const int startingLevelIncreaseDelta = 100;

// Message frames before desappearing
const int messageTime = 150;

// Extra life cost and amount
const int marketLifeAmount = 10;
const int marketLifeCost = 10;

// Menu elements distance
const int marketCostDistance = 20;
const int marketVerticalOffSet = 2;
const int marketSymbolOffSet = 8;
const int marketLifeAmountOffset = marketSymbolOffSet - 2;
const int statsDistance = WIDTH + 10;

// In-game money bonus
const int moneyBonus = 5; 

#endif