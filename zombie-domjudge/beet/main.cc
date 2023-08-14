#include <bits/stdc++.h>
using namespace std;

using Int = long long;
const char newl = '\n';

template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
template<typename T> void drop(const T &x){cout<<x<<endl;exit(0);}
template<typename T=int>
vector<T> read(size_t n){
  vector<T> ts(n);
  for(size_t i=0;i<n;i++) cin>>ts[i];
  return ts;
}

struct Precision{
  Precision(){
    cout<<fixed<<setprecision(12);
  }
}precision_beet;

//INSERT ABOVE HERE
const int MAX = 1024;
int xs[MAX],ys[MAX],vx[MAX],vy[MAX];

using D = double;
const D INF = 1e18;
const D EPS = 1e-15;

#define equals(a,b) (fabs((a)-(b))<EPS)

struct Point{
  double x,y;
  Point(){}
  Point(double x,double y):x(x),y(y){}
  Point operator+(Point p) {return Point(x+p.x,y+p.y);}
  Point operator-(Point p) {return Point(x-p.x,y-p.y);}
  Point operator*(double k){return Point(x*k,y*k);}
  Point operator/(double k){return Point(x/k,y/k);}
  double norm(){return x*x+y*y;}
  double abs(){return sqrt(norm());}

  bool operator<(const Point &p) const{
    return x!=p.x?x<p.x:y<p.y;
    //grid-point only
    //return !equals(x,p.x)?x<p.x:!equals(y,p.y)?y<p.y:0;
  }

  bool operator==(const Point &p) const{
    return fabs(x-p.x)<EPS and fabs(y-p.y)<EPS;
  }
};

typedef Point Vector;
typedef vector<Point> Polygon;

struct Segment{
  Point p1,p2;
  Segment(){}
  Segment(Point p1, Point p2):p1(p1),p2(p2){}
};
typedef Segment Line;

struct Circle{
  Point c;
  double r;
  Circle(){}
  Circle(Point c,double r):c(c),r(r){}
};



double norm(Vector a){
  return a.x*a.x+a.y*a.y;
}

double abs(Vector a){
  return sqrt(norm(a));
}

double dot(Vector a,Vector b){
  return a.x*b.x+a.y*b.y;
}

double cross(Vector a,Vector b){
  return a.x*b.y-a.y*b.x;
}

Point orth(Point p){return Point(-p.y,p.x);}

bool isOrthogonal(Vector a,Vector b){
  return equals(dot(a,b),0.0);
}

bool isOrthogonal(Point a1,Point a2,Point b1,Point b2){
  return isOrthogonal(a1-a2,b1-b2);
}

bool isOrthogonal(Segment s1,Segment s2){
  return equals(dot(s1.p2-s1.p1,s2.p2-s2.p1),0.0);
}

bool isParallel(Vector a,Vector b){
  return equals(cross(a,b),0.0);
}

bool isParallel(Point a1,Point a2,Point b1,Point b2){
  return isParallel(a1-a2,b1-b2);
}

bool isParallel(Segment s1,Segment s2){
  return equals(cross(s1.p2-s1.p1,s2.p2-s2.p1),0.0);
}

Point project(Segment s,Point p){
  Vector base=s.p2-s.p1;
  double r=dot(p-s.p1,base)/norm(base);
  return s.p1+base*r;
}

double getDistanceLP(Line l,Point p){
  return fabs(cross(l.p2-l.p1,p-l.p1)/abs(l.p2-l.p1));
}

Polygon getCrossPointCL(Circle c,Line l){
  Polygon ps;
  Point pr=project(l,c.c);
  Vector e=(l.p2-l.p1)/abs(l.p2-l.p1);
  if(equals(getDistanceLP(l,c.c),c.r)){
    ps.emplace_back(pr);
    return ps;
  }
  double base=sqrt(c.r*c.r-norm(pr-c.c));
  ps.emplace_back(pr+e*base);
  ps.emplace_back(pr-e*base);
  return ps;
}


signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n,d;
  cin>>n>>d;

  for(int i=0;i<=n;i++)
    cin>>xs[i]>>ys[i]>>vx[i]>>vy[i];

  vector<int> used(n+1,0);
  vector<D> dist(n+1,INF);
  dist[0]=0;

  for(int t=0;t<=n;t++){
    int v=-1;
    for(int i=0;i<=n;i++){
      if(used[i]) continue;
      if(v<0 or dist[v]>dist[i]) v=i;
    }
    if(v<0) break;
    used[v]=1;
    for(int u=0;u<=n;u++){
      Vector vv(vx[u]-vx[v],vy[u]-vy[v]);

      D lb=INF,ub=-1;

      if(vv==Vector(0,0)){
        if(abs(Point(xs[u],ys[u])-Point(xs[v],ys[v]))<=d+EPS){
          lb=0;
          ub=INF;
        }
      }else{
        Line l(Point(xs[u],ys[u]),Point(xs[u],ys[u])+vv);
        if(getDistanceLP(l,Point(xs[v],ys[v]))>d+EPS) continue;

        auto ps=getCrossPointCL(Circle(Point(xs[v],ys[v]),d),l);

        auto get_time=[&](Point p){
          Vector uu=p-Point(xs[u],ys[u]);
          return abs(uu)/abs(vv)*(dot(uu,vv)>0?+1:-1);
        };

        for(auto p:ps){
          chmin(lb,get_time(p));
          chmax(ub,get_time(p));
        }
        // cout<<v<<' '<<u<<':'<<lb<<' '<<ub<<endl;
      }

      if(ub<dist[v]) continue;
      chmin(dist[u],max(dist[v],lb));
    }
  }

  for(int i=1;i<=n;i++){
    if(dist[i]==INF) cout<<-1<<newl;
    else cout<<dist[i]<<newl;
  }
  return 0;
}
