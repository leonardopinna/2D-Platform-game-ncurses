#include "Player.cpp"
#include <fstream>
#include <iostream>
#include "GameData.cpp"

using namespace std;

class Market {

    private: 
        int H;
        int W;

    public: 
        Market() {};

        void saveGame() {
            std::ofstream outputFile;
            outputFile.open("save.txt");

            if (outputFile.is_open()) {
                // Write data to the file
                int score = 100;
                int level = 5;
                std::string playerName = "John Doe";

                outputFile << "Score: " << score << std::endl;
                outputFile << "Level: " << level << std::endl;
                outputFile << "Player Name: " << playerName << std::endl;

                // Close the file
                outputFile.close();

                cout << "Game saved successfully!" << std::endl;
            } else {
                cout << "Error opening the file!" << std::endl;
            }
        };

        void buyWeapon() {
            // Find the selected/highlighted weapon
            // If enough money, isBought(true) for that weapon
        };

        void selectWeapon() {
            // player.bullet = selectedWeapon;
        }

        void loadGame() {
            std::ifstream inputFile;
            inputFile.open("save.txt");

            if (inputFile.is_open()) {
                // Variables to store the loaded data
                int score;
                int level;
                std::string playerName;

                // Read data from the file
                string line;
                while (getline(inputFile, line)) {
                    // Assuming the file format is "Label: Value"
                    size_t colonPos = line.find(':');
                    if (colonPos != string::npos) {
                        string label = line.substr(0, colonPos);
                        string valueStr = line.substr(colonPos + 1);
                        int value = stoi(valueStr);

                        if (label == "Score") {
                            score = value;
                        } else if (label == "Level") {
                            level = value;
                        } else if (label == "Player Name") {
                            playerName = valueStr;
                        }
                    }
                }

                // Close the file
                inputFile.close();

                // Display the loaded data
                cout << "Score: " << score << endl;
                cout << "Level: " << level << endl;
                cout << "Player Name: " << playerName << endl;
            } else {
                cout << "Error opening the file!" << endl;
            }
        }

        void startGame() {
            
        };
};