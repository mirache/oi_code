#include <bits/stdc++.h>
using namespace std;

const int N=5001000;
int a[N],sa,sb,sc,sd,p,n;

inline int qm(int x){return x<p?x:x-p;}
int f(int x){return qm(sd+1ll*x*(sc+1ll*x*(sb+1ll*x*sa%p)%p)%p);}

bool check(int t){
	int d=-2e9;
	for(int i=1;i<=n;++i)
		if(a[i]+t<d)return false;
		else d=max(d,a[i]-t);
	return true;
}

int main(){
	scanf("%d%d%d%d%d%d%d",&n,&sa,&sb,&sc,&sd,a+1,&p);
	for(int i=2;i<=n;++i)a[i]=qm(f(a[i-1])+f(a[i-2]));
	int l=0,r=1e9+7,res=r,mid=0;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))r=(res=mid)-1;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}
