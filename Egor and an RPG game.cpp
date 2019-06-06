//Codeforces-1097E
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 101000;
int a[N],f[N],fr[N],vs[N],v[N];
int M;

namespace BIT{
	#define lb(x) (x&(-x))
	int d[N];
	inline void clear(){for(int i=0;i<=M;++i) d[i] = 0; v[0] = 0;}
	inline void upd(int x,int y){for(;x<=M;x+=lb(x)) if(v[d[x]] < v[y]) d[x] = y;}
	inline int qy(int x){int i=0;for(;x;x-=lb(x)) if(v[d[x]] > v[i]) i = d[x]; return i;}
	#undef lb
}

int LIS(int n){
	BIT::clear();
	for(int i=1;i<=n;++i) {
		int p = BIT::qy(a[i]);
		fr[i] = p, v[i] = v[p] + 1;
		BIT::upd(a[i],i);
	}
	return v[BIT::qy(M)];
}

vector <int> ans[N];

int main(){
	int T,n; read(T);
	while(T--){
		read(n); M = n;
		for(int i=0;i<=n;++i) f[i] = 0;
		
		for(int i=1;i*(i+1)<=n+n;++i) f[i*(i+1)>>1] = i;
		for(int i=1;i<=n;++i) if(!f[i]) f[i] = f[i-1];
		for(int i=1;i<=n;++i) read(a[i]);
		int tot = 0;
		while(n) {
			int k = f[n];
			int len = LIS(n);
			if(len > k){
				++tot;
				int x = BIT::qy(M);
				while(x){
					ans[tot].push_back(a[x]);
					vs[x] = 1, x = fr[x];
				}
				reverse(ans[tot].begin(),ans[tot].end());
				int nn = 0;
				for(int i=1;i<=n;++i)
					if(!vs[i]) a[++nn] = a[i];
					else vs[i] = 0;
				n = nn;
			}else {
				for(int i=1;i<=n;++i)
					ans[tot+v[i]].push_back(a[i]);
				tot += len;
				break;
			}
		}
		printf("%d\n",tot);
		for(int i=1,t;i<=tot;++i){
			printf("%d",t = int(ans[i].size()));
			for(int j=0;j<t;++j) printf(" %d",ans[i][j]);
			putchar(10);
			ans[i].clear();
		}
	}return 0;
}
