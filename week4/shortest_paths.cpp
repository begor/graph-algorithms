#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void fill_negative_shortest(vector<vector<pair<int, int>>> &adj, vector<int> &negative, vector<int> &shortest) {
  vector<int> seen(adj.size(), 0);

  for (int i : negative) {
    queue<int> q;
    
    q.push(i);
    shortest[i] = 0;
    seen[i] = 1;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto pair : adj[u]) {
        int v = pair.first;

        if (!seen[v]) {
          shortest[v] = 0;
          seen[v] = 1;
          q.push(v);
        }
      }
    }
  }
  
}

void shortest_paths(vector<vector<pair<int, int>>> &adj, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  distance[s] = 0;
  reachable[s] = 1;
  vector<int> changed;

  for (int i = 0; i <= adj.size(); i++) {
    vector<int> changed_this_iteration;

    for (int u = 0; u < adj.size(); u++) {
      long long d = distance[u];

      if (!reachable[u]) {
        continue;
      }

      for (auto pair : adj[u]) {
        int v = pair.first;
        long long d1 = (long long)pair.second;

        if (d + d1 < distance[v]) {
          distance[v] = d + d1;
          changed_this_iteration.push_back(v);
          shortest[v] = 1;
          reachable[v] = 1;
        }
      }
    }

    changed = changed_this_iteration;
  }

  fill_negative_shortest(adj, changed, shortest);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<pair<int, int>> > adj(n, vector<pair<int, int>>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(std::make_pair(y - 1, w));
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
