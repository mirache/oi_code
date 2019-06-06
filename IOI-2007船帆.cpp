//bzoj-1805
#include <bits/stdc++.h>

inline void read(int&x){
	char ch=getchar();x=0;while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
}

const int N = 101000;
int tag[N<<2], ls[N<<2], rs[N<<2];
int n, H; long long ans = 0ll;

struct node {
	int h, k;
	inline void in() {read(h), read(k);}
	friend inline bool operator < (const node&A, const node&B) {return A.h < B.h;}
}p[N];

inline void down(const int x) {
	const int l = x << 1, r = l | 1;
	int&v = tag[x];
	tag[l] += v, ls[l] += v, rs[l] += v;
	tag[r] += v, ls[r] += v, rs[r] += v;
	v = 0;
}

void upd(int l, int r, int x, int L, int R) {
	if(L <= l and r <= R) return ++tag[x], ++ls[x], ++rs[x], void();
	int mid = l + r >> 1; if(tag[x]) down(x);
	if(mid < R) upd(mid+1, r, x<<1|1, L, R);
	if(L <= mid) upd(l, mid, x<<1, L, R);
	ls[x] = ls[x<<1], rs[x] = rs[x<<1|1];
}

int get_sgl(int l, int r, int x, int ps) {
	if(l == r) return tag[x];
	int mid = l + r >> 1; if(tag[x]) down(x);
	if(ps <= mid) return get_sgl(l, mid, x<<1, ps);
	else return get_sgl(mid+1, r, x<<1|1, ps);
}

void get_all(int l, int r, int x) {
	if(l == r) return ans += (long long)tag[x] * (tag[x]-1), void();
	int mid = l + r >> 1; if(tag[x]) down(x);
	get_all(l, mid, x<<1);
	get_all(mid+1, r, x<<1|1);
}

int get_lpos(int l, int r, int x, int R, int vl) {
	if(R < l or ls[x] < vl or rs[x] > vl) return 0;
	if(l == r) return l;
	int mid = l + r >> 1, res = 0; if(tag[x]) down(x);
	if(res = get_lpos(l, mid, x<<1, R, vl)) return res;
	return get_lpos(mid+1, r, x<<1|1, R, vl);
}

int get_rpos(int l, int r, int x, int L, int vl) {
	if(r < L or ls[x] < vl or rs[x] > vl) return 0;
	if(l == r) return l;
	int mid = l + r >> 1, res = 0; if(tag[x]) down(x);
	if(res = get_rpos(mid+1, r, x<<1|1, L, vl)) return res;
	return get_rpos(l, mid, x<<1, L, vl);
}

int main() {
	read(n);
	for(int i=1;i<=n;++i)
		p[i].in(), H = std::max(H, p[i].h);
	std::sort(p+1,p+n+1);
	
	for(int i=1;i<=n;++i) {
		int&res = p[i].k;
		int x = get_sgl(1,H,1,p[i].h-res+1);
		int rps = get_rpos(1,H,1,p[i].h-res+1,x);
		int lps = get_lpos(1,H,1,p[i].h-res+1,x);
		rps = std::min(rps, p[i].h);
		if(rps < p[i].h) upd(1,H,1,rps+1,p[i].h);
		res -= p[i].h - rps;
		upd(1,H,1,lps,lps+res-1);
	}
	
	get_all(1,H,1);
	printf("%lld\n", ans >> 1);
	return 0;
}
