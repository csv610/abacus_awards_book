#include <iostream>
#include <cmath>
#include <vector>

double determinant(std::vector<std::vector<double>> a) {
    double result = 1;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        int pivot = i;
        for (int j = i + 1; j < static_cast<int>(a.size()); ++j)
            if (std::abs(a[j][i]) > std::abs(a[pivot][i])) pivot = j;
        if (std::abs(a[pivot][i]) < 1e-12) return 0;
        if (pivot != i) std::swap(a[pivot], a[i]), result = -result;
        result *= a[i][i];
        for (int j = i + 1; j < static_cast<int>(a.size()); ++j) {
            double factor = a[j][i] / a[i][i];
            for (int k = i + 1; k < static_cast<int>(a.size()); ++k) a[j][k] -= factor * a[i][k];
        }
    }
    return result;
}

int main() {
    // Triangle edges a,b,c. Every spanning tree omits exactly one edge.
    std::vector<std::vector<int>> trees{{0,1},{0,2},{1,2}};
    std::vector<int> appearances(3);
    for (const auto& tree : trees) for (int edge : tree) ++appearances[edge];
    std::cout << "spanning trees of a triangle = " << trees.size() << '\n';
    for (int edge = 0; edge < 3; ++edge)
        std::cout << "edge " << char('a' + edge) << " marginal = "
                  << appearances[edge] << "/" << trees.size() << '\n';
    std::cout << "The spanning-tree polynomial is T(a,b,c)=ab+ac+bc.\n";
    // Delete one row and column from the triangle Laplacian: matrix-tree theorem.
    std::cout << "matrix-tree determinant = " << determinant({{2,-1},{-1,2}}) << '\n';
}
