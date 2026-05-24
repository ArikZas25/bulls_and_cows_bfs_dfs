#include "StrategyDFS.h"

StrategyDFS::StrategyDFS(int n, int k) : n(n), k(k), finished(false) {
    for (int i = 0; i < n; ++i) {
        currentGuess.push_back('1' + i); // Start from the lowest number (e.g. "1234")
    }
}

std::string StrategyDFS::getNextGuess() {
    if (history.empty()) {
        return currentGuess;
    }
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
    history.push_back(std::make_pair(currentGuess, std::make_pair(bulls, cows)));
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
    return std::make_pair(bulls, cows);
}

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

void StrategyDFS::generateNextLexicographicalGuess() {
    do {
        for (int i = n - 1; i >= 0; --i) {
            if (currentGuess[i] - '1' < k - 1) { // Counts up to k
                currentGuess[i]++;
                break;
            }
            else {
                currentGuess[i] = '1';
            }
        }
    } while (!hasUniqueDigits(currentGuess));
}

bool StrategyDFS::hasUniqueDigits(const std::string& str) const {
    std::vector<bool> seen(k, false);
    for (char c : str) {
        int digit = c - '1';
        if (digit < 0 || digit >= k || seen[digit]) return false;
        seen[digit] = true;
    }
    return true;
}