// 。没有使用数据结构，有bug，暂且录入。

#include<iostream>
using namespace std;

int main()
{
    char a[1505],c;
    int i,sum=0;
    int cnt1_1=0,cnt1_2=0,cnt2_1=0,cnt2_2=0,cnt3_1=0,cnt3_2=0;
    while((c=getchar())!=EOF) a[sum++]=c;
    for(i=0;i<sum;i++){
        if(a[i]=='/'&&a[i+1]=='/'){
            while(a[i]!='\n') i++;
        }
        else if(a[i]=='/'&&a[i+1]=='*'){
            while(a[i]!='*'||a[i+1]!='/') i++;
            i++;
        }
        else{
            switch (a[i]){
                case '(': cnt1_1++; break;
                case ')': cnt1_2++; break;
                case '[': cnt2_1++; break;
                case ']': cnt2_2++; break;
                case '{': cnt3_1++; break;
                case '}': cnt3_2++; break;
                default: break;
            }
        }
    }
    int m=cnt1_1+cnt1_2+cnt2_1+cnt2_2+cnt3_1+cnt3_2;
    cout<<m<<' ';
    if(cnt1_1!=cnt1_2||cnt2_1!=cnt2_2||cnt3_1!=cnt3_2) cout<<"no"<<endl;
    else cout<<"yes"<<endl;
    return 0;
}