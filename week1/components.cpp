#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;


void dfs(vector<vector<int>> &adj, unordered_set<int> &visited, int v) {
  visited.insert(v);

  for (int n : adj[v]) {
    if (visited.find(n) == visited.end()) {
      dfs(adj, visited, n);
    }
  }
};


int components(vector<vector<int>> &adj) {
  int comps = 0;
  unordered_set<int> visited;

  for (int i = 0; i < adj.size(); i++) {
    if (visited.find(i) == visited.end()) {
      dfs(adj, visited, i);
      comps += 1;
    }
  }

  return comps;
}


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());

  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  
  std::cout << components(adj);
}