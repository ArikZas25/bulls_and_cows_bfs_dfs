#include "StrategyDFS.h"

StrategyDFS::StrategyDFS(int n, int k) : n(n), k(k), finished(false) {
    // We don't generate all candidates here! 
    // We just start with the lowest possible valid number (e.g., "0123" for n=4)
    for (int i = 0; i < n; ++i) {
        currentGuess.push_back('0' + i);
    }
}

std::string StrategyDFS::getNextGuess() {
    // If it's the very first guess, return the initial setup
    if (history.empty()) {
        return currentGuess;
    }

    // Otherwise, find the next lexicographically valid guess
    do {
        generateNextLexicographicalGuess();
    } while (!isConsistent(currentGuess));

    return currentGuess;
}

void StrategyDFS::handleFeedback(int bulls, int cows) {
    if (bulls == n) {
        finished = true;
        return;
    }
    // Save the result to our history so we can check future candidates against it
    history.push_back({ currentGuess, {bulls, cows} });
}

bool StrategyDFS::isFinished() const {
    return finished;
}

std::pair<int, int> StrategyDFS::calculateFeedback(const std::string& guess, const std::string& secret) const {
    int bulls = 0, cows = 0;
    for (int i = 0; i < n; ++i) {
        if (guess[i] == secret[i]) bulls++;
        else if (secret.find(guess[i]) != std::string::npos) cows++;
    }
    return { bulls, cows };
}

// Checks if a candidate would give the exact same feedback for all past guesses
bool StrategyDFS::isConsistent(const std::string& candidate) const {
    for (const auto& pastRecord : history) {
        auto simulatedFeedback = calculateFeedback(candidate, pastRecord.first);
        if (simulatedFeedback.first != pastRecord.second.first ||
            simulatedFeedback.second != pastRecord.second.second) {
            return false;
        }
    }
    return true;
}

// Advances the string to the next valid sequence of unique digits (Base-K addition)
void StrategyDFS::generateNextLexicographicalGuess() {
    do {
        // Treat the string like a base-K number and add 1
        for (int i = n - 1; i >= 0; --i) {
            if (currentGuess[i] - '0' < k - 1) {
                currentGuess[i]++;
                break;
            }
            else {
                currentGuess[i] = '0'; // Carry over
            }
        }
    } while (!hasUniqueDigits(currentGuess)); // Skip numbers with repeating digits
}

// Helper to ensure digits don't repeat
bool StrategyDFS::hasUniqueDigits(const std::string& str) const {
    std::vector<bool> seen(k, false);
    for (char c : str) {
        int digit = c - '0';
        if (seen[digit]) return false;
        seen[digit] = true;
    }
    return true;
}