#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
using namespace std;
#define cl(x) memset(x,0,sizeof(x))
#define rg register

const int maxl=105,maxn=105;
char O[maxl],be[maxn],en[maxn];
int st[maxn];
string s[maxn];
string bian;

int work(){
	int L,ans=0;
	bool bo=0;
	set <string> c;
	scanf("%d",&L);
	scanf("%s",O);
	int flag=1,xian=0,top=0;
	char le[4];
	for(rg int i=1;i<=L;++i){
		scanf("%s",le);
		if(le[0]=='F'){
			++top;st[top]=0;
			std::cin>>s[top];
			if(c.count(s[top]))flag=2;
			c.insert(s[top]);
			scanf("%s%s",be,en);
			if(be[0]>='0'&&be[0]<='9')
				if(en[0]<'0'||en[0]>'9')++xian,st[top]=1;
			if(be[0]<'0'||be[0]>'9')
				if(en[0]>='0'&&en[0]<='9')st[top]=2,bo=1;
			if(be[0]>='0'&&be[0]<='9')
			if(en[0]>='0'&&en[0]<='9'){
				int A=0,B=0,lena=strlen(be),lenb=strlen(en);
				for(rg int i=0;i<lena;++i)A=A*10+be[i]-'0';
				for(rg int i=0;i<lenb;++i)B=B*10+en[i]-'0';
				if(A>B)
					st[top]=2,bo=1;
				if(A==B)
					st[top]=0;
			}
			if(!bo)ans=max(ans,xian);
		}
		else {
			if(st[top]==1)--xian;
			if(st[top]==2)bo=0;
			c.erase(s[top]);
			--top;
			if(top<0)top=0,flag=2;
		}
	}
	if(top!=0)flag=2;
	if(flag==2)return 2;
	if(ans==0){
		if(O[2]=='1')return 1;
		else return 0;
	}
	int ff=0;
	for(rg int i=4;O[i]!=')';++i)ff=ff*10+O[i]-'0';
	if(ans==ff)return 1;
	return 0;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int tem=work();
		if(tem==0)puts("No");
		else if(tem==1)puts("Yes");
		else if(tem==2)puts("ERR");
	}
	return 0;
}
