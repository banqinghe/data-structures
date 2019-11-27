#include <iostream>
#include <string>
using namespace std;

bool cmp_biginteger(string a,string b)  //判断是否大于等于
{
    while(*a.begin()=='0'&&a.begin()!=a.end()-1)
        a.erase(a.begin());
    if(a.size()>b.size()||(a.size()==b.size()&&(a.compare(b)==0||a.compare(b)>0)))
        return true;
    return false;
}

string add(string a, string b)
{
    int num1[205]={0},num2[205]={0},num3[205]={0};
    for(int i=0;i<a.size();i++)
        num1[i]=a[a.size()-i-1]-'0';
    for(int i=0;i<b.size();i++)
        num2[i]=b[b.size()-i-1]-'0';
    int l=a.size()>b.size()?a.size():b.size();
    for(int i=0;i<l;i++){
        num3[i]=num1[i]+num2[i]+num3[i];
        if(num3[i]>=10){
            num3[i]-=10;
            num3[i+1]=1;
        }
    }
    if(num3[l]!=0) l++;
    string c;
    for(int i=l-1;i>=0;i--)
        c+=num3[i]+'0';
    return c;
}

string sub(string a,string b)
{
    int num1[205]={0},num2[205]={0},num3[205]={0};
    for(int i=0;i<a.size();i++)
        num1[i]=a[a.size()-i-1]-'0';
    for(int i=0;i<b.size();i++)
        num2[i]=b[b.size()-i-1]-'0';
    int l=a.size()>b.size()?a.size():b.size();
    string c;
    if(cmp_biginteger(a,b)){
        for(int i=0;i<l;i++){
            num3[i]=num1[i]-num2[i]+num3[i];
            if(num3[i]<0){
                num3[i]+=10;
                num3[i+1]=-1;
            }
        }
        for(int i=l-1;num3[i]==0;i--)
            l--;
        for(int i=l-1;i>=0;i--)
            c+=num3[i]+'0';
    }
    else{
        c='-'+sub(b,a);
    }
    if(c.size()==0) c+='0';
    return c;
}

string multiple(string a, string b)
{
    int num1[205]={0},num2[205]={0},num3[405]={0};
    for(int i=0;i<a.size();i++)
        num1[i]=a[a.size()-i-1]-'0';
    for(int i=0;i<b.size();i++)
        num2[i]=b[b.size()-i-1]-'0';
    int l=0;
    int i,j;
    for(i=0;i<a.size();i++){
        for(j=0,l=i;j<b.size();j++){
            num3[l++]+=num2[j]*num1[i];
        }
    }
    for(i=0;i<l;i++){
        if(num3[i]>=10){
            if(num3[l-1]>=10)
                l++;
            num3[i+1]+=num3[i]/10;
            num3[i]%=10;
        }
    }
    string c;
    for(i=l-1;i>=0;i--)
        c+=num3[i]+'0';
    while(*c.begin()=='0'&&c.begin()!=c.end()-1)
        c.erase(c.begin());
    return c;
}

string divide(string a, string b)
{
    string c,temp;
    int i,cnt,l=a.size();
    while(cmp_biginteger(a,b)){
        cnt=0;
        i=0;
        if(temp.size()==0){
            temp=a.substr(0,b.size());
            c.insert(c.begin(),b.size()-1,'0');
            i=1;
        }
        else if(temp.compare("0")==0){
            i=1;
            temp=a[0];
        }
        else{
            int t=temp.size();
            temp=a.substr(0,temp.size()+1);
            i=temp.size()-t;
        }
        int count=0;
        bool ok=true;
        while((!cmp_biginteger(temp,b))&&c.size()+1<l){
            c+='0';
            temp=a.substr(0,temp.size()+1);
            i++;
            count++;
            ok=false;
        }
        if(!ok) i--;
        while(*temp.begin()=='0'&&temp.begin()!=temp.end()-1)
            temp.erase(temp.begin());
        int t=temp.size();
        while(cmp_biginteger(temp,b)){
            temp=sub(temp,b);
            cnt++;
        }
        c+=cnt+'0';
        if(c.size()==l)
            break;
        if(temp.compare("0")==0)
            a.erase(0,t);
        else
            a.replace(0,t,temp);
    }
    c.insert(c.end(),l-c.size(),'0');
    while(*c.begin()=='0'&&c.begin()!=c.end()-1)
        c.erase(c.begin());
    return c;
}

int main()
{
    string a,b;
    cin>>a>>b;
    string::iterator it1=a.begin();
    string::iterator it2=b.begin();
    bool sign1=0,sign2=0;
    if(a[0]=='-') sign1=1, a.erase(it1);
    if(b[0]=='-') sign2=1, b.erase(it2);
    char commend;
    cin>>commend;
    switch (commend){
        case '+':
            if(sign1&&sign2) cout<<'-'<<add(a,b)<<endl;     //同负
            else if(sign1==0&&sign2==1) cout<<sub(a,b)<<endl;     //正负
            else if(sign1==1&&sign2==0) cout<<sub(b,a)<<endl;     //负正
            else cout<<add(a,b)<<endl;     //同正
            break;
        case '-':
            if(sign1&&sign2) cout<<sub(b,a)<<endl;      //同负
            else if(sign1==0&&sign2==1) cout<<add(a,b)<<endl;    //正负
            else if(sign1==1&&sign2==0) cout<<'-'<<add(a,b)<<endl;  //负正
            else cout<<sub(a,b)<<endl;    //同正
            break;
        case '*':
            if(sign1!=sign2) cout<<'-'<<multiple(a,b)<<endl;
            else cout<<multiple(a,b)<<endl;
            break;
        case '/':
            if(a.compare("0")==0) cout<<"0"<<endl;
            else if(sign1!=sign2) cout<<'-'<<divide(a,b)<<endl;
            else cout<<divide(a,b)<<endl;
            break;
        default:
            cout<<"Wrong commend!"<<endl;
			break;
    }
    return 0;
}