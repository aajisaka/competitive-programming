#include<vector>

std::vector<int> par(200005);
std::vector<int> rank(200005);

void init(int n) {
  for(int i=1; i<=n; i++) {
    par.at(i) = i;
    rank.at(i) = 0;
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
  if (rank.at(x) < rank.at(y)) {
    par.at(x) = y;
  } else {
    par.at(y) = x;
    if (rank.at(x) == rank.at(y)) rank.at(x)++;
  }
}

bool same(int x, int y) {
  return find(x) == find(y);
}