#include<vector>

std::vector<int> par(200005);
std::vector<int> rak(200005);

void init(int n) {
  for(int i=1; i<=n; i++) {
    par.at(i) = i;
    rak.at(i) = 0;
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