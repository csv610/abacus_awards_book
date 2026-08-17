#include <cmath>
#include <iostream>
#include <vector>

// STUDENT OBJECTIVE
// -----------------
// By the end of this small program, you should be able to:
//   1. recognize the mixed Nash equilibrium of matching pennies;
//   2. check whether a proposed strategy is within epsilon of that equilibrium;
//   3. follow a simple path whose endpoint is guaranteed to exist.
//
// These are the two ideas used here to introduce Daskalakis's area of work:
// equilibrium computation and the path-following viewpoint behind PPAD.
// This program is an illustration. It is not a hardness proof or a complete
// PPAD implementation.

// In matching pennies, row plays Heads with probability row_heads and column
// plays Heads with probability column_heads. The exact equilibrium is:
//       row_heads = 1/2 and column_heads = 1/2.
// At those probabilities, neither player can improve by changing only their
// own strategy. We call a strategy epsilon-close when both probabilities are
// at most epsilon away from 1/2.
bool is_epsilon_equilibrium(double row_heads, double column_heads,
                            double epsilon) {
    return std::abs(row_heads - 0.5) <= epsilon &&
           std::abs(column_heads - 0.5) <= epsilon;
}

// A tiny path-following example. successor[u] tells us the next node after u.
// The value -1 means that u is an endpoint.
void print_path(const std::vector<int>& successor, int start) {
    int node = start;
    while (node != -1) {
        std::cout << node;
        node = successor[node];
        if (node != -1)
            std::cout << " -> ";
    }
}

int main() {
    constexpr double exact_equilibrium = 0.5;
    constexpr double epsilon = 0.01;

    std::cout << "DASKALAKIS EXAMPLE\n\n";

    std::cout << "Part 1: matching pennies\n";
    std::cout << "Goal: find strategies from which neither player wants to deviate.\n";
    std::cout << "Exact equilibrium: Row plays Heads with probability "
              << exact_equilibrium << ", and Column does the same.\n";

    const double row_heads = 0.5;
    const double column_heads = 0.5;
    std::cout << "Check: is this a " << epsilon << "-equilibrium? "
              << std::boolalpha
              << is_epsilon_equilibrium(row_heads, column_heads, epsilon)
              << "\n\n";

    std::cout << "Part 2: path following\n";
    std::cout << "Goal: start at node 0 and follow successor links to an endpoint.\n";
    const std::vector<int> successor{1, 2, -1};
    std::cout << "Path: ";
    print_path(successor, 0);
    std::cout << "\nEndpoint: node 2\n\n";

    std::cout << "What this demonstrates:\n"
              << "- Nash equilibrium is a search problem: find stable strategies.\n"
              << "- A path-following problem can guarantee that another endpoint exists.\n"
              << "- Real PPAD examples use an implicit, possibly very large graph;\n"
              << "  this three-node path is only a readable toy model.\n";
}
