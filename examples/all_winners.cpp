#include <iostream>
#include <string>
#include <vector>

// STUDENT OBJECTIVE
// Learn how a small table of records can be stored, printed, and searched.
// Input: a year. Output: the matching winner, or "not found".
// This example treats history as data; it does not verify historical facts.

std::string find_winner(const std::vector<std::pair<int, std::string>>& winners, int year) {
    for (const auto& [y, name] : winners) if (y == year) return name;
    return "not found";
}

int main() {
    const std::vector<std::pair<int, std::string>> winners{
        {1982,"Tarjan"},{1986,"Valiant"},{1990,"Razborov"},{1994,"Wigderson"},
        {1998,"Shor"},{2002,"Sudan"},{2006,"Kleinberg"},{2010,"Spielman"},
        {2014,"Khot"},{2018,"Daskalakis"},{2022,"Braverman"},{2026,"Oveis Gharan"}
    };
    for (auto [year, name] : winners) std::cout << year << ": " << name << '\n';
    std::cout << "2010 winner: " << find_winner(winners, 2010) << '\n';
    std::cout << "The lineage is structured data: years map to winners and themes.\n";
}
