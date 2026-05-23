#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>

/**
 * IStrategy - Abstract base class for Bulls and Cows guessing strategies
 *
 * Defines the interface for different strategy implementations
 * (e.g., DFS-based, BFS/Minimax-based)
 */
class IStrategy {
public:
    /**
     * Virtual destructor
     */
    virtual ~IStrategy() = default;

    /**
     * Get the next guess according to the strategy
     * @return the next guess as a string
     */
    virtual std::string getNextGuess() = 0;

    /**
     * Handle feedback for the previous guess
     * @param bulls - number of bulls (correct digit in correct position)
     * @param cows - number of cows (correct digit in wrong position)
     */
    virtual void handleFeedback(int bulls, int cows) = 0;

    /**
     * Check if the strategy has found the secret number
     * @return true if the secret number has been found (bulls == n)
     */
    virtual bool isFinished() const = 0;
};

#endif // ISTRATEGY_H