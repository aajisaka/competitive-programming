#include <bits/stdc++.h>

using namespace std;

void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#define rep(i,n) for(int i=0; i<(int)(n); i++)
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

using ll = long long;
using P = pair<ll, ll>;

//constexpr ll mod = 998244353;
constexpr ll mod = 1e9+7;
const double PI = acos(-1.0);
mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());

//
// start LCA
//

// 0-indexed tree
constexpr int ROOT = 0;
constexpr int MAX_V = 100005;
const int MAX_LOG_V = ceil(log2(MAX_V));
vector<int> graph[MAX_V];
vector<vector<int>> parent;
int depth[MAX_V];

void dfs(int v, int p, int d) {
  parent[0][v] = p;
  depth[v] = d;
  for(auto& e: graph[v]) {
    if (e != p) {
      dfs(e, v, d+1);
    }
  }
}

void init(int n) {
  parent.resize(MAX_LOG_V, vector<int>(MAX_V));
  dfs(ROOT, -1, 0);
  for(int k=0; k+1<MAX_LOG_V; k++) {
    for(int v=0; v<n; v++) {
      if (parent[k][v]<0) {
        parent[k+1][v] = -1;
      } else {
        parent[k+1][v] = parent[k][parent[k][v]];
      }
    }
  }
}

int lca(int u, int v) {
  if (depth[u] > depth[v]) swap(u, v);
  for(int k=0; k<MAX_LOG_V; k++) {
    if ((depth[v] - depth[u]) >> k & 1) {
      v = parent[k][v];
    }
  }
  if (u==v) return u;
  for(int k=MAX_LOG_V-1; k>=0; k--) {
    if (parent[k][u] != parent[k][v]) {
      u = parent[k][u];
      v = parent[k][v];
    }
  }
  return parent[0][u];
}

//
// end LCA
//

vector<P> graph2[100005];
vector<P> edge(100005);
vector<P> sum[100005];
vector<P> num[100005];
vector<int> used(100005, -1);
vector<ll> length;
int cnt = 0;

void euler_tour(int p) {
  used[p] = cnt;
  length.push_back(0);
  cnt++;
  for(auto &e: graph2[p]) {
    if (used[e.first] > -1) continue;
    used[e.first] = cnt;
    int c = edge[e.second].first;
    int d = edge[e.second].second;
    sum[c].emplace_back(cnt, d);
    num[c].emplace_back(cnt, 1);
    length.push_back(d);
    cnt++;
    euler_tour(e.first);
    sum[c].emplace_back(cnt, -d);
    num[c].emplace_back(cnt, -1);
    length.push_back(-d);
    cnt++;
  }
}

void cumulative_sum() {
  rep(i, 100005) {
    for(int j=1; j<sum[i].size(); j++) {
      sum[i][j].second += sum[i][j-1].second;
      num[i][j].second += num[i][j-1].second;
    }
  }
  for(int i=1; i<length.size(); i++) {
    length[i] += length[i-1];
  }
}

ll get_num(int u, int c) {
  int pos = used[u];
  auto it = lower_bound(num[c].begin(), num[c].end(), P(pos, LLONG_MAX));
  if (it == num[c].begin()) return 0;
  it--;
  return (*it).second;
}

ll get_sum(int u, int c) {
  int pos = used[u];
  auto it = lower_bound(sum[c].begin(), sum[c].end(), P(pos, LLONG_MAX));
  if (it == sum[c].begin()) return 0;
  it--;
  return (*it).second;
}

ll get_length(int x, int y, int u) {
  int pos = used[u];
  ll len = length[pos];
  len += get_num(u, x)*y - get_sum(u, x);
  return len;
}

// verify: https://atcoder.jp/contests/abc133/submissions/6304625

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q; cin >> n >> q;
  rep(i, n-1) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    a--; b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
    graph2[a].emplace_back(b, i);
    graph2[b].emplace_back(a, i);
    edge[i].first = c;
    edge[i].second = d;
  }
  init(n);
  euler_tour(0);
  cumulative_sum();

  while(q--) {
    int x, y, u, v;
    cin >> x >> y >> u >> v;
    u--; v--;
    int p = lca(u, v);
    auto ulen = get_length(x, y, u);
    auto vlen = get_length(x, y, v);
    auto plen = get_length(x, y, p);
    cout << ulen + vlen - 2*plen << '\n';
  }
}