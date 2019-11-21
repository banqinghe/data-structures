#include<cstdio>
using namespace std;

void solve2(int n)
{
    if(n==0){
        printf("0\n");
        return;
    }
    int i,cnt=0,a[100];
    while(n>0){
        a[cnt++]=n&1;
        n>>=1;
    }
    for(i=cnt-1;i>=0;i--)
        printf("%d",a[i]);
    printf("\n");
}

void solve8(int n)
{
    printf("%o\n",n);
}

void solve16(int n)
{
    printf("%X\n",n);
}

int main()
{
    int n,t;
    scanf("%d%d",&n,&t);
    if(t==2) solve2(n);
    else if(t==8) solve8(n);
    else solve16(n);
    return 0;
}