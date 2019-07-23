#include<vector>

std::vector<int> par;
std::vector<int> rak; // rank

void init(int n) {
  par.resize(n+1);
  rak.resize(n+1, 0);
  for(int i=1; i<=n; i++) {
    par[i] = i;
  }
}

int find(int x) {
  if (par[x] == x) {
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x==y) return;
  if (rak[x] < rak[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rak[x] == rak[y]) rak[x]++;
  }
}

bool same(int x, int y) {
  return find(x) == find(y);
}