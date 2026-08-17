#include <iostream>
#include <vector>

// STUDENT OBJECTIVE
// Learn to test whether a Boolean function is monotone: changing any input
// from 0 to 1 must never change the output from 1 to 0. The program checks a
// complete small truth table and finds parity's violating pair. This illustrates
// one obstruction, not Razborov's full asymptotic circuit lower bound.

bool parity(const std::vector<int>& x) {
    int ones = 0; for (int bit : x) ones += bit;
    return ones % 2;
}

bool monotone(const std::vector<int>& x, const std::vector<int>& y) {
    for (size_t i = 0; i < x.size(); ++i) if (x[i] > y[i]) return true;
    return false;
}

bool is_monotone_function(const std::vector<int>& truth, int n) {
    for (int x = 0; x < (1 << n); ++x) for (int y = 0; y < (1 << n); ++y)
        if ((x & y) == x && truth[x] > truth[y]) return false;
    return true;
}

int main() {
    std::vector<int> low{0, 1, 0}, high{0, 1, 1};
    std::cout << "parity(low)=" << parity(low) << ", parity(high)=" << parity(high) << '\n';
    std::cout << "low <= high coordinatewise: " << std::boolalpha << !monotone(low, high) << '\n';
    std::cout << "Parity drops when an input rises, so no AND/OR-only circuit computes it.\n";
    std::vector<int> parity_table(8);
    for (int mask = 0; mask < 8; ++mask) parity_table[mask] = __builtin_popcount(static_cast<unsigned>(mask)) % 2;
    std::cout << "parity monotone: " << is_monotone_function(parity_table, 3) << '\n';
}
