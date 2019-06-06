#include<algorithm>
#include<cstdio>
#include<cctype>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int L=6001000,li=1000;
struct lst{int l,r,cnt,sum;}seg[L];
int rt[L],sum[210][210][1010],cnt[210][210][1010];
int n,m,q,tot;

#define mid (((l)+(r))>>1)

inline void update(int las,int&x,int l,int r,int alpha){
	seg[x=++tot]=seg[las];
	++seg[x].cnt,seg[x].sum+=alpha;
	if(l==r)return ;
	if(alpha<=mid)update(seg[las].l,seg[x].l,l,mid,alpha);
	else update(seg[las].r,seg[x].r,mid+1,r,alpha);
	return ;
}

inline int query(int las,int x,int l,int r,int alpha){
	if(!alpha)return 0;
	int Cnt=seg[seg[x].r].cnt-seg[seg[las].r].cnt;
	int Sum=seg[seg[x].r].sum-seg[seg[las].r].sum;
	if(l==r){
		Cnt=seg[x].cnt-seg[las].cnt;
		return min((alpha+l-1)/l,Cnt);
	}
	if(Sum>=alpha)return query(seg[las].r,seg[x].r,mid+1,r,alpha);
	else return Cnt+query(seg[las].l,seg[x].l,l,mid,alpha-Sum);
}

int main(){
	read(n),read(m),read(q);
	if(n==1){
		swap(n,m);
		rg int x,l,r,alpha;
		for(rg int i=1;i<=n;++i)read(x),update(rt[i-1],rt[i],1,li,x);
		while(q--){
			read(x),read(l),read(x),read(r),read(alpha);
			if(seg[rt[r]].sum-seg[rt[l-1]].sum<alpha)puts("Poor QLW");
			else printf("%d\n",query(rt[l-1],rt[r],1,li,alpha));
		}
		return 0;
	}
	else {
		rg int x,l,r,ans,md,x1,y1,x2,y2;
		for(rg int i=1;i<=n;++i)
		for(rg int j=1;j<=m;++j){
			read(x);
			for(rg int k=1;k<=li;++k)
				if(x<k)
					cnt[i][j][k]=cnt[i-1][j][k]+cnt[i][j-1][k]-cnt[i-1][j-1][k],
					sum[i][j][k]=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k];
				else 
					cnt[i][j][k]=cnt[i-1][j][k]+cnt[i][j-1][k]-cnt[i-1][j-1][k]+1,
					sum[i][j][k]=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k]+x;
		}
		#define beta (sum[x2][y2][mid]-sum[x2][y1][mid]-sum[x1][y2][mid]+sum[x1][y1][mid])
		while(q--){
			read(x1),read(y1),read(x2),read(y2),read(x);
			--x1,--y1;
			if(sum[x2][y2][1]-sum[x2][y1][1]-sum[x1][y2][1]+sum[x1][y1][1]<x)
				{puts("Poor QLW");continue;}
			l=0,r=1001,ans=123321;
			while(l+1<r){
				md=(l+r)>>1;
				if(x<=beta)l=md,ans=md;
				else r=md;
			}l=ans;
			int Sum=sum[x2][y2][l]-sum[x2][y1][l]-sum[x1][y2][l]+sum[x1][y1][l];
			int Cnt=cnt[x2][y2][l]-cnt[x1][y2][l]-cnt[x2][y1][l]+cnt[x1][y1][l];
			printf("%d\n",Cnt-(Sum-x)/l);
		}
	}
}
