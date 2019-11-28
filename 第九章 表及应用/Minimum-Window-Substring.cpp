#include <iostream>
#include <algorithm>
using namespace std;

bool include_char(string &s,string &t,int head,int tail){
    int i,arr[256]={0};
    for(i=0;i<t.size();i++){
        arr[t[i]]++;
    }
    for(i=head;i<=tail;i++){
        arr[s[i]]--;
    }
    bool ok=true;
    for(i=0;i<t.size();i++){
        if(arr[t[i]]>0){
            ok=false;
            break;
        }
    }
    if(ok) return true;
    return false;
}

int main()
{
    int i=0,j=0,ans=2005,t1=0,t2=0;
    string s,t;
    cin>>s>>t;
    while(j<s.size()){
        if(include_char(s,t,i,j)==false)
            j++;
        else{
            if(ans>j-i+1){
                ans=j-i+1;
                t1=i;
                t2=j;
            }
            i++;
        }
    }
    if(ans==2005){
        cout<<"NULL"<<endl;
    }
    else{
        for(;t1<=t2;t1++){
            cout<<s[t1];
        }
        cout<<endl;
    }
    return 0;
}