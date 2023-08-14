#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }


using Double = long double;
constexpr Double INF = 1e+100L;
constexpr Double EPS = 1e-12L;

int N;
Int D;
vector<Int> X, Y, Z, W;

Double calc(int u, int v, Double t0) {
  const Int x = X[v] - X[u];
  const Int y = Y[v] - Y[u];
  const Int z = Z[v] - Z[u];
  const Int w = W[v] - W[u];
// cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
  // a t^2 + 2 b t + c <= 0
  const Int a = z * z + w * w;
  const Int b = x * z + y * w;
  const Int c = x * x + y * y - D * D;
  if ((a * t0 + 2.0L * b) * t0 + c <= EPS) {
    return t0;
  }
  if (a == 0) {
    assert(b == 0);
    return INF;
  }
  assert(a > 0);
  if ((__int128)b * b - (__int128)a * c < 0) {
    return INF;
  }
  // -b / a < t0
  if ((Double)-b / a < t0) {
    return INF;
  }
  Double delta = (Double)b * b - (Double)a * c;
  delta = sqrt(max(delta, 0.0L));
  const Double t = (-b - delta) / a;
// cerr<<"  "<<a<<" "<<b<<" "<<c<<": "<<t<<endl;
  assert(t > t0);
  return t;
}

int main() {
  for (; ~scanf("%d%lld", &N, &D); ) {
    ++N;
    X.resize(N);
    Y.resize(N);
    Z.resize(N);
    W.resize(N);
    for (int u = 0; u < N; ++u) {
      scanf("%lld%lld%lld%lld", &X[u], &Y[u], &Z[u], &W[u]);
    }
    
    vector<Double> ans(N, INF);
    vector<int> vis(N, 0);
    ans[0] = 0.0L;
    for (; ; ) {
      int um = -1;
      for (int u = 0; u < N; ++u) if (!vis[u] && ans[u] < INF) {
        if (!~um || ans[um] > ans[u]) {
          um = u;
        }
      }
      if (!~um) {
        break;
      }
      vis[um] = true;
      for (int v = 0; v < N; ++v) if (!vis[v]) {
        chmin(ans[v], calc(um, v, ans[um]));
      }
    }
    
    for (int u = 1; u < N; ++u) {
      if (vis[u]) {
        printf("%.12Lf\n", ans[u]);
      } else {
        puts("-1");
      }
    }
  }
  return 0;
}
