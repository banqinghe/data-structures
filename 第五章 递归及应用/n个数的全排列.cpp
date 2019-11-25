#include<iostream>
using namespace std;

int num,b[25],c[25],cnt;

void all_permutation(int x)
{
    if(cnt>=10) return ;
    for(int i=0;i<num;i++){
        if(b[i]==0){
            b[i]=1;
            c[x]=i+1;
            if(x==num-1){
                cnt++;
                cout<<cnt<<':';
                for(int j=0;j<num;j++){
                    cout<<c[j]<<' ';
                }
                cout<<endl;
            }
            else all_permutation(x+1);
            b[i]=0;
        }
    }
    return ;
}

int main()
{
    cin>>num;
    all_permutation(0);
    long long sum=1;
    for(int i=2;i<=num;i++)
        sum*=i;
    cout<<sum<<endl;
    return 0;
}