#include <iomanip>
#include <iostream>
#include <vector>

// STUDENT OBJECTIVE
// Learn why a graph Laplacian represents energy and how conjugate gradient
// solves a small linear system using matrix-vector products. The output gives
// an energy and an approximate solution. The dense toy solver is not a
// nearly-linear-time Spielman--Teng implementation.

double dot(const std::vector<double>& a, const std::vector<double>& b) {
    double result = 0; for (size_t i = 0; i < a.size(); ++i) result += a[i] * b[i]; return result;
}

std::vector<double> multiply(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    std::vector<double> result(A.size());
    for (size_t i = 0; i < A.size(); ++i) for (size_t j = 0; j < x.size(); ++j) result[i] += A[i][j] * x[j];
    return result;
}

std::vector<double> conjugate_gradient(const std::vector<std::vector<double>>& A,
                                       const std::vector<double>& b, int iterations) {
    std::vector<double> x(b.size()), r = b, p = r;
    double rr = dot(r, r);
    for (int i = 0; i < iterations && rr > 1e-12; ++i) {
        auto Ap = multiply(A, p); double alpha = rr / dot(p, Ap);
        for (size_t j = 0; j < x.size(); ++j) x[j] += alpha * p[j], r[j] -= alpha * Ap[j];
        double next_rr = dot(r, r), beta = next_rr / rr;
        for (size_t j = 0; j < p.size(); ++j) p[j] = r[j] + beta * p[j];
        rr = next_rr;
    }
    return x;
}

int main() {
    // Unit-weight path 1--2--3.
    std::vector<std::vector<double>> L{{1,-1,0},{-1,2,-1},{0,-1,1}};
    std::vector<double> x{1,0,-1};
    double energy = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) energy += x[i] * L[i][j] * x[j];
    std::cout << "Laplacian energy x^T L x = " << energy << '\n';
    std::cout << "For a unit path from 1 to 3, effective resistance = 1 + 1 = 2 ohms.\n";
    std::cout << "The constant vector has zero energy, expressing the Laplacian's zero eigenvalue.\n";
    // Pin the final vertex to zero so the singular Laplacian becomes solvable.
    std::vector<std::vector<double>> pinned{{1,-1},{-1,2}};
    auto solution = conjugate_gradient(pinned, {1,0}, 10);
    std::cout << "conjugate-gradient solution of pinned system: " << solution[0] << ", " << solution[1] << '\n';
}
