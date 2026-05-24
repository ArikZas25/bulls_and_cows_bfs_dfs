#include <iostream>
#include <string>
#include <vector>
#include "StrategyBFS.h"
#include "StrategyDFS.h"

// The Game Master needs its own function to calculate the real feedback
// to give to the strategies.
std::pair<int, int> getRealFeedback(const std::string& guess, const std::string& secret) {
    int bulls = 0, cows = 0;
    int n = guess.length();
    for (int i = 0; i < n; ++i) {
        if (guess[i] == secret[i]) {
            bulls++;
        }
        else if (secret.find(guess[i]) != std::string::npos) {
            cows++;
        }
    }
    return { bulls, cows };
}

// A generic function that can play the game with ANY strategy
void playGame(IStrategy* strategy, const std::string& secret, const std::string& strategyName) {
    std::cout << "\n--- Playing with " << strategyName << " ---" << std::endl;
    std::cout << "Target Secret: " << secret << std::endl;

    int turns = 0;
    while (!strategy->isFinished()) {
        turns++;

        // 1. Ask strategy for its guess
        std::string guess = strategy->getNextGuess();

        // 2. Game master calculates the real feedback
        auto feedback = getRealFeedback(guess, secret);
        int bulls = feedback.first;
        int cows = feedback.second;

        std::cout << "Turn " << turns << ": Guess = " << guess
            << " -> Bulls: " << bulls << ", Cows: " << cows << std::endl;

        // 3. Give feedback back to the strategy
        strategy->handleFeedback(bulls, cows);

        // Safety break just in case of infinite loops during development
        if (turns > 30) {
            std::cout << "Too many turns! Stopping." << std::endl;
            break;
        }
    }

    if (strategy->isFinished()) {
        std::cout << ">>> " << strategyName << " WON in " << turns << " turns! <<<" << std::endl;
    }
}

int main() {
    int n, k;
    std::string secret;

    std::cout << "=== Bulls and Cows AI Tester ===" << std::endl;

    // Get the number of digits (n) and the range of digits (k)
    std::cout << "Enter n (number of digits): ";
    std::cin >> n;

    std::cout << "Enter k (range of digits): ";
    std::cin >> k;

    // Get the secret number
    std::cout << "Enter the secret number (must be " << n << " digits long): ";
    std::cin >> secret;

    // Basic validation: Does the secret number length match n?
    if (secret.length() != (size_t)n) {
        std::cerr << "Error: The secret number length does not match n" << std::endl;
        return 1; // Exit with error
    }

    std::cout << "\nTarget Secret: " << secret << std::endl;

    // --- Run BFS Algorithm ---
    IStrategy* bfs = new StrategyBFS(n, k);
    playGame(bfs, secret, "BFS Strategy");
    delete bfs; // Mandatory: Free dynamically allocated memory!

    // --- Run DFS Algorithm ---
    IStrategy* dfs = new StrategyDFS(n, k);
    playGame(dfs, secret, "DFS Strategy");
    delete dfs; // Mandatory: Free dynamically allocated memory!

    std::cout << "\nAll tests completed successfully." << std::endl;
    return 0;
}