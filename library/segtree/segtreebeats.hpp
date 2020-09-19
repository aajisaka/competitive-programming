#pragma once
#include "../common.hpp"

// Original: https://github.com/refine-P/KyoproLibrary/blob/master/data_structure/segment_tree_beats.hpp

// update: range {chmin, chmax, addVal, updateVal}
// query: range {max, min, sum}
// 参考: https://github.com/tjkendev/segment-tree-beats/blob/master/basic/sgt-beats-3.cpp
template <class T = ll>
struct SegmentTreeBeats {
    static const T INF;

private:
    int n;
    vector<T> maxv, smaxv, minv, sminv, sum, max_cnt, min_cnt;
    vector<T> lazy_add, lazy_val;
    vector<int> len;

    void updateNodeMax(int k, T x) {
      assert(x < maxv[k]);
      sum[k] += (x - maxv[k]) * max_cnt[k];

      if (maxv[k] == minv[k]) { // 値が1種類
        maxv[k] = minv[k] = x;
      } else if (maxv[k] == sminv[k]) { // 値が2種類
        maxv[k] = sminv[k] = x;
      } else {
        maxv[k] = x;
      }

      if (lazy_val[k] != INF && x < lazy_val[k]) {
        lazy_val[k] = x;
      }
    }

    void updateNodeMin(int k, T x) {
      assert(x > minv[k]);
      sum[k] += (x - minv[k]) * min_cnt[k];

      if (minv[k] == maxv[k]) { // 値が1種類
        minv[k] = maxv[k] = x;
      } else if (minv[k] == smaxv[k]) { // 値が2種類
        minv[k] = smaxv[k] = x;
      } else {
        minv[k] = x;
      }

      if (lazy_val[k] != INF && x > lazy_val[k]) {
        lazy_val[k] = x;
      }
    }

    void addNodeVal(int k, T x) {
      maxv[k] += x;
      if (smaxv[k] != -INF) smaxv[k] += x;
      minv[k] += x;
      if (sminv[k] != INF) sminv[k] += x;

      sum[k] += len[k] * x;
      if (lazy_val[k] != INF) {
        lazy_val[k] += x;
      } else {
        lazy_add[k] += x;
      }
    }

    void updateNodeVal(int k, T x) {
      maxv[k] = x;
      smaxv[k] = -INF;
      max_cnt[k] = len[k];

      minv[k] = x;
      sminv[k] = INF;
      min_cnt[k] = len[k];

      sum[k] = len[k] * x;
      lazy_val[k] = x;
      lazy_add[k] = 0;
    }

    void push(int k) {
      int li = (k << 1) + 1, ri = (k << 1) + 2;

      if (lazy_val[k] != INF) {
        updateNodeVal(li, lazy_val[k]);
        updateNodeVal(ri, lazy_val[k]);
        lazy_val[k] = INF;
      }

      if (lazy_add[k] != 0) {
        addNodeVal(li, lazy_add[k]);
        addNodeVal(ri, lazy_add[k]);
        lazy_add[k] = 0;
      }

      if (maxv[k] < maxv[li]) updateNodeMax(li, maxv[k]);
      if (maxv[k] < maxv[ri]) updateNodeMax(ri, maxv[k]);

      if (minv[k] > minv[li]) updateNodeMin(li, minv[k]);
      if (minv[k] > minv[ri]) updateNodeMin(ri, minv[k]);
    }

    void update(int k) {
      int li = (k << 1) + 1, ri = (k << 1) + 2;

      sum[k] = sum[li] + sum[ri];

      if (maxv[li] < maxv[ri]) {
        maxv[k] = maxv[ri];
        max_cnt[k] = max_cnt[ri];
        smaxv[k] = max(maxv[li], smaxv[ri]);
      } else if (maxv[li] > maxv[ri]) {
        maxv[k] = maxv[li];
        max_cnt[k] = max_cnt[li];
        smaxv[k] = max(smaxv[li], maxv[ri]);
      } else {
        maxv[k] = maxv[li];
        max_cnt[k] = max_cnt[li] + max_cnt[ri];
        smaxv[k] = max(smaxv[li], smaxv[ri]);
      }

      if (minv[li] > minv[ri]) {
        minv[k] = minv[ri];
        min_cnt[k] = min_cnt[ri];
        sminv[k] = min(minv[li], sminv[ri]);
      } else if (minv[li] < minv[ri]) {
        minv[k] = minv[li];
        min_cnt[k] = min_cnt[li];
        sminv[k] = min(sminv[li], minv[ri]);
      } else {
        minv[k] = minv[li];
        min_cnt[k] = min_cnt[li] + min_cnt[ri];
        sminv[k] = min(sminv[li], sminv[ri]);
      }
    }

    //区間[a, b)に対する更新
    //k:節点番号, [l, r):節点に対応する区間
    void updateMin(int a, int b, T x, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合 + something (break condition)
      if (r <= a || b <= l || x >= maxv[k]) return;
      //[a, b)が[l, r)を含む場合 + something (tag condition)
      if (a <= l && r <= b && smaxv[k] < x) {
        updateNodeMax(k, x);
      } else {
        push(k);
        updateMin(a, b, x, k * 2 + 1, l, (l + r) / 2);
        updateMin(a, b, x, k * 2 + 2, (l + r) / 2, r);
        update(k);
      }
    }

    void updateMax(int a, int b, T x, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合 + something (break condition)
      if (r <= a || b <= l || x <= minv[k]) return;
      //[a, b)が[l, r)を含む場合 + something (tag condition)
      if (a <= l && r <= b && sminv[k] > x) {
        updateNodeMin(k, x);
      } else {
        push(k);
        updateMax(a, b, x, k * 2 + 1, l, (l + r) / 2);
        updateMax(a, b, x, k * 2 + 2, (l + r) / 2, r);
        update(k);
      }
    }

    void addVal(int a, int b, T x, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合
      if (r <= a || b <= l) return;
      //[a, b)が[l, r)を含む場合
      if (a <= l && r <= b) {
        addNodeVal(k, x);
      } else {
        push(k);
        addVal(a, b, x, k * 2 + 1, l, (l + r) / 2);
        addVal(a, b, x, k * 2 + 2, (l + r) / 2, r);
        update(k);
      }
    }

    void updateVal(int a, int b, T x, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合
      if (r <= a || b <= l) return;
      //[a, b)が[l, r)を含む場合
      if (a <= l && r <= b) {
        updateNodeVal(k, x);
      } else {
        push(k);
        updateVal(a, b, x, k * 2 + 1, l, (l + r) / 2);
        updateVal(a, b, x, k * 2 + 2, (l + r) / 2, r);
        update(k);
      }
    }

    //区間[a, b)に対するクエリに答える
    //k:節点番号, [l, r):節点に対応する区間
    T queryMax(int a, int b, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合
      if (r <= a || b <= l) return -INF;
      //[a, b)が[l, r)を含む場合、節点の値
      if (a <= l && r <= b) return maxv[k];
      else {
        //二つの子をマージ
        push(k);
        T vl = queryMax(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = queryMax(a, b, k * 2 + 2, (l + r) / 2, r);
        return max(vl, vr);
      }
    }

    T queryMin(int a, int b, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合
      if (r <= a || b <= l) return INF;
      //[a, b)が[l, r)を含む場合、節点の値
      if (a <= l && r <= b) return minv[k];
      else {
        //二つの子をマージ
        push(k);
        T vl = queryMin(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = queryMin(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(vl, vr);
      }
    }

    T querySum(int a, int b, int k, int l, int r) {
      //[a, b)と[l, r)が交差しない場合
      if (r <= a || b <= l) return 0;
      //[a, b)が[l, r)を含む場合、節点の値
      if (a <= l && r <= b) return sum[k];
      else {
        //二つの子をマージ
        push(k);
        T vl = querySum(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = querySum(a, b, k * 2 + 2, (l + r) / 2, r);
        return vl + vr;
      }
    }

public:
    SegmentTreeBeats() {}

    SegmentTreeBeats(int size, T initial_value = 0) {
      n = 1;
      while (n < size) n <<= 1;

      maxv.assign(2 * n - 1, -INF);
      smaxv.assign(2 * n - 1, -INF);
      minv.assign(2 * n - 1, INF);
      sminv.assign(2 * n - 1, INF);
      sum.assign(2 * n - 1, 0);
      max_cnt.assign(2 * n - 1, 0);
      min_cnt.assign(2 * n - 1, 0);

      for (int i = 0; i < size; ++i) {
        maxv[i + n - 1] = minv[i + n - 1] = sum[i + n - 1] = initial_value;
        max_cnt[i + n - 1] = min_cnt[i + n - 1] = 1;
      }

      len.assign(2 * n - 1, 0);
      len[0] = n;
      for (int i = 0; i < n - 1; ++i) {
        len[(i<<1)+1] = len[(i<<1)+2] = (len[i] >> 1);
      }

      lazy_add.assign(2 * n - 1, 0);
      lazy_val.assign(2 * n - 1, INF);

      for (int i = n - 2; i >= 0; --i) {
        update(i);
      }
    }

    SegmentTreeBeats(const vector<ll>& v) {
      int size = v.size();
      n = 1;
      while (n < size) n <<= 1;

      maxv.assign(2 * n - 1, -INF);
      smaxv.assign(2 * n - 1, -INF);
      minv.assign(2 * n - 1, INF);
      sminv.assign(2 * n - 1, INF);
      sum.assign(2 * n - 1, 0);
      max_cnt.assign(2 * n - 1, 0);
      min_cnt.assign(2 * n - 1, 0);

      for (int i = 0; i < size; ++i) {
        maxv[i + n - 1] = minv[i + n - 1] = sum[i + n - 1] = v[i];
        max_cnt[i + n - 1] = min_cnt[i + n - 1] = 1;
      }

      len.assign(2 * n - 1, 0);
      len[0] = n;
      for (int i = 0; i < n - 1; ++i) {
        len[(i<<1)+1] = len[(i<<1)+2] = (len[i] >> 1);
      }

      lazy_add.assign(2 * n - 1, 0);
      lazy_val.assign(2 * n - 1, INF);

      for (int i = n - 2; i >= 0; --i) {
        update(i);
      }
    }

    // chmin query
    void updateMin(int a, int b, T x) {
      updateMin(a, b, x, 0, 0, n);
    }

    // chmax query
    void updateMax(int a, int b, T x) {
      updateMax(a, b, x, 0, 0, n);
    }

    void addVal(int a, int b, T x) {
      addVal(a, b, x, 0, 0, n);
    }

    void updateVal(int a, int b, T x) {
      updateVal(a, b, x, 0, 0, n);
    }

    T queryMax(int a, int b) {
      return queryMax(a, b, 0, 0, n);
    }

    T queryMin(int a, int b) {
      return queryMin(a, b, 0, 0, n);
    }

    T querySum(int a, int b) {
      return querySum(a, b, 0, 0, n);
    }
};

template<class T>
const T SegmentTreeBeats<T>::INF = numeric_limits<T>::max();
