// Problem: Zombie
// Author: Darsein
// Expected Status: AC
// Complexity: O(N^2)

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long int;
using interval = pair<long double, long double>;

const long double INF = 1e18;
const long double EPS = 1e-9;

interval solveQuadEquation(ll a, ll b, ll c) {
  if (a == 0) {
    if (b == 0) {
      return c <= 0 ? interval(0, INF) : interval(-1, -1);
    } else if (b < 0) {
      return interval(max(0.0L, (long double)(-c) / b), INF); 
    } else {
      long double ans = (long double)(-c) / b;
      return ans > -EPS ? interval(0.0L, ans) : interval(-1, -1); 
    }
  }
  long double da = a, db = b, dc = c;
  long double s = db * db - 4 * da * dc;
  if (s < 0) {
    return a < 0 ? interval(0, INF) : interval(-1, -1);
  }
  long double l = (-db - sqrt(s)) / 2 / da, r = (-db + sqrt(s)) / 2 / da;
  if (r < 0) {
    return interval(-1, -1);
  }
  return interval(max(0.0L, l), r);
}

vector<long double> solve(ll n, ll d, vector<ll> x, vector<ll> y,
			  vector<ll> vx, vector<ll> vy) {
  vector<long double> ans(n, INF);
  ans[0] = 0;

  vector< vector<interval> > timing(n, vector<interval>(n, interval(-1, -1)));
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      ll x1 = x[i], y1 = y[i], vx1 = vx[i], vy1 = vy[i];
      ll x2 = x[j], y2 = y[j], vx2 = vx[j], vy2 = vy[j];
      ll X = x1 - x2, Y = y1 - y2, VX = vx1 - vx2, VY = vy1 - vy2;
      ll a = VX * VX + VY * VY, b = 2 * (X * VX + Y * VY), c = X * X + Y * Y - d * d;
      timing[i][j] = timing[j][i] = solveQuadEquation(a, b, c);
    }
  }

  vector<bool> used(n, false);
  while (true) {
    long double t = INF;
    int v = -1;
    for (int i = 0; i < n; ++i) {
      if (!used[i] && ans[i] < t) {
	v = i;
	t = ans[i];
      }
    }
    if (v < 0) {
      break;
    }

    used[v] = true;
    for (int i = 0; i < n; ++i) {
      if (timing[v][i].second < t - EPS) {
	continue;
      }
      long double nt = max(t, timing[v][i].first);
      ans[i] = min(ans[i], nt);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (abs(ans[i] - INF) < EPS) {
      ans[i] = -1;
    }
  }    
  return ans;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  ll n, d;
  cin >> n >> d;
  vector<ll> x(n+1), y(n+1), vx(n+1), vy(n+1);
  for (int i = 0; i <= n; ++i) {
    cin >> x[i] >> y[i] >> vx[i] >> vy[i];
  }

  vector<long double> ans = solve(n+1, d, x, y, vx, vy);
  for (int i = 0; i < n; ++i) {
    cout << fixed << setprecision(10) << ans[i + 1] << endl;
  }
}
