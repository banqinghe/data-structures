#include<iostream>
using namespace std;

int main()
{
    int num[125],i,size1=0,size2=0,n;
    for(i=0;;i+=2){
        cin>>n; 
        if(n==-1)  break;
        else num[i]=n,size1++;
    }
    for(i=1;;i+=2){
        cin>>n;
        if(n==-1) break;
        else num[i]=n,size2++;
    }
    for(i=size1*2-2;i>=0;i-=2)
        cout<<num[i]<<" ";
    cout<<endl;
    for(i=size2*2-1;i>=1;i-=2)
        cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}