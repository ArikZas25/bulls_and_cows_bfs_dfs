#ifndef STRATEGY_BFS_H
#define STRATEGY_BFS_H

#include "IStrategy.h"
#include <vector>
#include <set>

/**
 * StrategyBFS - Minimax Strategy for Bulls and Cows
 *
 * Uses a minimax approach with search space depth minimization.
 * Algorithm:
 * 1. Maintain set S of all consistent candidate guesses
 * 2. Choose guess with minimal worst-case search space depth
 * 3. Filter S based on feedback
 * 4. Repeat until solved
 */
class StrategyBFS : public IStrategy {
public:
    /**
     * Constructor
     * @param n - number of digits
     * @param k - range of digits (0 to k-1)
     */
    StrategyBFS(int n, int k);

    /**
     * Get the next guess according to minimax strategy
     * @return the next guess as a string
     */
    std::string getNextGuess() override;

    /**
     * Handle feedback for the previous guess
     * @param bulls - number of bulls (correct digit in correct position)
     * @param cows - number of cows (correct digit in wrong position)
     */
    void handleFeedback(int bulls, int cows) override;

    /**
     * Check if strategy is finished
     * @return true if the secret number has been found
     */
    bool isFinished() const override;

private:
    int n;          // Number of digits
    int k;          // Range of digits (0 to k-1)
    std::set<std::string> S;  // Set of consistent candidates
    bool finished;  // Flag indicating if secret found
    std::string lastGuess;  // Last guess made

    /**
     * Generate all possible n-digit numbers with digits in range [0, k-1]
     * @return set of all possible guesses as strings
     */
    std::set<std::string> generateAllGuesses() const;

    /**
     * Helper that runs our recursive backtracking to generate guesses
     * @return set of all possible guesses as strings
     */
    void StrategyBFS::generateGuessesHelper(std::string& current_guess, std::vector<bool>& used, std::set<std::string>& guesses) const;

    /**
     * Calculate feedback (bulls and cows) between two guesses
     * @param guess - the guessed number
     * @param secret - the secret number
     * @return pair<bulls, cows>
     */
    std::pair<int, int> calculateFeedback(const std::string& guess, const std::string& secret) const;

    /**
     * Filter set S to keep only consistent guesses
     * Removes all guesses that don't match the feedback when compared to lastGuess
     * @param bulls - bulls in feedback
     * @param cows - cows in feedback
     */
    void filterConsistent(int bulls, int cows);

    /**
     * Calculate search space depth for a given guess
     * depth(x) = max over all y in S of: |{candidates in S that match feedback(x,y)}|
     * @param guess - the candidate guess
     * @return the maximum search space size for worst-case scenario
     */
    int calculateSearchSpaceDepth(const std::string& guess) const;

    /**
     * Select the best guess from S using minimax criteria
     * Chooses guess that minimizes search space depth
     * If multiple guesses have same depth, chooses lexicographically smallest
     * @return the best guess
     */
    std::string selectBestGuess();
};

#endif // STRATEGY_BFS_H