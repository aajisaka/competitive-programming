#include<map>
using namespace std;
using ll = long long;

void prime_factorization(long long a, map<long long, int>& mp) {
  for(long long i=2; i*i<=a; i++) {
    while (a%i == 0) {
      mp[i]++;
      a /= i;
    }
  }
  if (a > 1) {
    mp[a]++;
  }
}

map<ll, int> prime_factorization(ll a) {
  map<ll, int> mp;
  for(ll i=2; i*i<=a; i++) {
    while (a%i == 0) { mp[i]++; a /= i; }
  }
  if (a > 1) mp[a]++;
  return mp;
}