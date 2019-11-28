#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string s;
    cin>>s;
    int i,vis[256],ans=0,cur=-1;
    memset(vis,-1,sizeof(vis));
    for(i=0;i<s.size();i++){
        if(vis[s[i]]>cur)
            cur=vis[s[i]];
        vis[s[i]]=i;
        ans=ans>(i-cur)?ans:(i-cur);
    }
    cout<<ans<<endl;
}