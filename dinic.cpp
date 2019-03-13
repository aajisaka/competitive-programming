struct {
  struct edge { int to; ll cost; int rev; };
  int N;
  vector<vector<edge>> graph;
  vector<int> level;
  vector<int> iter;

  void init(int n) {
    graph.resize(n+1, vector<edge>());
    level.resize(n+1);
    iter.resize(n+1);
    N=n+1;
  }

  void add_edge(int from, int to, ll cost) {
    int r1 = graph[from].size();
    int r2 = graph[to].size();
    graph[from].push_back((edge){to, cost, r2});
    graph[to].push_back((edge){from, 0, r1});
  }

  void bfs(int s) {
    for(int i=0; i<N; i++) level[i] = -1;
    queue<int> que;
    level[s] = 0; que.push(s);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(auto& e: graph[v]) {
        if (e.cost > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
      }
    }
  }

  ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    for(int &i = iter[v]; i < graph[v].size(); i++) {
      iter[v] = i;
      edge &e = graph[v][i];
      if (e.cost > 0 && level[v] < level[e.to]) {
        ll d = dfs(e.to, t, min(f, e.cost));
        if (d > 0) {
          e.cost -= d;
          graph[e.to][e.rev].cost += d;
          return d;
        }
      }
    }
    return 0;
  }

  ll max_flow(int s, int t) {
    ll flow = 0;
    while(true) {
      bfs(s);
      if (level[t] < 0) return flow;
      for(int i=0; i<N; i++) iter[i] = 0;
      ll f;
      while((f = dfs(s, t, LLONG_MAX/4)) > 0) {
        flow += f;
      }
    }
  }
} D;