int N=100;
int color[100];
bool A[100][100];

// depth first search
// return false if the graph is not bipartite graph
bool dfs(int v, int c) {
  color[v] = c;
  for (int i = 1; i <= N; i++) {
    if (v == i) {
      continue;
    }
    if (A[v][i]) {
      if (color[i] == c) {
        return false;
      }
      if (color[i] == 0 && !dfs(i, c*(-1))) {
        return false;
      }
    }
  }
  return true;
}