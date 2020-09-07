#include<vector>

struct DisjointSet {
    std::vector<int> par;
    std::vector<int> rak; // number of the vertices

    void init(int n) {
      par.resize(n);
      rak.resize(n);
      for(int i=0; i<n; i++) {
        par[i] = i;
        rak[i] = 1;
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
        rak[y] += rak[x];
        par[x] = y;
      } else {
        rak[x] += rak[y];
        par[y] = x;
      }
    }

    bool same(int x, int y) {
      return find(x) == find(y);
    }
};
