#include<bits/stdc++.h>
using namespace std;
#define cl(x) memset(x,0,sizeof(x))
#define CL(x) memset(x,-1,sizeof(x))

template <typename _Tp> inline void read(_Tp &x){
	char c11=getchar();x=0;
	while(c11<'0'||c11>'9')c11=getchar();
	while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
	return ;
}

const int maxn=100500,maxm=500050;
int s[maxn];
int n,m;
struct node {int v,nxt;} a[maxm<<1];
int head[maxn],p=0;
struct node1{int v,nxt;} b[maxm<<1];
int head1[maxn],p1=0;
int minn[maxn],maxx[maxn];

inline void add(int,int);
inline void app(int,int);
void init();

void spfa(){
	queue <int> q;
	q.push(1);
	CL(minn);
	minn[1]=s[1];
	while(!q.empty()){
		int x=q.front();
		q.pop();
		minn[x]=min(minn[x],s[x]);
		for(int i=head[x];i;i=a[i].nxt){
			int v=a[i].v;
			if(minn[v]==-1||min(minn[x],s[v])<minn[v]){
				minn[v]=min(minn[x],s[v]);
				q.push(v);
			}
		}
	}
	return ;
}
bool flag=0;
void spfa2(){
	queue <int> q;
	q.push(n);
	CL(maxx);
	maxx[n]=s[n];
	while(!q.empty()){
		int x=q.front();
		if(x==1)flag=1;
		q.pop();
		for(int i=head1[x];i;i=b[i].nxt){
			int v=b[i].v;
			if(max(maxx[x],s[v])>maxx[v]){
				maxx[v]=max(s[v],maxx[x]);
				q.push(v);
			}
		}
	}
	return ;
}

void work(){
	if(flag==0){printf("0\n");return ;}
	int rich=0;
	for(int i=1;i<=n;i++)if(maxx[i]!=-1&&minn[i]!=-1)
		rich=max(rich,maxx[i]-minn[i]);
	printf("%d\n",rich);
	return ;
}

int main(){freopen("in.txt","r",stdin);freopen("1.out","w",stdout);
	init();
	spfa();
	spfa2();
	work();
	return 0;
}

void init(){
	read(n);read(m);
	for(int i=1;i<=n;i++)	read(s[i]);
	int A,B,C;
	for(int i=1;i<=m;i++){
		read(A);read(B);read(C);
		if(C==2)
			add(B,A),app(A,B);
		add(A,B);
		app(B,A);
	}
	return ;
}

inline void add(int u,int v){
	a[++p].v=v;
	a[p].nxt=head[u];
	head[u]=p;
	return ;
}

inline void app(int u,int v){
	b[++p1].v=v;
	b[p1].nxt=head1[u];
	head1[u]=p1;
	return ;
}
