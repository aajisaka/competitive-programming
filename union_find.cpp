#include<vector>

std::vector<int> par;
std::vector<int> rak; // rank

void init(int n) {
  par.resize(n+1);
  rak.resize(n+1);
  for(int i=1; i<=n; i++) {
    par[i] = i;
    rak[i] = 0;
  }
}

int find(int x) {
  if (par.at(x) == x) {
    return x;
  } else {
    return par.at(x) = find(par.at(x));
  }
}

void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x==y) return;
  if (rak.at(x) < rak.at(y)) {
    par.at(x) = y;
  } else {
    par.at(y) = x;
    if (rak.at(x) == rak.at(y)) rak.at(x)++;
  }
}

bool same(int x, int y) {
  return find(x) == find(y);
}