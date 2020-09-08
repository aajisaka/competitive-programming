// Original: https://img.atcoder.jp/practice2/ac-library.zip

#include <algorithm>
#include <cassert>
#include <vector>

/*
// Sample Usages (copy-and-paste it!)

// RangeSumQuery
auto f = [](ll a, ll b) { return a+b; };
auto e = []() { return 0; };

// RangeMaximumQuery:
auto f = [](ll a, ll b) { return max(a, b); };
auto e = []() { return LLONG_MIN/2 };

// RangeMinimumQuery:
auto f = [](ll a, ll b) { return min(a, b); };
auto e = []() { return LLONG_MAX/2 };

auto seg = segtree<ll, f, e>(v);
*/

template<class S, S (*op)(S, S), S (*e)()>
struct segtree {
public:
    segtree() : segtree(0) {}

    segtree(int n) : segtree(std::vector<S>(n, e())) {}

    segtree(const std::vector<S> &v) : _n(int(v.size())) {
      log = 0;
      while((1U << log) < (unsigned int)(_n)) log++; // ceil_pow2(_n)
      size = 1 << log;
      d = std::vector<S>(2 * size, e());
      for (int i = 0; i < _n; i++) d[size + i] = v[i];
      for (int i = size - 1; i >= 1; i--) {
        update(i);
      }
    }

    void set(int p, S x) {
      assert(0 <= p && p < _n);
      p += size;
      d[p] = x;
      for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
      assert(0 <= p && p < _n);
      return d[p + size];
    }

    S prod(int l, int r) {
      assert(0 <= l && l <= r && r <= _n);
      S sml = e(), smr = e();
      l += size;
      r += size;

      while (l < r) {
        if (l & 1) sml = op(sml, d[l++]);
        if (r & 1) smr = op(d[--r], smr);
        l >>= 1;
        r >>= 1;
      }
      return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template<bool (*f)(S)>
    int max_right(int l) {
      return max_right(l, [](S x) { return f(x); });
    }

    // return the smallest r such that f(op(a[l], ... ,a[r-1])) become false
    // f(e()) must return true
    template<class F>
    int max_right(int l, F f) {
      assert(0 <= l && l <= _n);
      assert(f(e()));
      if (l == _n) return _n;
      l += size;
      S sm = e();
      do {
        while (l % 2 == 0) l >>= 1;
        if (!f(op(sm, d[l]))) {
          while (l < size) {
            l = (2 * l);
            if (f(op(sm, d[l]))) {
              sm = op(sm, d[l]);
              l++;
            }
          }
          return l - size;
        }
        sm = op(sm, d[l]);
        l++;
      } while ((l & -l) != l);
      return _n;
    }

    template<bool (*f)(S)>
    int min_left(int r) {
      return min_left(r, [](S x) { return f(x); });
    }

    // return the largest l such that f(op(a[l], ... ,a[r-1])) become false
    // f(e()) must return true
    template<class F>
    int min_left(int r, F f) {
      assert(0 <= r && r <= _n);
      assert(f(e()));
      if (r == 0) return 0;
      r += size;
      S sm = e();
      do {
        r--;
        while (r > 1 && (r % 2)) r >>= 1;
        if (!f(op(d[r], sm))) {
          while (r < size) {
            r = (2 * r + 1);
            if (f(op(d[r], sm))) {
              sm = op(d[r], sm);
              r--;
            }
          }
          return r + 1 - size;
        }
        sm = op(d[r], sm);
      } while ((r & -r) != r);
      return 0;
    }

private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};