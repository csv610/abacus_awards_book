#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

std::pair<std::vector<double>, std::vector<double>> hits(const std::vector<std::vector<int>>& links, int rounds) {
    std::vector<double> a(links.size(), 1), h(links.size(), 1);
    for (int round = 0; round < rounds; ++round) {
        std::vector<double> next_a(a.size()), next_h(a.size());
        for (int u = 0; u < static_cast<int>(links.size()); ++u)
            for (int v : links[u]) { next_a[v] += h[u]; next_h[u] += a[v]; }
        a = next_a; h = next_h;
    }
    return {a, h};
}

int greedy_grid_route(int n, std::pair<int,int> start, std::pair<int,int> target,
                      const std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>>& shortcuts) {
    auto distance = [](auto a, auto b) { return std::abs(a.first-b.first) + std::abs(a.second-b.second); };
    auto current = start; int steps = 0;
    while (current != target && steps < n*n) {
        auto next = current;
        auto best = distance(current, target);
        for (auto candidate : {std::pair<int,int>{current.first + 1, current.second},
                               std::pair<int,int>{current.first, current.second + 1}})
            if (candidate.first <= n && candidate.second <= n && distance(candidate, target) < best)
                best = distance(candidate, target), next = candidate;
        for (const auto& [from, to] : shortcuts)
            if (from == current && distance(to, target) < best) best = distance(to, target), next = to;
        if (next == current) break;
        current = next; ++steps;
    }
    return current == target ? steps : -1;
}

int main() {
    // Directed pages: B->A, C->A, C->B, D->C.
    std::vector<std::vector<int>> links{{}, {0}, {0,1}, {2}};
    std::vector<double> authority(4, 1), hub(4, 1);
    for (int round = 1; round <= 3; ++round) {
        std::vector<double> next_a(4), next_h(4);
        for (int u = 0; u < 4; ++u)
            for (int v : links[u]) { next_a[v] += hub[u]; next_h[u] += authority[v]; }
        authority = next_a; hub = next_h;
        std::cout << "round " << round << " authority:";
        for (double x : authority) std::cout << ' ' << x;
        std::cout << " | hub:";
        for (double x : hub) std::cout << ' ' << x;
        std::cout << '\n';
    }
    std::cout << "HITS reinforces authority and hub scores; Kleinberg's grid model studies local routing separately.\n";
    auto scores = hits(links, 5);
    std::cout << "reusable HITS authority after 5 rounds: " << scores.first[0] << '\n';
    std::cout << "greedy route with shortcut: " << greedy_grid_route(4, {1,1}, {4,4}, {{{1,1},{3,3}}}) << " steps\n";
}
