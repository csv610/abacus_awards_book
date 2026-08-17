#include <iostream>
#include <numeric>
#include <vector>

// STUDENT OBJECTIVE
// Learn that a zero-one matrix can encode a bipartite matching problem. The
// program counts perfect matchings twice—by trying choices recursively and by
// Ryser's permanent formula—and compares the answers. Both methods are
// exponential here; this is a counting demonstration, not a fast solver.

long long count_matchings(const std::vector<std::vector<int>>& a, int row, int used) {
    if (row == static_cast<int>(a.size())) return 1;
    long long total = 0;
    for (int col = 0; col < static_cast<int>(a.size()); ++col)
        if (a[row][col] && !(used & (1 << col)))
            total += count_matchings(a, row + 1, used | (1 << col));
    return total;
}

long long permanent_ryser(const std::vector<std::vector<int>>& a) {
    const int n = static_cast<int>(a.size()); long long total = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        long long product = 1;
        for (int row = 0; row < n; ++row) {
            long long sum = 0;
            for (int col = 0; col < n; ++col) if (mask & (1 << col)) sum += a[row][col];
            product *= sum;
        }
        int omitted = n - __builtin_popcount(static_cast<unsigned>(mask));
        total += (omitted % 2 ? -product : product);
    }
    return total;
}

int main() {
    // Complete bipartite graph K_3,3 with edge (row 0, column 0) removed.
    std::vector<std::vector<int>> a(3, std::vector<int>(3, 1));
    a[0][0] = 0;
    const auto brute = count_matchings(a, 0, 0);
    std::cout << "perfect matchings = " << brute << "\n";
    std::cout << "Ryser permanent = " << permanent_ryser(a) << "\n";
    if (brute != permanent_ryser(a)) return 1;
    std::cout << "The permanent counts all matchings; decision only asks whether the count is nonzero.\n";
}
