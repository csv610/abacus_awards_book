#include <iostream>
#include <numeric>
#include <vector>

// OBJECTIVE: Demonstrate the classical number-theory part of Shor's method:
// find an order modulo 15 and use that order to recover factors 3 and 5.

int mod_pow(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent) {
        if (exponent & 1) result = result * base % modulus;
        base = base * base % modulus; exponent >>= 1;
    }
    return result;
}

int find_order(int a, int n) {
    int value = 1;
    for (int r = 1; r <= n; ++r) { value = value * a % n; if (value == 1) return r; }
    return -1;
}

std::vector<int> factor_from_order(int a, int n, int r) {
    if (r <= 0 || r % 2 || mod_pow(a, r / 2, n) == n - 1) return {};
    int half = mod_pow(a, r / 2, n);
    int p = std::gcd(half - 1, n), q = std::gcd(half + 1, n);
    return (p > 1 && q > 1 && p < n && q < n) ? std::vector<int>{p, q} : std::vector<int>{};
}

int main() {
    const int N = 15, a = 7;
    int r = find_order(a, N);
    std::cout << "order of " << a << " modulo " << N << " = " << r << '\n';
    auto factors = factor_from_order(a, N, r);
    if (!factors.empty()) std::cout << "factors: " << factors[0] << " and " << factors[1] << '\n';
    std::cout << "A quantum computer accelerates the order-finding step; this program performs it classically.\n";
}
