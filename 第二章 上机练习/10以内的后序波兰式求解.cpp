#include<iostream>
#include<cctype>
#include<stack>
using namespace std;

int main()
{
    stack<int> num;
    char c,ok=1;
    while((c=getchar())!=EOF){
        if(isdigit(c)) num.push(c-'0');
        else{
            if(num.size()<2) { ok=0; break; }
            int temp;
            switch (c){
                case '+':
                    temp=num.top();
                    num.pop();
                    num.top()+=temp;
                    break;
                case '-':
                    temp=num.top();
                    num.pop();
                    num.top()-=temp;
                    break;
                case '*':
                    temp=num.top();
                    num.pop();
                    num.top()*=temp;
                    break;
                case '/':
                    temp=num.top();
                    num.pop();
                    num.top()/=temp;
                    break;
                default:
                    ok=0;
                    break;
            }
            if(!ok) break;
        }
    }
    // cout<<"ok="<<(int)ok<<endl<<"num.size()="<<num.size()<<endl;
    if(ok&&num.size()==1) cout<<num.top()<<endl;
    else cout<<"none"<<endl;
    return 0;
}