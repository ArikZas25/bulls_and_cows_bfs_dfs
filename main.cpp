#include <iostream>
#include "StrategyBFS.h"
#include "StrategyDFS.h"

int main() {
    std::cout << "Bulls and Cows - BFS/DFS Strategies" << std::endl;
    std::cout << "Testing BFS Strategy with n=4, k=6..." << std::endl;

    StrategyBFS bfs(4, 6);
    std::cout << "First BFS guess: " << bfs.getNextGuess() << std::endl;

    return 0;
}