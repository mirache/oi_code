//UOJ-176
#include <bits/stdc++.h>
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

int d[301000],bin[30];
int n,m;ll ans=0ll;

inline int find(int x){return d[x]^x?d[x]=find(d[x]):x;}

int main(){
	read(n),read(m);bin[0]=1;
	for(int i=1;i<=m;++i)bin[i]=bin[i-1]<<1;
	for(int i=1,x;i<=n;++i){
		read(x);
		if(d[x])ans+=x;
		d[x]=x;
	}
	for(int i=bin[m]-1;i;--i){
		if(!d[i])
		for(int j=0;j<m;++j)
			if(!(i&bin[j])&&d[i|bin[j]])
				{d[i]=d[i|bin[j]];break;}
		for(int j=0;j<m;++j)
			if(!(i&bin[j])&&d[i|bin[j]])
			if(find(i)!=find(i|bin[j]))
				d[find(i)]=find(i|bin[j]),ans+=(ll)i;
	}printf("%lld\n",ans);
	return 0;
}
