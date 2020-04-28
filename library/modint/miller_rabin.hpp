/*
  The implementation of Miller-Rabin Test with C++
  varified with ALDS1_1_C

  http://joisino.hatenablog.com/entry/2017/08/03/210000

  Copyright (c) 2017 joisino
  Released under the MIT license
  http://opensource.org/licenses/mit-license.php
 */
struct Miller {
    const vector<long long> v = { 2 , 7 , 61 }; // < 4,759,123,141
    long long modpow( long long x, long long k, long long m ){
      long long res = 1;
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
    bool check( long long n ){
      if( n < 2 ){
        return false;
      }
      long long d = n - 1;
      long long s = 0;
      while( d % 2 == 0 ){
        d /= 2;
        s++;
      }
      for( long long a : v ){
        if( a == n ){
          return true;
        }
        if( modpow( a , d , n ) != 1 ){
          bool ok = true;
          for( long long r = 0; r < s; r++ ){
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
