#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <utility>
#include "IStrategy.h"

class Game {
public:
    // Constructor that receives initial data
    Game(int n, int k, int strategyNum, unsigned int seed);

    // Destructor to free the strategy memory
    ~Game();

    // Run the game loop
    void play();

private:
    int n;
    int k;
    unsigned int seed;
    std::string secret;
    IStrategy* player2; // Pointer to the chosen strategy

    // Internal helper functions
    std::vector<std::string> generateAllValidOptions() const;
    void generateOptionsHelper(std::string& current, std::vector<bool>& used, std::vector<std::string>& options) const;
    void chooseSecretNumber();
    std::pair<int, int> getFeedback(const std::string& guess) const;
};

#endif // GAME_H