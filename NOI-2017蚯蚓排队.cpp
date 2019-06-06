//bzoj-4943
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int T = 14233333;

namespace hs {
	int nxt[T], ln[T], v[T]; ull ky[T];
	int head[T], _;
	inline void upd(int x, int l, ull y, int dlt) {
		for(int i=head[x];i;i=nxt[i])
			if(ln[i] == l and ky[i] == y) {v[i] += dlt; return ;}
		v[++_] = dlt, ky[_] = y, ln[_] = l, nxt[_] = head[x], head[x] = _;
	}
	inline int get(int x, int l, ull y) {
		for(int i=head[x];i;i=nxt[i])
			if(ln[i] == l and ky[i] == y) return v[i];
		return 0;
	}
}

char str[T];
int s[T];
int he, ta;

const int bs1 = 11;
const ull bs2 = 31;

int pw1[T], m1;
ull pw2[T], m2;

inline void clr() {he = 1, ta = m1 = m2 = 0;}

const int N = 201000;
int fr[N], ba[N], dig[N];

inline void ins(int x) {
	s[++ta] = x;
	m1 = (m1 * bs1 + x)%T,
	m2 = (m2 * bs2 + x);
}

inline void ers() {
	m1 = (m1 - (ll)pw1[ta-he] * s[he] + (ll)T * T)%T,
	m2 = (m2 - pw2[ta-he] * s[he]);
	++he;
}

int s1[53], t1;
int s2[53], t2;

int main() {
	int n, Q;
	read(n), read(Q);
	pw1[0] = pw2[0] = 1;
	for(int i=1;i<=n*6;++i) {
		pw1[i] = (pw1[i-1] * bs1)%T;
		pw2[i] = (pw2[i-1] * bs2);
	}
	for(int i=1;i<=n;++i)
		read(dig[i]), hs::upd(dig[i], 1, dig[i], 1);
	
	int op, x, y;
	while(Q--) {
		read(op);
		if(op == 1) {
			read(x), read(y);
			s1[t1 = 1] = x; for(int i=x;t1 < 50 and fr[i];i=fr[i]) s1[++t1] = fr[i];
			s2[t2 = 1] = y; for(int i=y;t2 < 50 and ba[i];i=ba[i]) s2[++t2] = ba[i];
			for(int i=1;i<=t1;++i) {
				clr();
				for(int j=i;j;--j) ins(dig[s1[j]]);
				for(int j=1;j<=t2 and i+j<=50;++j) {
					ins(dig[s2[j]]);
					hs::upd(m1, ta-he+1, m2, 1);
				}
			}
			ba[x] = y, fr[y] = x;
			continue;
		}
		if(op == 2) {
			read(x), y = ba[x];
			s1[t1 = 1] = x; for(int i=x;t1 < 50 and fr[i];i=fr[i]) s1[++t1] = fr[i];
			s2[t2 = 1] = y; for(int i=y;t2 < 50 and ba[i];i=ba[i]) s2[++t2] = ba[i];
			for(int i=1;i<=t1;++i) {
				clr();
				for(int j=i;j;--j) ins(dig[s1[j]]);
				for(int j=1;j<=t2 and i+j<=50;++j) {
					ins(dig[s2[j]]);
					hs::upd(m1, ta-he+1, m2, -1);
				}
			}
			ba[x] = fr[y] = 0;
			continue;
		}
		scanf("%s",str+1), read(y);
		const int p = 998244353;
		int len = strlen(str+1);
		ll ans = 1; clr();
		for(int i=1;i<y;++i) ins(str[i] - '0');
		for(int i=y;i<=len;++i)
			ins(str[i] - '0'),
			ans = ans * hs::get(m1, y, m2)%p,
			ers();
		printf("%lld\n",ans);
	}
	return 0;
}
