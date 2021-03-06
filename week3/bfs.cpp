#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


int distance(vector<vector<int>> &adj, int s, int t) {
  int max = -1;

  vector<int> distances(adj.size(), -1);
  distances[s] = 0;

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int i = q.front();
    q.pop();

    int i_dist = distances[i];

    if (i == t) {
      return i_dist;
    }

    for (int j : adj[i]) {
      if (distances[j] == max) {
        distances[j] = i_dist + 1;
        q.push(j);
      }
    }
  }

  return distances[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
