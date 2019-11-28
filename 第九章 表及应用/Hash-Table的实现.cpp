#include <iostream>
#include <cstring>
using namespace std;

const int max_size=2005;
enum Error_code{success,overflow,duplicate_error,not_present};

struct Data{
    int key,value;
};

class hash_table{
public:
    hash_table();
    void clear();
    void getsize(int& size);
    Error_code insert(const int &new_key,const int &new_value);
    Error_code retrieve(const int &target) const;
    void traverse(void (*visit)(int&));
private:
    Data table[max_size];
    int cnt,hash_size;
};

hash_table::hash_table(){
    cnt=0;
    hash_size=0;
    for(int i=0;i<max_size;i++){
        table[i].key=-1;
    }
    // memset(table,-1,max_size);
}

void hash_table::clear(){
    cnt=0;
    for(int i=0;i<max_size;i++){
        table[i].key=-1;
    }
    // memset(table,-1,max_size);
}

void hash_table::getsize(int& size){
    hash_size=size;
}

Error_code hash_table::insert(const int &new_key,const int &new_value){
    Error_code result=success;
    int probe=new_key % hash_size,increment=1,probe_cnt=0;
    while(table[probe].key!=-1
            &&table[probe].key!=new_key
            &&probe_cnt<(hash_size+1)/2){
        probe_cnt++;
        probe=(probe+increment)%hash_size;
        increment+=2;
    }
    if(table[probe].key==-1){
        table[probe].key=new_key;
        table[probe].value=new_value;
        cnt++;
    }
    else if(table[probe].key==new_key) result=duplicate_error;
    else result=overflow;
    return result;
}

Error_code hash_table::retrieve(const int& target) const{
    int increment=-1; 
    bool ok=false,have_used[2000]={false};
    int position=target%hash_size;
    // cout<<"position="<<position<<endl;
    while(1){
        if(have_used[position]==true) break;
        cout<<position<<' ';
        if(table[position].key==-1) break;
        if(table[position].key==target){
            cout<<target<<' '<<table[position].value<<endl;
            ok=true;
            break;
        }
        have_used[position]=true;
        increment+=2;
        position=(position+increment)%hash_size;
    }
    if(ok==true) return success;
    cout<<"NULL"<<endl;
    return not_present;
}

void hash_table::traverse(void (*visit)(int&)){
    for(int i=0;i<hash_size;i++)
        (*visit)(table[i].key);
    cout<<endl;
}

void print(int &x){
    cout<<x<<' ';
}

int main()
{
    hash_table p;
    int a,b,m,n;
    cin>>m>>n;
    p.getsize(m);
    for(int i=0;i<n;i++){
        cin>>a>>b;
        p.insert(a,b);
    }
    int target1,target2;
    cin>>target1>>target2;
    p.retrieve(target1);
    p.retrieve(target2);
    // p.traverse(print);
    return 0;
}