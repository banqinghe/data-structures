#include<iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--){
        string s;
        int cnt=0,i,ok=1;
        cin>>s;
        for(i=0;i<s.size();i++){
            if(s[i]=='I') cnt++;
            else cnt--;
            if(cnt<0) { ok=0; break; }
        }
        if(ok) cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }
    return 0;
}