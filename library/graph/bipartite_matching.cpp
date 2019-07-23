#include <vector>

constexpr int MAXN = 1e5;
vector<int> graph[MAXN+1]; // bipartite graph
vector<bool> used(MAXN+1);
vector<int> match(MAXN+1, -1);

bool dfs(int v) {
  used[v] = true;
  for(auto e: graph[v]) {
    int w = match[e];
    if (w < 0 || (!used[w] && dfs(w))) {
      match[v] = e;
      match[e] = v;
      return true;
    }
  }
  return false;
}

// cnt: maximum matching, minimum vertex cover
// MAXN-cnt: maximum stable set
// detail (Japanese): https://www.slideshare.net/drken1215/ss-86894312
signed main() {
  int cnt = 0;
  for(int i=1; i<=MAXN; i++) {
    if (match[i] < 0) {
      for(int j=1; j<=MAXN; j++) used[j] = false;
      if (dfs(i)) cnt++;
    }
  }
}