#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

double H(double p) {
    auto term = [](double q) { return q == 0 ? 0.0 : -q * std::log2(q); };
    return term(p) + term(1 - p);
}

double mutual_information_noisy_bit(double noise) { return 1.0 - H(noise); }

double and_protocol_internal_information(double probability_x_one) {
    return H(probability_x_one) + probability_x_one;
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    for (double noise : {0.0, 0.25, 0.5})
        std::cout << "noise " << noise << ": I(X;Z) = " << mutual_information_noisy_bit(noise) << " bits\n";
    std::cout << "For the fair-bit AND protocol, internal information cost = "
              << and_protocol_internal_information(0.5) << " bits.\n";
    std::cout << "For Pr[X=1]=1/4, cost = " << and_protocol_internal_information(0.25) << " bits.\n";
}
