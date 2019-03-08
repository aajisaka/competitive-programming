#include<vector>
#include<string>

using namespace std;

// return A[i]: The length of the longest substring starting from S[i]
// which is also a prefix of S. Obviously, A[0] = S.size();
void Zalgorithm(vector<int>& A, string& S) {
  A[0] = S.size();
  int i = 1, j = 0;
  while (i < S.size()) {
    while (i+j < S.size() && S[j] == S[i+j]) ++j;
    A[i] = j;
    if (j == 0) { ++i; continue;}
    int k = 1;
    while (i+k < S.size() && k+A[k] < j) A[i+k] = A[k], ++k;
    i += k; j -= k;
  }
}