#include <iostream>
#include <cmath>
#include <vector>

// OBJECTIVE: Illustrate two ideas connected with Daskalakis's work: a simple
// Nash equilibrium and a small PPAD-style path with another endpoint.

bool epsilon_equilibrium(double row_h, double col_h, double epsilon) {
    // Matching pennies: with a fair opponent, neither pure deviation improves payoff.
    return std::abs(row_h - 0.5) <= epsilon && std::abs(col_h - 0.5) <= epsilon;
}

int main() {
    std::cout << "Matching pennies equilibrium: Row(H)=1/2, Column(H)=1/2.\n";
    std::vector<int> successor{1, 2, -1, 4, -1};
    int node = 0;
    std::cout << "PPAD path: ";
    while (node != -1) {
        std::cout << node;
        node = successor[node];
        if (node != -1) std::cout << " -> ";
    }
    std::cout << " (the other endpoint is 2)\n";
    std::cout << "The path guarantees existence, but an implicit exponentially long path may be hard to follow.\n";
    std::cout << "(1/2,1/2) is a 0.01-equilibrium: " << std::boolalpha
              << epsilon_equilibrium(0.5, 0.5, 0.01) << '\n';
}
