//https://csacademy.com/contest/archive/task/randomly-permuted-costs/
#include <bits/stdc++.h>
using namespace std;
#define For(x,y) for(int x=1;x<=y;++x)

const double eps = 1e-8;
const int N = 1010;
struct Edge {int v, nxt; double w;} a[N+N];
int head[N], Head[N], _;
int deg[N], q[N];
double f[N];
int n, m, S, T;

inline void ad() {
	static int x, y; static double w; scanf("%d%d%lf",&x,&y,&w);
	a[++_].v = y, a[_].w = w, a[_].nxt = head[x], head[x] = _;
	a[++_].v = x, a[_].nxt = Head[y], Head[y] = _;
	if(x != y) ++deg[x];
}

typedef pair<double,int> pr;
pr brr[N*N], arr[N*N], crr[N*N];
int arc, brc, crc;

double ew[N*N]; int _ew;
double ot[N*N]; int _ot;
int ret[N], self_circle;

void init(int x) {
	arc = _ew = _ot = self_circle = 0;
	for(int i=head[x];i;i=a[i].nxt) {
		ew[++_ew] = a[i].w;
		if(a[i].v == x) ++self_circle;
		else ot[++_ot] = f[a[i].v];
	}
	sort(ew + 1, ew + _ew + 1);
	sort(ot + 1, ot + _ot + 1);
	For(i, _ew) For(j, _ot)
		arr[++arc] = make_pair(ew[i] + ot[j], j);
	sort(arr + 1, arr + arc + 1);
}

double calc(int x, double sw) {
	f[x] = sw, brc = 0;
	int t = 0; while(t < _ot and ot[t+1] < sw) ++t;
	For(i, _ew) For(j, self_circle)
		brr[++brc] = make_pair(ew[i] + sw, t + j);
	For(i, arc) if(arr[i].second > t) arr[i].second += self_circle;
	merge(arr+1, arr+arc+1, brr+1, brr+brc+1, crr+1);
	For(i, arc) if(arr[i].second > t) arr[i].second -= self_circle;
	
	crc = arc + brc;
	
	For(i, _ew) ret[i] = _ew;
	double coe = 1, ans = 0;
	for(int i=1, id; i <= crc and coe > eps; ++i) {
		ans += coe * (crr[i].first - crr[i-1].first);
		id = crr[i].second;
		coe /= ret[id] - (id - 1);
		--ret[id];
		coe *= ret[id] - (id - 1);
	}
	return ans;
}

void solve(int x) {
	init(x);
	if(!_ot) return f[x] = 1e9, void();
	double l = calc(x, 0), r = calc(x, 1e7), mid, res;
	while(l + eps < r) {
		mid = 0.5 * (l + r);
		res = calc(x, mid);
		if(res > mid) l = res;
		else r = res;
	}
	f[x] = l;
}

int main() {
	scanf("%d%d%d%d",&n,&m,&S,&T);
	while(m--) ad();
	
	int he = 1, ta = 0;
	For(i, n) {
		if(!deg[i]) q[++ta] = i;
		f[i] = 1e9;
	}
	while(he <= ta) {
		int x = q[he++];
		for(int i=Head[x];i;i=a[i].nxt)
			if(!(--deg[a[i].v]))
				q[++ta] = a[i].v;
		if(x == T) f[x] = 0;
		else solve(x);
	}
	if(f[S] < 1e8) printf("%.7lf\n",f[S]);
	else puts("-1");
	return 0;
}
