#include<bits/stdc++.h>
using namespace std;
int main()
{
	map<int,int>Map;
	set<int>Set;
	int n,d,ans=0;
	for(cin>>n;n--;)
	{
		cin>>d;
		Map[d]++;
		Set.insert(d);
	}
	for(set<int>::iterator it=Set.begin();it!=Set.end();it++)
		if(Map[*it]>1) ans++;
	cout<<ans;
}
