//CodeForces-865D
#include <bits/stdc++.h>

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=601000;
int h[N],top;

void push(int x){
	h[++top]=x;int pp=top;
	while(pp>1&&h[pp]<h[pp>>1])std::swap(h[pp],h[pp>>1]),pp>>=1;
}

void pop(){
	h[1]=h[top--];int pp=1;
	while(((pp<<1)<=top&&h[pp]>h[pp<<1])||((pp<<1|1)<=top&&h[pp]>h[pp<<1|1])){
		pp<<=1;
		if(h[pp]>h[pp|1])pp|=1;
		std::swap(h[pp],h[pp>>1]);
	}
}

int main(){
	int n,x;read(n);
	long long ans=0ll;
	while(n--){
		read(x);
		push(x),push(x);
		ans+=x-h[1],pop();
	}printf("%I64d\n",ans);
	return 0;
}
