//bzoj-2034
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 5022;
int us[N],ps[N],n;

struct task{
	int l,r,v,p;
	inline void in(){read(l),read(r),read(v);}
}t[N];

inline bool cmpl(const task&A,const task&B) {return A.l < B.l;}
inline bool cmpv(const task&A,const task&B) {return A.v > B.v;}

bool chk(int x,int p){
	if(t[x].r < ps[p]) return false;
	if(!us[p]) return us[p] = x, true;
	if(t[x].r >= t[us[p]].r) return chk(x,p+1);
	if(chk(us[p], p+1)) return us[p] = x, true;
	return false;
}

int main(){
	read(n);
	for(int i=1;i<=n;++i) t[i].in();
	sort(t+1,t+n+1,cmpl);
	for(int i=1;i<=n;++i) ps[i] = max(ps[i-1]+1, t[i].l);
	for(int i=1;i<=n;++i) {
		t[i].p = t[i-1].p;
		while(ps[t[i].p] < t[i].l and t[i].p < n) ++t[i].p;
	}
	sort(t+1,t+n+1,cmpv);
	long long ans = 0ll;
	for(int i=1;i<=n;++i)
		if(chk(i,t[i].p))
			ans += t[i].v;
	printf("%lld\n",ans);
	return 0;
}
