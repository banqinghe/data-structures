#include<iostream>
using namespace std;

void solve(string s,int cur,int sum){
    if(cur==s.size())
        cout<<sum<<endl;
    else{
        sum=sum*2+s[cur]-'0';
        solve(s,cur+1,sum);
    }
}

int main()
{
    string s;
    cin>>s;
    solve(s,0,0);
    return 0;
}
