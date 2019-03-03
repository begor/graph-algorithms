#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;


int reach(vector<vector<int>> &adj, unordered_set<int> &visited, int x, int y) {
  if (x == y) {
    return 1;
  }

  visited.insert(x);

  for (int n : adj[x]) {
    if (visited.find(n) == visited.end()) {
      if (reach(adj, visited, n, y) == 1) {
        return 1;
      }
    }
  }

  return 0;
};


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
  int x, y;
  std::cin >> x >> y;
  unordered_set<int> visited; 
  std::cout << reach(adj, visited, x - 1, y - 1);
}