#include<iostream>
using namespace std;

string code[]={"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

void solve(string num,string temp,int cur,int t)	
//cur表示是第几个数字,t表示是该数字下的第几种可能
{
	if(cur!=num.size()){
		if(t!=code[num[cur]-'0'-2].size()){
			temp+=code[num[cur]-'0'-2][t];
			solve(num,temp,cur+1,0);
			temp.pop_back();
			solve(num,temp,cur,t+1);
		}
	}
	else{
		cout<<temp<<' ';
	}
}

int main()
{
	string num,temp;
	cin>>num;
	solve(num,temp,0,0);
	cout<<endl;
	return 0;
}
