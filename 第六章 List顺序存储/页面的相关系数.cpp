#include <iostream>
using namespace std;

struct Web{
    string URL;
    int vi;
};

int main()
{
    Web web[155];
    int T,i;
    cin>>T;
    for(i=0;i<T;i++)
        cin>>web[i].URL>>web[i].vi;
    int maxn=0;
    for(i=0;i<T;i++)
        if(maxn<web[i].vi)
            maxn=web[i].vi;
    for(i=0;i<T;i++)
        if(maxn==web[i].vi)
            cout<<web[i].URL<<endl;
    return 0;
}