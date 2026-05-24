#ifndef STRATEGY_DFS_H
#define STRATEGY_DFS_H

#include "IStrategy.h"
#include <vector>
#include <string>
#include <utility>

class StrategyDFS : public IStrategy {
public:
    StrategyDFS(int n, int k);
    std::string getNextGuess() override;
    void handleFeedback(int bulls, int cows) override;
    bool isFinished() const override;

private:
    int n, k;
    bool finished;
    std::string currentGuess;

    // Store past guesses and their feedback to verify future candidates
    std::vector<std::pair<std::string, std::pair<int, int>>> history;

    std::pair<int, int> calculateFeedback(const std::string& guess, const std::string& secret) const;
    bool isConsistent(const std::string& candidate) const;
    void generateNextLexicographicalGuess();
    bool hasUniqueDigits(const std::string& str) const;
};

#endif