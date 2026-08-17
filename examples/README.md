# C++23 chapter demonstrations

Each file is a small, dependency-free C++23 program illustrating one idea from a book chapter. These are teaching examples, not production implementations of the full theorems.

For a chapter-by-chapter explanation of the programs, see [UserGuide.tex](UserGuide.tex).

Compile one example with:

```sh
c++ -std=c++23 -O2 -Wall -Wextra examples/tarjan.cpp -o /tmp/tarjan
/tmp/tarjan
```

The examples are:

| File | Chapter idea |
|---|---|
| `tarjan.cpp` | Union--find, bridges, and Tarjan SCCs |
| `valiant.cpp` | Matching enumeration and Ryser's permanent |
| `razborov.cpp` | Monotonicity tests versus parity |
| `wigderson.cpp` | Relabeling, brute-force isomorphism, and toy GNI |
| `shor.cpp` | Modular exponentiation, order finding, and factoring 15 |
| `sudan.cpp` | Reusable Reed--Solomon list decoding candidates |
| `kleinberg.cpp` | Reusable HITS and greedy grid routing |
| `spielman.cpp` | Laplacian energy and conjugate gradient |
| `khot.cpp` | Random-hyperplane MAX-CUT rounding and ratio sampling |
| `daskalakis.cpp` | Matching pennies, approximate equilibrium, and PPAD path |
| `braverman.cpp` | Entropy, mutual information, and protocol cost |
| `shayan_oveis_gharan.cpp` | Tree marginals and matrix-tree determinant |
| `all_winners.cpp` | The award lineage as searchable data |

The original smoke demonstrations remain in each `main()`, while reusable functions now expose the paper-oriented mechanism. `examples/razborov.cpp` and `examples/wigderson.cpp` demonstrate restricted toy models; they do not prove asymptotic lower bounds or solve general graph isomorphism. Likewise, the Shor, Khot, Spielman, and Oveis Gharan examples reproduce small classical components rather than the full quantum, hardness, nearly-linear, or TSP results.
