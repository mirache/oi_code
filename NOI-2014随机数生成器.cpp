//bzoj-3671
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 5011, M = N*N;
int s[M];
short X[M],Y[M];
int n,m,T;

void hola() {
	int Q;
	register int a, b, c, d, x0, x1;
	read(x0), read(a), read(b), read(c), read(d);
	read(n), read(m), read(Q), T = n * m;
	for(register int i=1;i<=T;++i) {
		s[i] = i;
		x1 = ((ll)a * x0%d * x0 + (ll)b * x0 + c)%d;
		swap(s[i], s[x1%i+1]), x0 = x1;
	}
	while(Q--) read(a), read(b), swap(s[a], s[b]);
	for(int i=1,ii=0;i<=n;++i)
	for(int j=1;j<=m;++j)
		++ii, X[s[ii]] = i, Y[s[ii]] = j;
}

bitset <M> vs;
int Ans[N+N];

int main() {
	hola();
	
	register int x, y;
	for(register int t=1;t<=T;++t)
		if(!vs[t]) {
			Ans[++Ans[0]] = t;
			x = X[t], y = Y[t];
			if(x != 1 and y != m)
			for(int i=(x-2)*m+y+1;i>=1 and !vs[s[i]];i-=m)
			for(int j=i;j<i+m-y and !vs[s[j]];++j)
				vs.set(s[j]);
			if(x != n and y != 1)
			for(int i=x*m+y-1;i<=T and !vs[s[i]];i+=m)
			for(int j=i;j>i-y+1 and !vs[s[j]];--j)
				vs.set(s[j]);
		}
	for(int i=1;i<=Ans[0];++i)
		printf("%d ",Ans[i]);
	putchar(10);
	return 0;
}
