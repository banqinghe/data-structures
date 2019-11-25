#include<iostream>
#include<queue>
using namespace std;

int main()
{
    int t;
    cin>>t;
    getchar();
    while(t--){
        queue<char> str;
        char c;
        int cnt1=0,cnt2=0,flag_same=1,flag_short=0,flag_mao=0;
        while((c=getchar())!='\n'){
            if(c==':') {flag_mao=1; break;}
            str.push(c);
        }
        cnt1=str.size();
        if(flag_mao){
            while((c=getchar())!='\n'&&c!=EOF){
                cnt2++;
                if(str.empty()) flag_short=1;    /*前者更短*/
                else {
                    if(str.front()!=c) flag_same=0;
                    str.pop();
                }
            }
        }
        if(!flag_mao) cout<<'N'<<endl;
        else if(cnt1==cnt2&&flag_same) cout<<'S'<<endl;
        else if(cnt1==cnt2&&!flag_same) cout<<'D'<<endl;
        else if(flag_short) cout<<'R'<<endl;
        else cout<<'L'<<endl;
    }
    return 0;
}