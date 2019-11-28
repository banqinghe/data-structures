#include <iostream>
#include <string>
#include <list>
using namespace std;

const int max_size=1000;

struct Data{
    string key,value;
};

class hashmap{
public:
    hashmap();
    void getsize(const int &size);
    void put(string &key,string &value);
    void get(string &key);
    void remove(string &key);
    void before_insert(string &key);
    void print();
private:
    unsigned BKRD(string &key);
    int hash_size;
    list<Data> table[max_size];
};

hashmap::hashmap(){
    hash_size=0;
}

void hashmap::getsize(const int &size){
    hash_size=size;
}

void hashmap::put(string &key,string &value){
    Data temp;
    temp.key=key;
    temp.value=value;
    unsigned position=BKRD(key);
    list<Data>::iterator it=table[position].begin();
    bool ok=false;
    for(;it!=table[position].end();it++){
        if(it->key==key){
            it->value=value;
            ok=true;
            break;
        }
    }
    if(!ok){
        table[position].push_front(temp);
    }
}

void hashmap::get(string &key){
    int position=BKRD(key);
    list<Data>::iterator it=table[position].begin();
    cout<<position<<' ';
    list<string> path;
    bool ok=false;
    for(;it!=table[position].end();it++){
        if(it->key==key){
            ok=true;
            break;
        }
        path.push_back(it->key);
    }
    while(!path.empty()){
        cout<<path.front()<<' ';
        path.pop_front();
    }
    if(ok) cout<<it->key<<' '<<it->value<<endl;
    else cout<<key<<" NULL"<<endl;
}

void hashmap::remove(string &key){
    int position=BKRD(key);
    bool ok=false;
    cout<<position<<' ';
    list<Data>::iterator it=table[position].begin();
    list<string> path;
    for(;it!=table[position].end();it++){
        if(it->key==key){
            ok=true;
            break;
        }
        path.push_back(it->key);
    }
    while(!path.empty()){
        cout<<path.front()<<' ';
        path.pop_front();
    }
    cout<<key<<' ';
    if(ok){
        cout<<it->value<<' '<<endl;
        table[position].erase(it);
    }
    else{
        cout<<"NULL"<<endl;
    }
}

unsigned hashmap::BKRD(string &key){
    unsigned seed=31;
    unsigned hash=0;
    char* str=(char*)key.c_str();
    while(*str)
        hash=(hash*seed+(*str++))%hash_size;
    return hash%hash_size;
}

void hashmap::before_insert(string &key){
    cout<<BKRD(key)<<endl;
}

void hashmap::print(){
    for(int i=0;i<hash_size;i++){
        cout<<i<<' ';
        for(list<Data>::iterator it=table[i].begin();it!=table[i].end();it++){
            cout<<it->key<<' ';
        }
        cout<<endl;
    }
}

int main()
{
    hashmap p;
    int n,m;
    cin>>n>>m;
    p.getsize(n);
    string key,value;
    for(int i=0;i<m;i++){
        // cout<<"i="<<i<<endl;
        cin>>key>>value;
        p.put(key,value);
    }
    //p.print();
    cin>>key>>value;
    p.before_insert(key);
    p.put(key,value);
    cin>>key;
    p.remove(key);
    cin>>key;
    p.get(key);
    return 0;
}
