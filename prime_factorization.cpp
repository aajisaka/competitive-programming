#include<map>
using namespace std;

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