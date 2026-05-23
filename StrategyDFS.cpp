#include "IStrategy.h"
#include "StrategyDFS.h"


std::string StrategyDFS::getNextGuess() {
    if (currentGuess.empty()) {
        currentGuess = getFirstGuess();
        return currentGuess;
    }

    // Change the digits of the guess until a consistent guess is found [cite: 171, 172]
    // We look for the next lexicographically smallest consistent guess [cite: 177]
    do {
        generateNextLexicographicalGuess(currentGuess);
    } while (!isConsistent(currentGuess) && !currentGuess.empty());

    return currentGuess;
}

void StrategyDFS::handleFeedback(int bulls, int cows) {
    if (bulls == n) {
        finished = true; // We won [cite: 170]
    }
    else {
        // Save to history to check consistency for future guesses
        history.push_back({ currentGuess, {bulls, cows} });
    }
}

bool StrategyDFS::isConsistent(const std::string& candidate) const {
    for (const auto& record : history) {
        const std::string& pastGuess = record.first;
        int expectedBulls = record.second.first;
        int expectedCows = record.second.second;

        // Calculate what the feedback WOULD be
        std::pair<int, int> simulatedFeedback = calculateFeedback(candidate, pastGuess);

        if (simulatedFeedback.first != expectedBulls || simulatedFeedback.second != expectedCows) {
            return false; // Not consistent with this past guess
        }
    }
    return true; // Consistent with ALL past guesses
}



