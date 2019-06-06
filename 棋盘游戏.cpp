//yzoj-3901
#include <cstdio>

const int N=34;
int a[N][N],rw[N],ln[N];
int n,t;

inline int calc(int i,int j){
	int res=a[i][j],e;
	e=a[i+t][j],res+=(rw[j]?-e:e);
	e=a[i][j+t],res+=(ln[i]?-e:e);
	e=a[i+t][j+t],res+=(ln[i]^rw[j+t]?-e:e);
	return res>0?res:-res;
}

int main(){
	scanf("%d",&n);t=n+1>>1;
	for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
		scanf("%d",&a[i][j]);
	
	int ans=0;
	for(int lim=1<<t,S=0;S<lim;++S){
		int sum=0;
		for(int i=1;i<=t;++i)
			if(S&(1<<i-1))rw[i]=1,sum-=a[t][i];
			else rw[i]=0,sum+=a[t][i];
		for(int i=t+1;i<=n;++i){
			rw[i]=rw[t]^rw[i-t];
			if(rw[i])sum-=a[t][i];
			else sum+=a[t][i];
		}
		
		for(int i=1,r0,r1;i<t;++i){
			r0=a[i][t]+(rw[t]?-a[i+t][t]:a[i+t][t]);
			ln[i]=0;for(int j=1;j<t;++j)r0+=calc(i,j);
			
			r1=-a[i][t]+(rw[t]?a[i+t][t]:-a[i+t][t]);
			ln[i]=1;for(int j=1;j<t;++j)r1+=calc(i,j);
			sum+=r0>r1?r0:r1;
		}ans=ans>sum?ans:sum;
	}printf("%d\n",ans);
	return 0;
}
