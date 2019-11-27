#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

bool cmp(char &a,char &b){
    return a<b;
}

bool same_alpha(string a,string b){
    sort(a.begin(),a.end(),cmp);
    sort(b.begin(),b.end(),cmp);
    string::iterator end_unique1=unique(a.begin(), a.end());
    string::iterator end_unique2=unique(b.begin(), b.end());
    a.erase(end_unique1,a.end());
    b.erase(end_unique2,b.end());
    return a.compare(b)==0;
}

struct Word{
    string str;
    bool unused;
    int num;
};

int main()
{
    Word word[1005];
    int cnt=0,i,j,sum,sum_group=0;
    while(cin>>word[cnt].str)
        word[cnt++].unused=true;
    sum=cnt;
    string model;
    
    while(sum){
        sum_group++;
        for(i=0;i<cnt;i++){
            if(word[i].unused){
                if(model.size()==0){
                    model=word[i].str;
                    sum--;
                    word[i].unused=false;
                    word[i].num=sum_group-1;
                }
                else if(same_alpha(model,word[i].str)){
                    sum--;
                    word[i].unused=false;
                    word[i].num=sum_group-1;
                }
            }
        }
        model="";
    }

    cout<<sum_group<<endl;
    for(i=0;i<sum_group;i++){
        for(j=0;j<cnt;j++){
            if(word[j].num==i) cout<<word[j].str<<' ';
        }
        cout<<endl;
    }
    return 0;
}