#include <iostream>
using namespace std;

void sqrt_fun(unsigned long &x,unsigned long bottom,unsigned long top,unsigned long &ans){
    if(bottom<=top){
        ans=(top-bottom)/2+bottom;
        if(ans*ans>x) return sqrt_fun(x,bottom,ans-1,ans);
        else if(ans*ans<x) return sqrt_fun(x,ans+1,top,ans);
        return;
    }
    if(ans*ans>x) ans-=1;
}

int main()
{
    unsigned long x,ans;
    cin>>x;
    sqrt_fun(x,0,x,ans);
    cout<<ans<<endl;
    return 0;
}