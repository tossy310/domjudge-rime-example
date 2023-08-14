// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

using fltype = long double;
using itype = long long;

fltype INF = 1e100;

template<typename T>
struct Point {
    T x, y;
    Point() {}
    Point(T x, T y): x(x), y(y) {}
};


vector<fltype> quadratic_equation(itype a, itype b, itype c) {
    assert(abs(a) <= (1 << 30) && abs(b) <= (1LL << 31) && abs(c) <= (1 << 30));
    if (a) {
        if (a < 0) {
            a = -a;
            b = -b;
            c = -c;
        }
        itype d = b * b - 4 * a * c;
        if (d > 0) {
            if (b > 0) {
                fltype x1 = (-b - sqrt((fltype)d)) / (2 * a);
                fltype x2 = c / (fltype)a / x1;
                assert(x1 <= x2);
                return { x1, x2 };
            }
            else {
                fltype x2 = (-b + sqrt((fltype)d)) / (2 * a);
                fltype x1 = c / (fltype)a / x2;
                assert(x1 <= x2);
                return { x1, x2 };
            }
        }
        else if (d == 0) {
            return { -b / (fltype)(2 * a), -b / (fltype)(2 * a) };
        }
        else {
            return {};
        }
    }
    else if (b) {
        return { -c / (fltype)b, -c / (fltype)b };
    }
    else if (c > 0) {
        return {};
    }
    else {
        return { -INF, INF };
    }
}


vector<fltype> intersect_segment(const Point<itype>& p, const Point<itype>& v, itype d) {
    itype a = v.x * v.x + v.y * v.y;
    itype b = 2 * (p.x * v.x + p.y * v.y);
    itype c = p.x * p.x + p.y * p.y - d * d;
    return quadratic_equation(a, b, c);
}

vector<fltype> intersect_segment(const Point<itype>& p1, const Point<itype>& v1, const Point<itype>& p2, const Point<itype>& v2, itype d) {
    Point<itype> p(p2.x - p1.x, p2.y - p1.y);
    Point<itype> v(v2.x - v1.x, v2.y - v1.y);
    return intersect_segment(p, v, d);
}


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    itype d;
    cin >> n >> d;
    ++n;
    vector<Point<itype>> p(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y >> v[i].x >> v[i].y;
    }
    vector<fltype> dist(n, INF);
    vector<bool> used(n);
    dist[0] = 0;
    while (true) {
        int s = -1;
        fltype mi = INF;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && mi > dist[i]) {
                mi = dist[i];
                s = i;
            }
        }
        if (s == -1) break;
        used[s] = true;
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            vector<fltype> iss = intersect_segment(p[s], v[s], p[i], v[i], d);
            if (iss.size() == 0) continue;
            assert(iss.size() == 2);
            vector<fltype> seg = { max(dist[s], iss[0]), iss[1] };
            if (seg[0] <= seg[1] + 1e-9) {
                dist[i] = min(dist[i], seg[0]);
            }
        }
    }
    cout << setprecision(16);
    for (int i = 1; i < n; ++i) {
        if (dist[i] == INF) {
            cout << -1 << '\n';
        }
        else {
            cout << dist[i] << '\n';
        }
    }

    return 0;
}
