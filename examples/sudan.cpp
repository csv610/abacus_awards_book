#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

// OBJECTIVE: List all degree-one polynomial messages that agree with enough
// received data points. This is a tiny, readable list-decoding example.

struct Line { double m, b; };
bool operator<(const Line& a, const Line& b) { return a.m != b.m ? a.m < b.m : a.b < b.b; }

std::set<Line> list_decode(const std::vector<double>& x, const std::vector<double>& y, int minimum_agreement) {
    std::set<Line> candidates;
    for (int i = 0; i < static_cast<int>(x.size()); ++i)
        for (int j = i + 1; j < static_cast<int>(x.size()); ++j) {
            double m = (y[j] - y[i]) / (x[j] - x[i]), b = y[i] - m * x[i];
            int agreements = 0;
            for (int k = 0; k < static_cast<int>(x.size()); ++k)
                if (m * x[k] + b == y[k]) ++agreements;
            if (agreements >= minimum_agreement) candidates.insert({m, b});
        }
    return candidates;
}

int main() {
    // Received word (1,0,0,7) at x=(0,1,2,3). List degree-1 candidates
    // agreeing at least twice by interpolating every pair of received points.
    const double x[] = {0, 1, 2, 3}, y[] = {1, 0, 0, 7};
    std::set<Line> candidates = list_decode({x, x + 4}, {y, y + 4}, 2);
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& [m, b] : candidates)
        std::cout << "candidate p(x) = " << m << "x + " << b << '\n';
    std::cout << "The true message remains on the list despite two corrupted symbols.\n";
}
