#include <iostream>
using namespace std;

const int max_list=1000;
enum Error_code{success,overflow,underflow};

template <class List_entry>
class List{
public:
    List();
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void (*visit)(List_entry &));
    Error_code replace(int pos, const List_entry &x);
    Error_code remove(int pos);
    Error_code insert(int pos, const List_entry &x);
    Error_code push_back(List_entry &x);
    void swap(int x,int y);
    void bulid_heap();
    void insert_heap(const List_entry& current,int low,int high);
    void remove_frome_heap(const int cnt_del);
    void insert_into_heap(const List_entry& current);
protected:
    int cnt;
    List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List(){
    cnt=0;
}

template <class List_entry>
int List<List_entry>::size() const{
    return cnt;
}

template <class List_entry>
bool List<List_entry>::full() const{
    return cnt==max_list;
}

template <class List_entry>
bool List<List_entry>::empty() const{
    return cnt==0;
}

template <class List_entry>
void List<List_entry>::clear(){
    cnt=0;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &)){
    for(int i=0;i<cnt;i++){
        (*visit)(entry[i]);
    }
    cout<<endl;
}

template <class List_entry>
Error_code List<List_entry>::replace(int pos, const List_entry &x){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    entry[pos]=x;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int pos){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    for(int i=pos;i<cnt;i++)
        entry[i]=entry[i+1];
    cnt--;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int pos, const List_entry &x){
    if(pos>cnt) return overflow;
    else if(pos<0) return underflow;
    for(int i=cnt;i>pos;i--)
        entry[i]=entry[i-1];
    entry[pos]=x;
    cnt++;    
    return success;
}

template <class List_entry>
Error_code List<List_entry>::push_back(List_entry &x){
    return insert(cnt,x);
}

template <class List_entry>
void List<List_entry>::swap(int x,int y){
    List_entry temp;
    temp=entry[x];
    entry[x]=entry[y];
    entry[y]=temp;
}

template <class List_entry>
void List<List_entry>::insert_heap(const List_entry& current,int low,int high){
    int large=low*2+1;  //找到第一个叶子节点
    while(large<=high){
        if(large<high&&entry[large]<entry[large+1]) large++; //找到最大的子节点
        if(current>=entry[large]) break;
        else{
            entry[low]=entry[large];
            low=large;
            large=2*low+1;
        }
    }
    entry[low]=current;
}

template <class List_entry>
void List<List_entry>::bulid_heap(){
    int low;
    for(low=cnt/2-1;low>=0;low--){
        List_entry current=entry[low];
        insert_heap(current,low,cnt-1);
    }
}

template <class List_entry>
void List<List_entry>::remove_frome_heap(const int cnt_del){
    int i;
    for(i=0;i<cnt_del;i++){
        swap(cnt-1,0);
        List_entry current=entry[0];
        cnt--;
        insert_heap(current,0,cnt-1);
        // List_entry cur=entry[0];
        // int cur_position=0,large=cur_position*2+1;
        // cnt--;
        // // if(large+1<cnt&&entry[large+1]>entry[large])
        // //     large++;
        // while(large<cnt){
        //     if(entry[large]>cur){
        //         swap(cur_position,large);
        //         cur_position=large;
        //         large=cur_position*2+1;
        //     }
        //     else if(large+1<cnt&&entry[large+1]>cur){
        //         swap(cur_position,large+1);
        //         cur_position=large+1;
        //         large=cur_position*2+1;
        //     }
        //     else{
        //         break;
        //     }
        //     bulid_heap();
        // }
        // for(int i=0;i<cnt;i++)
        //     cout<<entry[i]<<' ';
        // cout<<endl;
    }
}

template <class List_entry>
void List<List_entry>::insert_into_heap(const List_entry& current){
    entry[cnt++]=current;
    bulid_heap();
}

template <class List_entry>
void print(List_entry &x){
    cout<<x<<' ';
}

int main()
{
    List<int> p;
    int num;
    while(cin>>num&&num!=-1)
        p.push_back(num);
    p.bulid_heap();
    p.traverse(print);
    cin>>num;
    p.remove_frome_heap(num);
    p.traverse(print);
    while(cin>>num&&num!=-1){
        p.insert_into_heap(num);
    }
    p.traverse(print);
    return 0;
}