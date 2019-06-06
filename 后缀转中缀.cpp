#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>0?(x):(-(x)))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

#define is1(x) ((x)=='+'||(x)=='-')
#define is2(x) ((x)!='+'&&(x)!='-')

//#define is1(x) ((x)!='*'&&(x)!='/')
//#define is2(x) ((x)=='*'&&(x)=='/')

//#define is1(x) ((x)=='+'||(x)=='-')
//#define is2(x) ((x)=='*'||(x)=='/')

struct node{
	char c[10000];int len;
	char val;
	node(){len=0;}
	node(const char&ch){c[len=1]=ch;val=0;}
};

char s[1010101];
int n,top(0);
node sta[1234];

int main(){
	freopen("in","r",stdin);
	read(n);scanf("%s",s);
	for(rg int i=0;s[i];++i){
		if(isalpha(s[i])){sta[++top]=node(s[i]);continue;}
		
		if(is1(s[i])){
			if(is1(sta[top].val)){
				sta[top-1].c[++sta[top-1].len]=s[i];
				sta[top-1].c[++sta[top-1].len]='(';
				for(rg int j=1;j<=sta[top].len;++j)
					sta[top-1].c[++sta[top-1].len]=sta[top].c[j];
				sta[top-1].c[++sta[top-1].len]=')';
				sta[top-1].val=s[i];
				--top;
				continue;
			}
			if(is2(sta[top].val)){
				sta[top-1].c[++sta[top-1].len]=s[i];
				for(rg int j=1;j<=sta[top].len;++j)
					sta[top-1].c[++sta[top-1].len]=sta[top].c[j];
				sta[top-1].val=s[i];
				--top;
				continue;
			}
		}
		
		if(is2(s[i])){
			if(!sta[top].val){
				sta[top-1].c[++sta[top-1].len]=s[i];
				for(rg int j=1;j<=sta[top].len;++j)
					sta[top-1].c[++sta[top-1].len]=sta[top].c[j];
				sta[top-1].val=s[i];
				--top;
				continue;
			}
			if(is1(sta[top-1].val)){
				for(rg int j=sta[top-1].len;j;--j)sta[top-1].c[j+1]=sta[top-1].c[j];
				sta[top-1].c[1]='(';sta[top-1].c[(sta[top-1].len+=2)]=')';
				sta[top-1].c[++sta[top-1].len]=s[i];
				sta[top-1].c[++sta[top-1].len]='(';
				for(rg int j=1;j<=sta[top].len;++j)
					sta[top-1].c[++sta[top-1].len]=sta[top].c[j];
				sta[top-1].c[++sta[top-1].len]=')';
				sta[top-1].val=s[i];
				--top;
				continue;
			}
			if(is2(sta[top-1].val)){
				sta[top-1].c[++sta[top-1].len]=s[i];
				sta[top-1].c[++sta[top-1].len]='(';
				for(rg int j=1;j<=sta[top].len;++j)
					sta[top-1].c[++sta[top-1].len]=sta[top].c[j];
				sta[top-1].c[++sta[top-1].len]=')';
				sta[top-1].val=s[i];
				--top;
				continue;
			}
		}
		puts("Wulalalalalala......");return 0;
	}
	for(rg int i=1;i<=sta[1].len;++i)
		putchar(sta[1].c[i]);
	putchar('\n');
	return 0;
}
