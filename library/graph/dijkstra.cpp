vector<ll> dp(MAX_V);
// P(to, cost)
vector<P> graph[MAX_V];

// copy-and-paste begin
priority_queue<P, vector<P>, greater<>> que;
que.emplace(0, 0);
dp[0] = 0;
while(!que.empty()) {
  auto p = que.top(); que.pop();
  if (p.first > dp[p.second]) continue;
  for(const auto& e: graph[p.second]) {
    if (dp[e.first] > p.first + e.second) {
      dp[e.first] = p.first + e.second;
      que.emplace(dp[e.first], e.first);
    }
  }
}
// copy-and-paste end
