#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;

class Record{
public:
    Record();
    Record(string x, string y);
    string the_key() const;
    string the_other() const;
private:
    string key;
    string other;
};

Record::Record(){
    key="";
    other="";
}

Record::Record(string x,string y){
    key=x;
    other=y;
}

string Record::the_key() const{
    return key;
}

string Record::the_other() const{
    return other;
}

bool operator < (const Record &a, const Record &b){
    return a.the_key()<b.the_key();
}

bool operator > (const Record &a, const Record &b){
    return a.the_key()>b.the_key();
}

bool operator == (const Record &a, const Record &b){
    return a.the_key()==b.the_key();
}

bool cmp(const Record &a, const Record &b){
    return a<b;
}

bool binary_search2(list<Record> &the_list,string &target,int bottom,int top,int &pos){
    list<Record>::iterator it=the_list.begin();
    if(bottom<=top){
        int mid=(top-bottom)/2+bottom;
        advance(it,mid);
        string data=(*it).the_key();
        if(data==target){
            pos=mid;
            return true;
        }
        else  if(data<target)
            return binary_search2(the_list,target,mid+1,top,pos);
        return binary_search2(the_list,target,bottom,mid-1,pos);
    }
    return false;
}

int main()
{
    list <Record> a;
    string target,sentence;
    cin>>target;
    getchar();
    getline(cin,sentence);
    string key,other;
    stringstream stream(sentence);
    while(stream>>key&&stream>>other){
        Record temp(key,other);
        a.push_back(temp);
    }
    a.sort(cmp);
    int pos;
    if(binary_search2(a,target,0,a.size()-1,pos)){
        cout<<pos<<endl;
        list<Record>::iterator it=a.begin();
        advance(it,pos);
        cout<<(*it).the_key()<<' '<<(*it).the_other()<<endl;
    }
    else cout<<"-1"<<endl;
    return 0;
}