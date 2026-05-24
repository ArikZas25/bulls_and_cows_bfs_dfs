#include <iostream>
#include <cstdlib> // For the exit() function
#include "Game.h"

int main() {
    int n, k, strategyNum;
    unsigned int seed;

    // Read the 4 parameters in a line (or separate lines)
    if (!(std::cin >> n >> k >> strategyNum >> seed)) {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }

    // Input validation checks:
    // 1. n and k must be positive
    // 2. n cannot be greater than k (since we assume unique digits)
    // 3. Strategy must be 1 or 2
    if (n <= 0 || k <= 0 || n > k || (strategyNum != 1 && strategyNum != 2)) {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }

    // Create an instance of the game (the class handles freeing the strategy in its Destructor)
    Game bullsAndCows(n, k, strategyNum, seed);

    // Run the game
    bullsAndCows.play();

    return 0;
}