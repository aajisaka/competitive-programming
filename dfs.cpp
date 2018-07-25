int const MAXV = 100;
int color[MAXV+1];
bool A[MAXV+1][MAXV+1];

// depth first search
// return false if the graph is not bipartite graph
bool dfs(int v, int c) {
  color[v] = c;
  for (int i = 1; i <= MAXV; i++) {
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