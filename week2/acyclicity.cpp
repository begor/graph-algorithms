#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

int CLOCK = 1;


void postvisit(vector<int> &postvisit_nums, int v) {
  postvisit_nums[v] = CLOCK++;
}


void dfs(vector<vector<int>> &adj, unordered_set<int> &visited, vector<int> &postvisit_nums, int v) {
  visited.insert(v);

  for (int n : adj[v]) {
    if (visited.find(n) == visited.end()) {
      dfs(adj, visited, postvisit_nums, n);
    }
  }

  postvisit(postvisit_nums, v);
};


int has_cycle(vector<vector<int>> &adj) {
  vector<int> postvisit_nums(adj.size());
  unordered_set<int> visited;

  // First: regular DFS with postorder numbers
  for (int i = 0; i < adj.size(); i++) {
    if (visited.find(i) == visited.end()) {
      dfs(adj, visited, postvisit_nums, i);
    }
  }

  // Second: theorem -- if it's a DAG with edje from u to v, than post[u] > post[v]
  for (int i = 0; i < adj.size(); i++) {
    for (int j : adj[i]) {
      if (postvisit_nums[i] <= postvisit_nums[j]) {
        return 1;
      }
    }
  }

  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  
  vector<vector<int>> adj(n, vector<int>());

  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  std::cout << has_cycle(adj);
}
