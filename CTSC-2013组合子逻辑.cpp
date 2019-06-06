//bzoj-3152
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char ch=getchar();x=0;while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
}

const int N = 2001001;
int h[N], a[N], T, n, tp;

inline void push(int x) {h[++tp] = x, push_heap(h+1,h+tp+1);}
inline void pop() {pop_heap(h+1,h+tp+1), --tp;}

void work() {
	read(n), tp = 0;
	for(int i=1;i<=n;++i) read(a[i]);
	if(n == 1) return puts("0"), void();
	int ret = a[1] - 1, ans = 1;
	for(int i=2;i<=n;++i)
		if(ret) --ret, push(a[i]);
		else {
			if(!tp) return puts("-1"), void();
			ret = h[1] - 2; if(ret < 0) return puts("-1"), void();
			++ans, pop(), push(a[i]);
		}
	printf("%d\n",ans);
}

int main() {
	int T; read(T);
	while(T--) work();
	return 0;
}
