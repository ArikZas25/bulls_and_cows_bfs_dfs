#include "Game.h"
#include "StrategyBFS.h"
#include "StrategyDFS.h"
#include <iostream>
#include <random>

Game::Game(int n, int k, int strategyNum, unsigned int seed) : n(n), k(k), seed(seed), player2(nullptr) {
    // Initialize the strategy based on user choice (dynamically allocated!)
    if (strategyNum == 1) {
        player2 = new StrategyDFS(n, k); // Assuming 1 is DFS
    }
    else {
        player2 = new StrategyBFS(n, k); // Assuming 2 is BFS
    }

    // Choose the secret number according to the requirements
    chooseSecretNumber();
}

Game::~Game() {
    // Free dynamically allocated memory - mandatory per the assignment!
    if (player2 != nullptr) {
        delete player2;
    }
}

// Recursive function to generate all valid options (unique digits from 0 to k-1)
void Game::generateOptionsHelper(std::string& current, std::vector<bool>& used, std::vector<std::string>& options) const {
    if ((int)current.size() == n) {
        options.push_back(current);
        return;
    }
    for (int i = 0; i < k; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back('0' + i);
            generateOptionsHelper(current, used, options);
            current.pop_back();
            used[i] = false;
        }
    }
}

// Generates all valid options sorted lexicographically
std::vector<std::string> Game::generateAllValidOptions() const {
    std::vector<std::string> options;
    std::string current;
    std::vector<bool> used(k, false);
    generateOptionsHelper(current, used, options);
    return options;
}

void Game::chooseSecretNumber() {
    // 1. Create a lexicographically sorted list S (our recursive function generates it sorted by default)
    std::vector<std::string> options = generateAllValidOptions();

    int num_options = options.size();
    if (num_options == 0) {
        std::cerr << "Error: No valid options to choose from!" << std::endl;
        exit(1);
    }

    // 2. Initialize the random number generator as required in the assignment
    std::mt19937 rng(seed);

    // 3. Choose a random index
    int rand_index = rng() % num_options;

    // 4. Save the secret number
    secret = options[rand_index];
}

std::pair<int, int> Game::getFeedback(const std::string& guess) const {
    int bulls = 0, cows = 0;
    for (int i = 0; i < n; ++i) {
        if (guess[i] == secret[i]) {
            bulls++;
        }
        else if (secret.find(guess[i]) != std::string::npos) {
            cows++;
        }
    }
    return std::make_pair(bulls, cows); // C++11 compatible
}

void Game::play() {
    int rounds = 0;
    // Keep history to print it nicely at the end
    std::vector<std::pair<std::string, std::pair<int, int>>> history;

    while (!player2->isFinished()) {
        rounds++;
        std::string guess = player2->getNextGuess();

        std::pair<int, int> feedback = getFeedback(guess);
        int bulls = feedback.first;
        int cows = feedback.second;

        history.push_back(std::make_pair(guess, feedback));
        player2->handleFeedback(bulls, cows);

        // Protection against an infinite loop
        if (rounds > 100) {
            break;
        }
    }

    // Print output according to the required format
    std::cout << "Rounds: " << rounds << std::endl;
    for (int i = 0; i < (int)history.size(); ++i) {
        std::cout << "Turn " << (i + 1) << ": Guess = " << history[i].first
            << ", Bulls = " << history[i].second.first
            << ", Cows = " << history[i].second.second << std::endl;
    }
}