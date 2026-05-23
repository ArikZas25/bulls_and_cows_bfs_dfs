#include "StrategyDFS.h"

StrategyDFS::StrategyDFS(int n, int k) : n(n), k(k), finished(false) {
    std::string current;
    std::vector<bool> used(k + 1, false);
    generateCandidates(current, used);
}

void StrategyDFS::generateCandidates(std::string& current, std::vector<bool>& used) {
    if ((int)current.size() == n) {
        candidates.push_back(current);
        return;
    }
    for (int i = 1; i <= k; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back('0' + i);
            generateCandidates(current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

std::pair<int, int> StrategyDFS::calculateFeedback(const std::string& guess, const std::string& secret) const {
    int bulls = 0, cows = 0;
    for (int i = 0; i < n; ++i) {
        if (guess[i] == secret[i]) bulls++;
        else if (secret.find(guess[i]) != std::string::npos) cows++;
    }
    return { bulls, cows };
}

std::string StrategyDFS::getNextGuess() {
    lastGuess = candidates.front();
    return lastGuess;
}

void StrategyDFS::handleFeedback(int bulls, int cows) {
    if (bulls == n) { finished = true; return; }
    std::vector<std::string> newCandidates;
    for (const std::string& c : candidates) {
        auto [b, cv] = calculateFeedback(lastGuess, c);
        if (b == bulls && cv == cows) newCandidates.push_back(c);
    }
    candidates = newCandidates;
}

bool StrategyDFS::isFinished() const {
    return finished;
}