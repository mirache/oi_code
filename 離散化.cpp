//因爲線段樹中會經常性地用到離散化，所以在這兒放一份拷貝
#include<bits/stdc++.h>
using namespace std;

int n,a[105],b[105];
int m;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){scanf("%d",&a[i]);b[i]=a[i];}
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=m;i++)	cout<<lower_bound(b+1,b+1+m,a[i])-b<<" ";
	return 0;
}
