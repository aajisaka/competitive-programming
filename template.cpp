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
constexpr double PI = 3.14159265358979323846;
mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);


}