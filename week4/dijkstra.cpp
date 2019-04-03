#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(vector<vector<pair<int, int>>> &adj, int s, int t) {
  vector<int> dist(adj.size(), std::numeric_limits<int>::max());

  priority_queue<pair<int, int>> q;

  dist[s] = 0;
  auto s_pair = std::make_pair(0, s);

  q.push(s_pair);

  while (!q.empty()) {
    auto u_pair = q.top();
    q.pop();

    int d = u_pair.first;
    int u = u_pair.second;
    
    for (auto v_pair : adj[u]) {
      int v = v_pair.first;
      int cost = v_pair.second;

      int new_dist = d + cost;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
        q.push(std::make_pair(new_dist, v));
      }
    }
  }

  return dist[t] < std::numeric_limits<int>::max() ? dist[t] : -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, int>> > adj(n, vector<pair<int, int>>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(std::make_pair(y - 1, w));
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
