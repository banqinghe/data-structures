#include<iostream>
#include<queue>
using namespace std;

int main()
{
    int n,num;
    queue<int> q1;      /*主道*/
    queue<int> q2;      /*要求*/
    queue<int> q3;      /*辅道*/
    cin>>n;
    for(int i=1;i<=n;i++) q1.push(i);
    for(int i=0;i<n;i++){
        cin>>num;
        q2.push(num);
    }
    int ok=1;
    while(!q2.empty()){
        if(q1.empty()){ /*主道为空*/
            if(q3.empty()||q3.front()!=q2.front()){ /*辅道为空或者辅道的头部也不符合*/
                ok=0;
                break;
            }
            else{   /*辅道符合*/
                q3.pop();
                q2.pop();
            }
        }
        else if(q1.front()!=q2.front()){    /*主道不为空且不符合*/
            if(q3.empty()||q3.front()!=q2.front()){ /*辅道也不符合*/
                q3.push(q1.front());
                q1.pop();
            }
            else{   /*辅道符合*/
                q3.pop();
                q2.pop();
            }
        }
        else{
            q1.pop();
            q2.pop();
        }
    }
    if(ok) cout<<n<<' '<<"Yes"<<endl;
    else cout<<n<<' '<<"No"<<endl;
    return 0;
}