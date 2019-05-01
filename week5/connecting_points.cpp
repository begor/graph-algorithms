#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>
#include <unordered_set>
#include <functional>

using std::vector;
using std::unordered_set;
using std::pair;
using std::priority_queue;


vector<vector<double>> get_dist_matrix(vector<int> x, vector<int> y) {
  vector<vector<double>> dist_matrix;

  for (int u = 0; u < x.size(); u++) {
    vector<double> u_dists;

    for (int v = 0; v < x.size(); v++) {
      if (u == v) {
        u_dists.push_back(0.);
        continue;
      }

      int xu = x[u];
      int yu = y[u];

      int xv = x[v];
      int yv = y[v];

      double dist = sqrt(pow(xu - xv, 2) + pow(yu - yv, 2));

      u_dists.push_back(dist);
    }

    dist_matrix.push_back(u_dists);
  }

  return dist_matrix;
}


double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;

  auto dist_matrix = get_dist_matrix(x, y);
  
  // Min heap
  priority_queue<pair<double, int>, std::vector<pair<double, int>>, std::greater<pair<double, int>>> q;
  unordered_set<int> s;

  q.push(std::make_pair(0., 0));

  while (!q.empty()) {
    auto point_dist = q.top();
    q.pop();

    int u = point_dist.second;
    double d = point_dist.first;

    if (s.find(u) != s.end()) {
      continue;
    }

    s.insert(u);
    result += d;

    for (int v = 0; v < x.size(); v++) {
      if (v == u || s.find(v) != s.end()) {
        continue;
      }

      q.push(std::make_pair(dist_matrix[u][v], v));
    }

  }

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
