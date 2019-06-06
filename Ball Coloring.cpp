//Atcoder-arc073E
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void cmin(int&x, const int&y) {if(x > y) x = y;}
inline void cmax(int&x, const int&y) {if(x < y) x = y;}
inline void cmin(ll&x, const ll&y) {if(x > y) x = y;}

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 201000, Inf = 1e9;

struct node {
	int x, y;
	friend inline bool operator < (const node&A,const node&B)
		{return A.x != B.x ? A.x < B.x : A.y  < B.y;}
}p[N];

int min_x, min_y;
int max_x, max_y;
int n;

int main(){
	read(n);
	min_x = min_y = Inf;
	max_x = max_y = 0;
	for(int i=1,x,y;i<=n;++i) {
		read(x), read(y);
		if(x > y) swap(x, y);
		p[i].x = x, p[i].y = y;
		cmin(min_x, x), cmax(max_x, x);
		cmin(min_y, y), cmax(max_y, y);
	}
	sort(p+1,p+n+1);
	ll ans = (ll)(max_x - min_x) * (max_y - min_y);
	int mi = Inf, mx = p[n].x;
	for(int i=1;i<=n;++i){
		if(i != 1) cmin(ans, (ll)(max_y - min_x) * (mx - min(p[i].x, mi)));
		cmax(mx, p[i].y), cmin(mi, p[i].y);
	}
	printf("%lld\n",ans);
	return 0;
}
