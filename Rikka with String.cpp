//hihocoder-1413
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 601000;
int ch[N][26], stp[N], pre[N];
int lft[N], rit[N], T[N], tpy[N];
int lst, tot, n;
char s[N];

ll d1[N], d2[N], Ans;

void ins(int x){
	int p = lst, np = ++tot; lst = np;
	stp[np] = stp[p] + 1;
	while(p and !ch[p][x]) ch[p][x] = np, p = pre[p];
	if(!p) pre[np] = 1;
	else {
		int q = ch[p][x];
		if(stp[q] == stp[p] + 1) pre[np] = q;
		else {
			int nq = ++tot; stp[nq] = stp[p] + 1;
			for(int i=0;i<26;++i) ch[nq][i] = ch[q][i];
			pre[nq] = pre[q], pre[q] = pre[np] = nq;
			while(ch[p][x] == q) ch[p][x] = nq, p = pre[p];
		}
	}
}

int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	lst = tot = 1;
	for(int i=1;i<=n;++i) {
		ins(s[i]-'a');
		lft[lst] = rit[lst] = i;
	}
	
	for(int i=1;i<=tot;++i) if(!lft[i]) lft[i] = 1e9, rit[i] = 0;
	for(int i=1;i<=tot;++i) ++T[stp[i]];
	for(int i=1;i<=tot;++i) T[i] += T[i-1];
	for(int i=tot;i;--i) tpy[T[stp[i]]--] = i;
	for(int i=tot,x;i;--i) {
		x = tpy[i];
		lft[pre[x]] = min(lft[pre[x]], lft[x]);
		rit[pre[x]] = max(rit[pre[x]], rit[x]);
		Ans += stp[x] - stp[pre[x]];
	}
	
	int L, R, len;
	for(int x=1;x<=tot;++x) {
		L = rit[x] - stp[x] + 1;
		R = min(rit[x] - stp[pre[x]], lft[x]);
		len = R - L + 1;
		if(L <= R) ++d2[L], d2[R+1] -= len + 1, d2[R+2] += len;
		L = R + 1, R = lft[x];
		if(L <= R) d1[L] += len, d1[R+1] -= len;
	}
	
	for(int i=1;i<=n;++i) d2[i] += d2[i-1], d1[i] += d2[i];
	for(int i=1;i<=n;++i) d1[i] += d1[i-1];
	for(int i=1;i<=n;++i) {
		ll ans = (ll)i * (n-i+1);
		ans += Ans - d1[i];
		printf("%lld ",ans);
	}
	putchar(10);
	return 0;
}
