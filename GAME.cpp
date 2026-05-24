#include "GAME.h"
#include "StrategyBFS.h"
#include "StrategyDFS.h"
#include <iostream>
#include <random>

Game::Game(int n, int k, int strategyNum, unsigned int seed) : n(n), k(k), seed(seed), player2(nullptr) {
    if (strategyNum == 1) {
        player2 = new StrategyDFS(n, k);
    }
    else {
        player2 = new StrategyBFS(n, k);
    }
    chooseSecretNumber();
}

Game::~Game() {
    if (player2 != nullptr) {
        delete player2;
    }
}

void Game::generateOptionsHelper(std::string& current, std::vector<bool>& used, std::vector<std::string>& options) const {
    if ((int)current.size() == n) {
        options.push_back(current);
        return;
    }
    for (int i = 0; i < k; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back('1' + i); // Digits from 1 to k
            generateOptionsHelper(current, used, options);
            current.pop_back();
            used[i] = false;
        }
    }
}

std::vector<std::string> Game::generateAllValidOptions() const {
    std::vector<std::string> options;
    std::string current;
    std::vector<bool> used(k, false);
    generateOptionsHelper(current, used, options);
    return options;
}

void Game::chooseSecretNumber() {
    std::vector<std::string> options = generateAllValidOptions();
    int num_options = options.size();
    if (num_options == 0) {
        std::cerr << "Error: No valid options to choose from!" << std::endl;
        exit(1);
    }
    std::mt19937 rng(seed);
    int rand_index = rng() % num_options;
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
    return std::make_pair(bulls, cows);
}

void Game::play() {
    int rounds = 0;
    std::cout << "\n"; // Empty line as expected by the tester

    while (!player2->isFinished()) {
        rounds++;
        std::string guess = player2->getNextGuess();

        std::pair<int, int> feedback = getFeedback(guess);
        int bulls = feedback.first;
        int cows = feedback.second;

        // Print in the exact format required by the tester
        std::cout << "Round " << rounds << ": Guess: " << guess
            << ", Feedback: (" << bulls << ", " << cows << ")\n";

        player2->handleFeedback(bulls, cows);

        if (rounds > 5000) { break; }
    }

    // Print summary line
    std::cout << "\nNumber of rounds: " << rounds << "\n";
}