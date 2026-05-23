#ifndef STRATEGY_DFS_H
#define STRATEGY_DFS_H

#include "IStrategy.h"
#include <vector>
#include <string>

class StrategyDFS : public IStrategy {
public:
    StrategyDFS(int n, int k);
    std::string getNextGuess() override;
    void handleFeedback(int bulls, int cows) override;
    bool isFinished() const override;

private:
    int n, k;
    bool finished;
    std::string lastGuess;
    std::vector<std::string> candidates;

    std::pair<int, int> calculateFeedback(const std::string& guess, const std::string& secret) const;
    void generateCandidates(std::string& current, std::vector<bool>& used);
};

#endif