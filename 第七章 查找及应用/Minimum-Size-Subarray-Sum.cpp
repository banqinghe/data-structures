#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    vector<int> a,b;
    int temp,i,j,s,sum=0;
    bool ok=true;
    cin>>s;
    b.push_back(0);
    a.push_back(0);
    while(cin>>temp&&temp!=-1){
        a.push_back(temp);
        sum+=temp;
        b.push_back(sum);
    }
    int min_length=2005,keynum=1e7,bottom=0,top=a.size()-1;
    if(sum<s) ok=false;
    else{
        i=1;
        for(j=1;j<a.size();j++){
            if(b[j]-b[i-1]<s) continue;
            while(b[j]-b[i-1]>s&&b[j]-b[i]>=s) i++;
            if((min_length>j-i+1)
            ||(min_length==j-i+1&&abs(s-(b[j]-b[i-1]))<abs(s-keynum))
            ||(min_length==j-i+1&&abs(s-(b[j]-b[i-1]))==abs(s-keynum)&&i<bottom)){
                bottom=i;
                top=j;
                min_length=j-i+1;
                keynum=b[j]-b[i-1];
            }
        }
    }
    if(ok){
        cout<<min_length<<endl;
        for(i=bottom;i<=top;i++){
            cout<<a[i]<<' ';
        }
        cout<<endl;
    }
    else cout<<0<<endl;
    return 0;
}
