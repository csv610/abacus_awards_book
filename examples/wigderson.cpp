#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

std::vector<int> degree_sequence(const std::vector<std::pair<int, int>>& edges, int n) {
    std::vector<int> d(n);
    for (auto [u, v] : edges) { ++d[u]; ++d[v]; }
    std::sort(d.begin(), d.end());
    return d;
}

std::vector<std::pair<int, int>> relabel(const std::vector<std::pair<int, int>>& edges,
                                         const std::vector<int>& permutation) {
    std::vector<std::pair<int, int>> result;
    for (auto [u, v] : edges) result.push_back({permutation[u], permutation[v]});
    return result;
}

bool same_graph(const std::vector<std::pair<int, int>>& a,
                const std::vector<std::pair<int, int>>& b, int n) {
    auto normal = [n](const std::vector<std::pair<int, int>>& edges) {
        std::vector<std::vector<bool>> m(n, std::vector<bool>(n));
        for (auto [u, v] : edges) m[u][v] = m[v][u] = true;
        return m;
    };
    auto target = normal(b); std::vector<int> p(n); std::iota(p.begin(), p.end(), 0);
    do {
        if (normal(relabel(a, p)) == target) return true;
    } while (std::next_permutation(p.begin(), p.end()));
    return false;
}

int main() {
    // C5 versus a triangle with a two-edge tail: both have 5 vertices and 5 edges.
    std::vector<std::pair<int, int>> cycle{{0,1},{1,2},{2,3},{3,4},{4,0}};
    std::vector<std::pair<int, int>> tail{{0,1},{1,2},{2,0},{0,3},{3,4}};
    std::mt19937 rng(7);
    std::uniform_int_distribution<int> coin(0, 1);
    for (int round = 1; round <= 5; ++round) {
        bool choose_cycle = coin(rng);
        auto degrees = degree_sequence(choose_cycle ? cycle : tail, 5);
        bool is_cycle = degrees == std::vector<int>{2,2,2,2,2};
        std::cout << "round " << round << ": verifier says "
                  << (is_cycle ? "five-cycle" : "triangle-plus-tail") << '\n';
    }
    std::cout << "This is a toy verifier using an easy invariant, not a general isomorphism algorithm.\n";
    std::cout << "brute-force isomorphism check: " << std::boolalpha
              << same_graph(cycle, tail, 5) << "\n";
}
