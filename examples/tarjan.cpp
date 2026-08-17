#include <iostream>
#include <stack>
#include <vector>

// STUDENT OBJECTIVE
// Learn three graph operations. Union-find answers whether vertices are in the
// same component; bridge detection finds edges whose removal disconnects a
// graph; SCC detection groups mutually reachable directed vertices. The sample
// graphs are small so the DFS state can be inspected easily.

struct DSU {
    std::vector<int> p, rank;
    explicit DSU(int n) : p(n), rank(n, 0) { for (int i = 0; i < n; ++i) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b); if (a == b) return;
        if (rank[a] < rank[b]) std::swap(a, b);
        p[b] = a; if (rank[a] == rank[b]) ++rank[a];
    }
};

int timer = 0;
void bridges(int v, int parent, const std::vector<std::vector<int>>& g,
             std::vector<int>& tin, std::vector<int>& low) {
    tin[v] = low[v] = ++timer;
    for (int to : g[v]) {
        if (to == parent) continue;
        if (tin[to]) low[v] = std::min(low[v], tin[to]);
        else {
            bridges(to, v, g, tin, low);
            low[v] = std::min(low[v], low[to]);
            if (low[to] > tin[v]) std::cout << "bridge: " << v << "-" << to << '\n';
        }
    }
}

void strongly_connected(int v, const std::vector<std::vector<int>>& g,
                        std::vector<int>& index, std::vector<int>& low,
                        std::vector<bool>& on_stack, std::stack<int>& active,
                        int& next_index, std::vector<std::vector<int>>& components) {
    index[v] = low[v] = next_index++;
    active.push(v); on_stack[v] = true;
    for (int to : g[v]) {
        if (index[to] == -1) {
            strongly_connected(to, g, index, low, on_stack, active, next_index, components);
            low[v] = std::min(low[v], low[to]);
        } else if (on_stack[to]) low[v] = std::min(low[v], index[to]);
    }
    if (low[v] == index[v]) {
        components.emplace_back();
        while (true) {
            int u = active.top(); active.pop(); on_stack[u] = false;
            components.back().push_back(u); if (u == v) break;
        }
    }
}

int main() {
    DSU dsu(6);
    dsu.unite(0, 1); dsu.unite(2, 3); dsu.unite(1, 2);
    std::cout << "find(0) == find(3): " << std::boolalpha
              << (dsu.find(0) == dsu.find(3)) << "\n";

    std::vector<std::vector<int>> g(6);
    auto add = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    add(0, 1); add(1, 2); add(2, 0); add(2, 3); add(3, 4); add(4, 5); add(5, 3);
    std::vector<int> tin(6), low(6);
    bridges(0, -1, g, tin, low);

    std::vector<std::vector<int>> directed{{1}, {2}, {0,3}, {4}, {3}};
    std::vector<int> index(5, -1), scc_low(5); std::vector<bool> on_stack(5);
    std::stack<int> active; int next_index = 0; std::vector<std::vector<int>> components;
    for (int v = 0; v < 5; ++v) if (index[v] == -1)
        strongly_connected(v, directed, index, scc_low, on_stack, active, next_index, components);
    std::cout << "SCC count = " << components.size() << "\n";
}
