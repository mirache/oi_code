//bzoj-4299 / 4408
#include <cstdio>
typedef long long ll;

const int N = 101000;
int rt[N],n,tot;

int ls[N*37], rs[N*37];
ll sz[N*37];

void update(int l,int r,int&x,int ps){
	++tot;
	ls[tot] = ls[x], rs[tot] = rs[x];
	sz[tot] = sz[x] + ps, x = tot;
	if(l == r) return ;
	int mid(l+r>>1);
	if(ps <= mid) update(l,mid,ls[x],ps);
	else update(mid+1,r,rs[x],ps);
}

ll query(int l,int r,int x,int y,int R){
	if(r <= R) return sz[y] - sz[x];
	int mid(l+r>>1);
	ll res = query(l,mid,ls[x],ls[y],R);
	if(mid < R) res += query(mid+1,r,rs[x],rs[y],R);
	return res;
}

int main(){
	scanf("%d",&n); int L = 1e9;
	for(int i=1,x;i<=n;++i) scanf("%d",&x), update(1,L,rt[i]=rt[i-1],x);
	int Q,l,r; scanf("%d",&Q);
	while(Q--){
		scanf("%d%d",&l,&r), --l;
		ll S = 1ll, del;
		while(1) {
			del = query(1,L,rt[l],rt[r],S);
			if(del < S) break;
			S = del + 1;
		}
		printf("%lld\n",S);
	}
	return 0;
}
