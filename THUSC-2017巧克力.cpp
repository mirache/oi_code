//loj-2977
#include <bits/stdc++.h>
using namespace std;

inline void cmin(int&x, const int y) {x = x < y ? x : y;}

const int bs = 10000;
const int N = 251;
int head[N], id[N][N];
int c[N], C[N], hs[N];
int v[N], srt[N], val[N];
int n, m, k, U, L, _, idc;

struct Edge {int v,nxt;} a[N*8];
inline void add(int x,int y) {a[++_].v = y, a[_].nxt = head[x], head[x] = _;}

int q[N*N], he, ta;
bool inq[N*N];

void Bellman(int*arr) {
	static int x;
	while(he <= ta) {
		inq[x = q[he++]] = false;
		for(int i=head[x];i;i=a[i].nxt)
			if(arr[a[i].v] > arr[x] + val[a[i].v]) {
				arr[a[i].v] = arr[x] + val[a[i].v];
				if(!inq[a[i].v]) inq[q[++ta] = a[i].v] = true;
			}
	}
}

int f[33][N];

int calc(int alpha) {
	for(int i=1;i<=U;++i) {
		for(int s = 0; s < (1 << k); ++ s) f[s][i] = 1e9;
		if(c[i] == -1) {val[i] = 1e9; continue;}
		if(v[i] < alpha) val[i] = bs - 1;
		else val[i] = bs + 1;
		f[1<<c[i]][i] = val[i];
	}
	
	for(int S = 1; S < (1 << k); ++ S) {
		for(int s = S & (S-1); s; s = (s-1) & S)
			for(int i=1;i<=U;++i) cmin(f[S][i], f[s][i] + f[S^s][i] - val[i]);
		
		he = 1, ta = 0;
		for(int i=1;i<=U;++i)
			if(f[S][i] < 1e9)
				inq[q[++ta] = i] = true;
		
		Bellman(f[S]);
	}
	
	int ans = 1e9;
	for(int i=1;i<=U;++i)
		ans = min(ans, f[(1<<k)-1][i]);
	return ans;
}

int solve() {
	const int cnt = (calc(1) + 500) / bs;
	int l = 1, r = L, mid, tmp, res = 1e7;
	while(l <= r) {
		mid = l + r >> 1, tmp = (calc(mid) + 500) % bs - 500;
		if(tmp > 0) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res + cnt * bs;
}

void work() {
	scanf("%d%d%d",&n,&m,&k), idc = _ = 0, U = n * m;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) head[id[i][j] = ++idc] = 0;
	for(int i=1;i<=U;++i) scanf("%d",C+i);
	for(int i=1;i<=U;++i) scanf("%d",v+i), srt[i] = v[i];
	sort(srt+1,srt+U+1); L = unique(srt+1,srt+U+1)-srt-1;
	for(int i=1;i<=U;++i) v[i] = lower_bound(srt+1,srt+L+1,v[i])-srt;
	
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		if(i != 1) add(id[i][j], id[i-1][j]); if(j != 1) add(id[i][j], id[i][j-1]);
		if(i != n) add(id[i][j], id[i+1][j]); if(j != m) add(id[i][j], id[i][j+1]);
	}
	
	int ct = 160, ans = 1e9;
	while(ct--) {
		for(int i=1;i<=U;++i) hs[i] = rand()%k;
		for(int i=1;i<=U;++i)
			if(C[i] == -1) c[i] = -1;
			else c[i] = hs[C[i]];
		ans = min(ans, solve());
	}
	printf("%d %d\n",ans/bs,srt[ans%bs]);
}

int main() {
	srand(time(0));
	int T; scanf("%d",&T);
	while(T--) work();
	return 0;
}
