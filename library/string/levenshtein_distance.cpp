#include<string>
#include<vector>
using namespace std;

// Time complexity is O(a.size()*b.size())
int get_edit_distance(const string& a, const string& b) {
  auto na = a.size();
  auto nb = b.size();
  vector<vector<int>> dp(na+1, vector<int>(nb+1));
  rep(i, na+1) dp[i][0] = i;
  rep(i, nb+1) dp[0][i] = i;

  for(int i=1; i<=na; i++) {
    for(int j=1; j<=nb; j++) {
      int m = min(dp[i-1][j]+1, dp[i][j-1]+1);
      if (a[i-1] == b[j-1]) {
        chmin(m, dp[i-1][j-1]);
      } else {
        chmin(m, dp[i-1][j-1]+1);
      }
      dp[i][j] = m;
    }
  }
  return dp[na][nb];
}
