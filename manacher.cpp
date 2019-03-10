#include<vector>
#include<string>

using namespace std;

// return R[i]: The length of the longest palindrome where
// the center is S[i]. Obviously, R[0] = R[S.size()] = 1;
// If you would like to find palindromes whose length are even,
// add dummy characters in S.
void manacher(string& S, vector<int>& R) {
  int i = 0, j = 0;
  while (i < S.size()) {
    while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
    R[i] = j;
    int k = 1;
    while (i-k >= 0 && i+k < S.size() && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
    i += k; j -= k;
  }
}
