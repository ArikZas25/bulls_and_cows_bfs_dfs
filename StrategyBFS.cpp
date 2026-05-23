#include "StrategyBFS.h"
#include <algorithm>
#include <cmath>
#include <numeric>

StrategyBFS::StrategyBFS(int n, int k)
    : n(n), k(k), finished(false) {
    // Initialize S with all possible n-digit guesses with digits in range [0, k-1]
    S = generateAllGuesses();
}

std::string StrategyBFS::getNextGuess() {
    // Select the best guess using minimax criteria (minimizes search space depth)
    lastGuess = selectBestGuess();
    return lastGuess;
}

void StrategyBFS::handleFeedback(int bulls, int cows) {
    // If we got n bulls, we found the secret
    if (bulls == n) {
        finished = true;
        return;
    }

    // Filter S: remove all guesses inconsistent with feedback
    filterConsistent(bulls, cows);
}

bool StrategyBFS::isFinished() const {
    return finished;
}

std::set<std::string> StrategyBFS::generateAllGuesses() const {
    std::set<std::string> guesses;

    std::string current_guess;
    current_guess.reserve(n); // Pre-allocate exactly n bytes

    std::vector<bool> used(k + 1, false);

    generateGuessesHelper(current_guess, used, guesses);

    return guesses;
}

void StrategyBFS::generateGuessesHelper(std::string& current_guess, std::vector<bool>& used, std::set<std::string>& guesses) const {
    // Base Case: The guess has reached the required size 'n'
    if (current_guess.length() == static_cast<size_t>(n)) {
        guesses.insert(current_guess);
        return;
    }

    // Recursive Step: Try appending every available digit from 1 to k
    for (int i = 1; i <= k; ++i) {
        if (!used[i]) {
            // 1. Mark digit as used and add to string
            used[i] = true;
            current_guess.push_back(static_cast<char>('0' + i));

            // 2. Recurse to pick the next digit
            generateGuessesHelper(current_guess, used, guesses);

            // 3. Backtrack: remove the digit and mark as unused for the next iteration
            current_guess.pop_back();
            used[i] = false;
        }
    }
}


std::pair<int, int> StrategyBFS::calculateFeedback(const std::string& guess, const std::string& secret) const {
    int bulls = 0;
    int cows = 0;
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

void StrategyBFS::filterConsistent(int bulls, int cows) {
    // Remove all candidates from S that don't produce the same feedback
    std::set<std::string> newS;
    for (const std::string& candidate : S) {
        auto [b, c] = calculateFeedback(lastGuess, candidate);
        if (b == bulls && c == cows) {
            newS.insert(candidate);
        }
    }
    S = newS;
}

int StrategyBFS::calculateSearchSpaceDepth(const std::string& guess) const {
    int maxDepth = 0;
    // For each possible secret in S, calculate cost(guess, secret)
    // cost(guess, secret) = number of remaining candidates after filtering with that feedback
    for (const std::string& secret : S) {
        auto [b, c] = calculateFeedback(guess, secret);

        // Count how many candidates would remain if we got feedback (b, c)
        int count = 0;
        for (const std::string& candidate : S) {
            auto [cb, cc] = calculateFeedback(guess, candidate);
            if (cb == b && cc == c) {
                count++;
            }
        }

        maxDepth = std::max(maxDepth, count);
    }

    return maxDepth;
}

std::string StrategyBFS::selectBestGuess() {
    // Find the guess with minimal search space depth
    // If tie, choose lexicographically smallest
    std::string bestGuess;
    int minDepth = INT_MAX;

    for (const std::string& guess : S) {
        int depth = calculateSearchSpaceDepth(guess);
        // Choose this guess if:
        // 1. It has smaller depth than current best, OR
        // 2. Same depth but lexicographically smaller
        if (depth < minDepth || (depth == minDepth && guess < bestGuess)) {
            minDepth = depth;
            bestGuess = guess;
        }
    }

    return bestGuess;
}