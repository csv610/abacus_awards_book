#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

// STUDENT OBJECTIVE
// Learn three quantities in bits: entropy, information surviving noise, and a
// toy protocol cost. The program prints values for simple probabilities so you
// can see that a fair bit has maximum uncertainty and noise destroys information.
// The final cost is a teaching formula, not a complete protocol theorem.

// H(p) is the entropy of a bit that is 1 with probability p.
// Entropy is measured in bits because we use log base 2.
double binary_entropy(double probability_of_one) {
    const auto entropy_term = [](double probability) {
        if (probability == 0.0)
            return 0.0; // 0 log(0) is defined to be 0.
        return -probability * std::log2(probability);
    };

    return entropy_term(probability_of_one) +
           entropy_term(1.0 - probability_of_one);
}

// X is a fair bit. Z is X after a binary-symmetric noise channel:
// with probability noise_probability, the bit is flipped.
// For this special case, I(X;Z) = 1 - H(noise_probability).
double information_in_noisy_bit(double noise_probability) {
    return 1.0 - binary_entropy(noise_probability);
}

// A deliberately small teaching formula used in this example.
// It is not a general information-complexity solver for AND.
double toy_and_protocol_cost(double probability_x_is_one) {
    return binary_entropy(probability_x_is_one) + probability_x_is_one;
}

int main() {
    std::cout << std::fixed << std::setprecision(3);

    std::cout << "Braverman example: information is measured in bits.\n\n";

    std::cout << "1. Entropy of a binary random variable\n";
    for (double probability : {0.0, 0.25, 0.5, 1.0}) {
        std::cout << "   P(bit=1) = " << probability
                  << " -> H(bit) = " << binary_entropy(probability)
                  << " bits\n";
    }

    std::cout << "\n2. Information left after a noisy channel\n";
    for (double noise : {0.0, 0.25, 0.5}) {
        std::cout << "   Flip probability = " << noise
                  << " -> I(X;Z) = " << information_in_noisy_bit(noise)
                  << " bits\n";
    }

    std::cout << "\n3. A small toy protocol-cost calculation\n";
    for (double probability : {0.25, 0.5}) {
        std::cout << "   P(X=1) = " << probability
                  << " -> toy cost = " << toy_and_protocol_cost(probability)
                  << " bits\n";
    }

    std::cout << "\nInterpretation:\n"
              << "- More noise means less information about the original bit.\n"
              << "- A fair bit has the largest binary entropy: 1 bit.\n"
              << "- The last calculation is only a toy illustration; it is not\n"
              << "  a complete protocol or a proof of an information-complexity theorem.\n";
}
