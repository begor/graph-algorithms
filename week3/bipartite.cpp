#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

enum NodeColour { none, black, white };

NodeColour get_opposite_colour(NodeColour col) {
  return col == white ? black : white;
}

int is_bipartite_bfs(vector<vector<int>> &adj, vector<NodeColour> &nodes_colour, int n) {
  nodes_colour[n] = white;

  queue<int> q;
  q.push(n);

  while (!q.empty()) {
    int i = q.front();
    q.pop();

    NodeColour icol = nodes_colour[i];

    for (int k : adj[i]) {
      if (nodes_colour[k] == icol) {
        return 0;
      } else if (nodes_colour[k] == none) {
        nodes_colour[k] = get_opposite_colour(icol);
        q.push(k);
      }
    }
  }

  return 1;
}

int bipartite(vector<vector<int>> &adj) {
  vector<NodeColour> nodes_colour(adj.size(), none);

  for (int i = 0; i < adj.size(); i++) {
    if (nodes_colour[i] != none)
      continue;

    if (!is_bipartite_bfs(adj, nodes_colour, i))
      return 0;
  }

  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
