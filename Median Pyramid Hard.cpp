//Atcoder-agc006D
#include <bits/stdc++.h>

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 201000;
int a[N],b[N],n,R;

bool check(int c){
	for(int i=1;i<=R;++i)
		b[i] = (a[i] >= c);
	int l = n, r = n;
	while(l > 1 and b[l] != b[l-1]) --l;
	while(r < R and b[r] != b[r+1]) ++r;
	
	int tag = 0, res = b[n];
	for(int i=1;i<=n;++i){
		while(l < r and b[l] == (b[l+1] ^ tag)) b[++l] ^= tag;
		while(l < r and b[r] == (b[r-1] ^ tag)) b[--r] ^= tag;
		tag ^= 1;
		if(l < n and n < r) res ^= 1;
		else break;
	}
	return res;
}

int main(){
	read(n); R = n + n - 1;
	for(int i=1;i<=R;++i) read(a[i]);
	int l = 1, r = R, mid, res = 0;
	while(l<=r){
		mid = l + r >> 1;
		if(check(mid)) l = (res = mid) + 1;
		else r = mid - 1;
	}
	printf("%d\n",res);
	return 0;
}
