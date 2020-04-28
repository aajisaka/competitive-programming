/*
  The implementation of Miller-Rabin Test with C++
  varified with ALDS1_1_C

  http://joisino.hatenablog.com/entry/2017/08/03/210000

  Copyright (c) 2017 joisino
  Released under the MIT license
  http://opensource.org/licenses/mit-license.php
 */

// 64bit support
// Verify: https://yukicoder.me/submissions/472283
struct Miller64 {
    const vector<__uint128_t> v = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}; // < 3,317,044,064,679,887,385,961,981
    __uint128_t modpow(__uint128_t x, __uint128_t k, __uint128_t m){
      __uint128_t res = 1;
      while( k ){
        if( k & 1 ){
          res = res * x % m;
        }
        k /= 2;
        x = x * x % m;
      }
      return res;
    }
    // check if n is prime
    bool check(__uint128_t n){
      if( n < 2 ){
        return false;
      }
      __uint128_t d = n - 1;
      __uint128_t s = 0;
      while( d % 2 == 0 ){
        d /= 2;
        s++;
      }
      for(__uint128_t a : v ){
        if( a == n ){
          return true;
        }
        if( modpow( a , d , n ) != 1 ){
          bool ok = true;
          for(__uint128_t r = 0; r < s; r++ ){
            if( modpow( a, d * (1LL << r), n ) == n-1 ){
              ok = false;
              break;
            }
          }
          if( ok ){
            return false;
          }
        }
      }
      return true;
    }
};
