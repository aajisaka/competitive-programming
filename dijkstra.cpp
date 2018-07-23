#include <vector>
#include <queue>
using namespace std;

// Use first for the cost, second for the point to sort by the cost
typedef pair<int, int> P;
struct edge {
    int to, cost;
};
int V=100;
vector<edge> G[101]; // graph
int d[101]; // d[i] is the distance between s to i

// s is the starting point
void dijkstra(int s) {
  // Initialize d[i]. Initialization can be done outside this method.
  fill(d, d+V, INT_MAX);
  d[s] = 0;

  priority_queue<P, vector<P>, greater<>> queue;
  queue.push(P(0, s));
  while (!queue.empty()) {
    P p = queue.top(); queue.pop();
    int u = p.second;
    if (d[u] < p.first) {
      continue;
    }
    for (edge e : G[u]) {
      if (d[u] + e.cost < d[e.to]) {
        d[e.to] = d[u] + e.cost;
        queue.push(P(d[e.to], e.to));
      }
    }
  }
}