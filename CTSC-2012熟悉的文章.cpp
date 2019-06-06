#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

const int N=2001000;
int pre[N],stp[N],ch[N][2];
int f[N],q[N],orz[N];
int n,m,len,tot=1,lst=1,L,R;
char s[N];

inline void ins(int x){
	int p=lst,np=++tot;
	lst=np;stp[np]=stp[p]+1;
	while(p&&!ch[p][x])ch[p][x]=np,p=pre[p];
	if(!p)pre[np]=1;
	else {
		int q=ch[p][x];
		if(stp[q]==stp[p]+1)pre[np]=q;
		else {
			int nq=++tot;stp[nq]=stp[p]+1;
			//*ch[nq]=*ch[q];
			ch[nq][0]=ch[q][0],ch[nq][1]=ch[q][1];
			pre[nq]=pre[q];
			pre[q]=pre[np]=nq;
			while(ch[p][x]==q)ch[p][x]=nq,p=pre[p];
		}
	}return ;
}

inline int check(int li){
	int he(1),ta(0);
	for(rg int i=1;i<=len;++i){
		f[i]=f[i-1];
		if(i<li)continue;
		while(he<=ta&&f[q[ta]]-q[ta]<=f[i-li]-i+li)--ta;
		q[++ta]=i-li;
		while(he<=ta&&q[he]<i-orz[i])++he;
		if(he<=ta)f[i]=max(f[i],f[q[he]]+i-q[he]);
	}return f[len]*10>=len*9;
}

void PRE(){
	scanf("%s",s+1);
	len=strlen(s+1);
	L=0;R=len;
	int nw(1),cnt(0);
	for(rg int i=1;i<=len;++i){
		int x=s[i]-'0';
		if(ch[nw][x])++cnt,nw=ch[nw][x];
		else {
			while(nw&&!ch[nw][x])nw=pre[nw];
			if(nw)cnt=stp[nw]+1,nw=ch[nw][x];
			else nw=1,cnt=0;
		}
		orz[i]=cnt;
	}return ;
}

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%s",s);lst=1;
		for(rg int i=0;s[i];++i)ins(s[i]-'0');
	}
	while(n--){
		PRE();
		while(L<R){
			int mid(L+R+1>>1);
			if(check(mid))L=mid;
			else R=mid-1;
		}
		printf("%d\n",L);
	}return 0;
}
