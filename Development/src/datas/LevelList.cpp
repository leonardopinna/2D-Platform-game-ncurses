#include "LevelList.hpp"

vector<vector<int>> level0 = {
    {10, 1},
    {10, 2},
    {10, 3},
    {10, 4},
    {10, 5},
    {10, 6},
    {10, 7},
    {10, 8},
};


vector<vector<int>> generateZigZag() {

    vector<vector<int>> vect;
    for (int x = 3; x <= WIDTH - 3; x += 3) {
        for (int y = 1; y <= HEIGHT - 2; y += 1) {
            if ((x + y) % 2 == 0) vect.push_back({x, y});
        }
    }
    return vect; 
};

vector<vector<int>> generateRect() {
    vector<vector<int>> vect;
    int startX = 3; 
    int startY = 1; 
    int endY = HEIGHT - 2;
    int endX = WIDTH - 4;

    for (int x = startX; x <= endX; x++) {  
        vect.push_back({x, startY}); 
        vect.push_back({x, endY}); 
    }
    for (int y = startY + 1; y <= endY - 1; y++) {
        vect.push_back({startX, y}); 
        vect.push_back({endX, y});
    }
    return vect; 
}

vector<vector<int>> generateSnake() {
    vector<vector<int>> vect;
    int startX = 3; 
    int startY = 1; 
    int endY = HEIGHT - 2;
    int endX = WIDTH - 3;
    int x = startX;
    int y = startY;  
    while (x <= endX) {
        if (y <= endY) {
            vect.push_back({x, y});
            y++;
        } else {
            y = startY;  
        }
        x++;
    }
    return vect; 
}

vector<vector<int>> generateSnakeInv() {
    vector<vector<int>> vect;
    int startX = 3; 
    int startY = 1; 
    int endY = HEIGHT - 2;
    int endX = WIDTH - 3;
    int x = startX;
    int y = endY;  
    while (x <= endX) {
        if (y >= startY) {
            vect.push_back({x, y});
            y--;
        } else {
            y = endY;  
        }
        x++;
    }
    return vect; 
}

vector<vector<int>> generateVertical() {
    vector<vector<int>> vect;
    for (int x = 4; x <= WIDTH - 5; x += 2) {
        for (int y = 0; y <= HEIGHT-2; y++) {
            vect.push_back({x, y});
        }
    }
    return vect;
}

vector<vector<int>> generateBoxes() {
    vector<vector<int>> vect;
    int startX = 5; 
    int startY = 1; 
    int endX = WIDTH - 5; 
    int endY = HEIGHT - 2; 

    while (startX < endX && startY < endY) {
        for (int x = startX; x <= endX; x++) {  
            vect.push_back({x, startY}); 
            vect.push_back({x, endY}); 
        }
        for (int y = startY + 1; y <= endY - 1; y++) {
            vect.push_back({startX, y}); 
            vect.push_back({endX, y});
        }
        startX += 3;
        startY += 2; 
        endX -= 3;
        endY -= 2;
    }
    return vect; 
};

vector<vector<int>> generateSuperBlock() {
    vector<vector<int>> vect;
    for (int x = WIDTH/2-4; x <= WIDTH/2+3; x++) {
        for (int y = 0; y <= HEIGHT-2; y++) {
            vect.push_back({x, y});
        }
    }
    return vect;
}

vector<vector<vector<int>>> availableLevels = {
    generateBoxes(),
    generateZigZag(),
    generateRect(),
    generateVertical(),
    generateSnake(),
    generateSnakeInv(),
    generateSuperBlock(),
    {} 
}; 
