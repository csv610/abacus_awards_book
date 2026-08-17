#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct Point { double x, y; };
double dot(Point a, Point b) { return a.x*b.x + a.y*b.y; }
double gw_ratio(double theta) {
    return (theta / std::acos(-1)) / ((1 - std::cos(theta)) / 2);
}

int main() {
    std::vector<Point> v{{1,0},{0,1},{-1,0},{0,-1}};
    std::vector<std::pair<int,int>> edges{{0,1},{1,2},{2,3},{3,0}};
    std::mt19937 rng(11);
    std::uniform_real_distribution<double> angle(0, 2 * std::acos(-1));
    int cut = 0;
    for (int trial = 0; trial < 10000; ++trial) {
        double a = angle(rng); Point r{std::cos(a), std::sin(a)};
        int value = 0;
        for (auto [u,w] : edges) value += (dot(r,v[u]) * dot(r,v[w]) < 0);
        cut += value;
    }
    std::cout << "average cut after random hyperplane rounding = "
              << static_cast<double>(cut) / 10000 << " of " << edges.size() << " edges\n";
    std::cout << "The SDP represents labels by vectors; the hyperplane turns them into two sides.\n";
    double worst = 1.0;
    for (int i = 1; i < 10000; ++i) worst = std::min(worst, gw_ratio(std::acos(-1) * i / 10000.0));
    std::cout << "sampled Goemans-Williamson worst ratio = " << worst << '\n';
}
