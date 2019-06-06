//bzoj-4946
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 101000;
int a[N], s[N], c[N], x[N], us[N];
ll Ans[N];
int n,m,Q;

typedef pair<ll,int> pr;
#define vl first
#define id second

vector <int> vec[N];
vector <int> :: iterator itr;

struct HEAP{
	pr h[N]; int tp;
	HEAP() {tp = 0;}
	inline void push(const pr&x) {h[++tp] = x, push_heap(h+1,h+tp+1);}
	inline void pop() {pop_heap(h+1,h+tp+1), --tp;}
	inline pr top() {return h[1];}
}H;

inline int rst(int i,int d) {return c[i] - x[i] * (d-1) - us[i];}

int stk[N*10], tp;

int main() {
	read(n), read(m), read(Q);
	const int D = 1e5;
	for(int i=1;i<=n;++i) {
		read(a[i]), read(s[i]), read(c[i]), read(x[i]);
		if(!x[i]) vec[D].push_back(i);
		else vec[min(D, (c[i]+x[i]-1)/x[i])].push_back(i);
	}
	
	ll&res = Ans[D];
	for(int i=D;i;--i) {
		for(itr = vec[i].begin(); itr != vec[i].end(); ++ itr)
			H.push(pr(a[*itr] + s[*itr], *itr));
		
		int mm = m; tp = 0;
		while(mm and H.tp) {
			pr nw = H.top(); H.pop();
			if(!us[nw.id]) {
				res += nw.vl, nw.vl = a[nw.id];
				mm -= (us[nw.id] = 1);
				H.push(nw); continue;
			}
			int ct = min(mm, rst(nw.id, i));
			res += nw.vl * ct;
			us[nw.id] += ct, mm -= ct;
			stk[++tp] = nw.id;
		}
		while(tp) {
			mm = stk[tp--];
			if(rst(mm, i-1)) H.push(pr(a[mm],mm));
		}
	}
	
	int tot = 0;
	for(int i=1;i<=n;++i) {
		if(us[i]) stk[++tot] = a[i]+s[i];
		for(int j=1;j<us[i];++j) stk[++tot] = a[i];
	}
	
	sort(stk+1,stk+tot+1);
	reverse(stk+1,stk+tot+1);
	
	for(int i=D-1;i;--i) {
		Ans[i] = Ans[i+1];
		while(tot > i * m) Ans[i] -= stk[tot--];
	}
	
	while(Q--) read(tot), printf("%lld\n",Ans[tot]);
	return 0;
}
