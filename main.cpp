#include <iostream>
#include <cstdlib> // For the exit() function
#include "GAME.h"

int main() {
    int n, k, strategyNum;
    unsigned int seed;

    // Print exact prompts as the automated tester expects
    std::cout << "Enter n: \n";
    if (!(std::cin >> n)) { std::cout << "invalid input\n"; exit(1); }

    std::cout << "Enter k: \n";
    if (!(std::cin >> k)) { std::cout << "invalid input\n"; exit(1); }

    std::cout << "Enter strategy_num: \n";
    if (!(std::cin >> strategyNum)) { std::cout << "invalid input\n"; exit(1); }

    std::cout << "Enter seed: \n";
    if (!(std::cin >> seed)) { std::cout << "invalid input\n"; exit(1); }

    // Input validation
    if (n <= 0 || k <= 0 || n > k || (strategyNum != 1 && strategyNum != 2)) {
        std::cout << "invalid input\n";
        exit(1);
    }

    Game bullsAndCows(n, k, strategyNum, seed);
    bullsAndCows.play();

    return 0;
}