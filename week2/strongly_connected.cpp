#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

vector<vector<int>> get_reversed_graph(vector<vector<int>> &adj) {
  vector<vector<int>> reverse_adj(adj.size(), vector<int>());

  for (int i = 0; i < adj.size(); i++) {
    for (int j : adj[i]) {
      reverse_adj[j].push_back(i);
    }
  }

  return reverse_adj;
}

void dfs(vector<vector<int>> &adj, unordered_set<int> &visited, vector<int> &order, int i) {
  visited.insert(i);

  for (int x : adj[i]) {
    if (visited.find(x) == visited.end()) {
      dfs(adj, visited, order, x);
    }
  }

  order.push_back(i);
}

vector<int> get_desc_post_order(vector<vector<int>> &adj) {
  vector<int> order;
  unordered_set<int> visited;

  for (int i = 0; i < adj.size(); i++) {
    if (visited.find(i) == visited.end()) {
      dfs(adj, visited, order, i);
    }
  }

  std::reverse(order.begin(), order.end());

  return order;
}

int get_scc_num(vector<vector<int>> &adj, vector<int> &order) {
  unordered_set<int> visited;
  vector<int> new_order;  // Just to be able to use dfs procedure without modifications, we don't need ordering here
 
  int result = 0;
  for (int i : order) {
    if (visited.find(i) == visited.end()) {
      dfs(adj, visited, new_order, i);
      result++;
    }
  }

  return result;
}

int number_of_strongly_connected_components(vector<vector<int>> &adj) {
  // Get Gr -- reversed graph of given graph G
  auto revesed_graph = get_reversed_graph(adj);
  // Get decreasing post order from Gr
  auto desc_order = get_desc_post_order(revesed_graph);

  // Run connected components on G using desc post order on Gr
  return get_scc_num(adj, desc_order);
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
  std::cout << number_of_strongly_connected_components(adj);
}
