#ifndef STRATEGY_DFS_H
#define STRATEGY_DFS_H

#include "IStrategy.h"
#include <string>
#include <vector>
#include <utility>

/**
 * StrategyDFS - DFS-based Strategy for Bulls and Cows
 *
 * Iterates through possible guesses in lexicographical order and finds
 * the first guess that is consistent with all previous feedback.
 */
class StrategyDFS : public IStrategy {
public:
    StrategyDFS(int n, int k);

    std::string getNextGuess() override;
    void handleFeedback(int bulls, int cows) override;
    bool isFinished() const override;

private:
    int n;
    int k;
    bool finished;
    std::string currentGuess;

    // Stores history of (Guess, (Bulls, Cows))
    std::vector<std::pair<std::string, std::pair<int, int>>> history;

    // Helper functions
    std::string getFirstGuess() const;
    void generateNextLexicographicalGuess(std::string& guess);
    bool hasUniqueDigits(const std::string& str) const;
    bool isConsistent(const std::string& candidate) const;
    std::pair<int, int> calculateFeedback(const std::string& guess, const std::string& secret) const;
};

#endif // STRATEGY_DFS_H