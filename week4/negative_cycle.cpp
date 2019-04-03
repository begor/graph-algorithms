#include <iostream>
#include <limits>
#include <vector>

using std::vector;
using std::pair;

int negative_cycle(vector<vector<pair<int, int>>> &adj) {
  for (int s = 0; s < adj.size(); s++) {
    vector<int> distance(adj.size(), 100500);

    distance[s] = 0;

    bool result = false;

    for (int i = 0; i <= adj.size(); i++) {
      bool has_changed = false;

      for (int u = 0; u < adj.size(); u++) {
        for (auto v_pair : adj[u]) {
          int d = distance[u];
          int v = v_pair.first;
          int d_uv = v_pair.second;
          int new_d = d + d_uv;
   
          if (new_d < distance[v]) {
            has_changed = true;
            distance[v] = new_d;
          }
        }
      }

      result = has_changed;
    }

    if (result) {
      return 1;
    }
  }

  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(std::make_pair(y - 1, w));
  }
  std::cout << negative_cycle(adj);
}
