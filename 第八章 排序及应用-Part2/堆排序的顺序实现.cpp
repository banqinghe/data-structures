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
    // Error_code retrieve(int pos, List_entry &x) const;
    Error_code replace(int pos, const List_entry &x);
    Error_code remove(int pos);
    Error_code insert(int pos, const List_entry &x);
    void insertion_sort();
    void sort_interval(const int start, const int increment);
    void shell_sort(const int* a,const int sum);
    void transfer(const int pos1,const int pos2);
    void selection_sort();
    void swap(int x,int y);
    void quicksort();
    void recursive_quick_sort(int low,int high);
    int partition(int low,int high);
    void heapsort();
    void insert_heap(const List_entry& current,int low,int high);
    void build_heap();
    Error_code push_back(List_entry &x);
protected:
    bool have_print;
    int cnt;
    List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List(){
    cnt=0;
    have_print=false;
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

// template <class List_entry>
// Error_code List<List_entry>::retrieve(int pos, List_entry &x) const{
//     if(pos>=cnt) return overflow;
//     else if(pos<0) return underflow;
//     x=entry[pos];
//     return success;
// }

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
void List<List_entry>::insertion_sort(){
    int cnt_sorted,cur=1,cur_sorted;
    for(cnt_sorted=1;cnt_sorted<cnt;cnt_sorted++){
        // if(cnt_sorted==cnt/2){
        //     for(int i=0;i<cnt;i++)
        //         cout<<entry[i]<<' ';
        //     cout<<endl;
        // }
        for(cur_sorted=0;cur_sorted<cnt_sorted;cur_sorted++){
            if(entry[cur]<entry[cur_sorted]){
                transfer(cur,cur_sorted);
                break;
            }
        }
        cur++;
    }
}

template <class List_entry>
void List<List_entry>::sort_interval(const int start,const int increment){
    int cur=start+increment,cur_sorted;
    while(cur<cnt){
        for(cur_sorted=start;cur_sorted<cnt&&cur>cur_sorted;cur_sorted+=increment){
            if(entry[cur]<entry[cur_sorted]){
                List_entry temp=entry[cur];
                for(int i=cur;i>cur_sorted;i-=increment){
                    entry[i]=entry[i-increment];
                }
                entry[cur_sorted]=temp;
                break;
            }
        }
        cur+=increment;
    }
}

template <class List_entry>
void List<List_entry>::shell_sort(const int* a,const int sum){
    int i,start;
    for(i=0;i<sum;i++){
        for(start=0;start<a[i];start++){
            sort_interval(start,a[i]);
        }
        for(int j=0;j<cnt;j++)
            cout<<entry[j]<<' ';
        cout<<endl;
    }
}

template <class List_entry>
void List<List_entry>::transfer(const int pos1,const int pos2){
    List_entry temp=entry[pos1];
    remove(pos1);
    insert(pos2,temp);
}

template <class List_entry>
void List<List_entry>::selection_sort(){
    int i,cnt_sorted;
    for(cnt_sorted=0;cnt_sorted<cnt;cnt_sorted++){
        if(cnt_sorted==cnt/2){
            for(int i=0;i<cnt;i++)
                cout<<entry[i]<<' ';
            cout<<endl;
        }
        int index=cnt_sorted,min=entry[cnt_sorted];
        for(i=cnt_sorted;i<cnt;i++){
            if(entry[i]<min){
                min=entry[i];
                index=i;
            }
        }
        List_entry temp=entry[cnt_sorted];
        entry[cnt_sorted]=min;
        entry[index]=temp;
    }
}

template <class List_entry>
void List<List_entry>::swap(int x,int y){
    List_entry temp;
    temp=entry[x];
    entry[x]=entry[y];
    entry[y]=temp;
}

template <class List_entry>
void List<List_entry>::quicksort(){
    recursive_quick_sort(0,cnt-1);
}

template <class List_entry>
void List<List_entry>::recursive_quick_sort(int low,int high){
    int pivot_position;
    if(low<high){
        pivot_position=partition(low,high);
        if(!have_print){
            for(int i=0;i<cnt;i++){
                cout<<entry[i]<<' ';
            }
            cout<<endl;
            have_print=true;
        }
        recursive_quick_sort(low,pivot_position-1);
        recursive_quick_sort(pivot_position+1,high);
    }
}

template <class List_entry>
int List<List_entry>::partition(int low,int high){
    List_entry pivot;
    int i, last_small;
    swap(low,high);
    pivot=entry[low];
    last_small=low;
    for(i=low+1;i<=high;i++){
        if(entry[i]<pivot){
            last_small++;
            swap(last_small,i);
        }
    }
    swap(low,last_small);
    return last_small;
}

template <class List_entry>
void List<List_entry>::heapsort(){
    List_entry current;
    int last_unsorted;
    build_heap();
    for(int i=0;i<cnt;i++)
        cout<<entry[i]<<' ';
    cout<<endl;
    for(last_unsorted=cnt-1;last_unsorted>0;last_unsorted--){
        current=entry[last_unsorted];
        entry[last_unsorted]=entry[0];
        insert_heap(current,0,last_unsorted-1);
    }
}

template <class List_entry>
void List<List_entry>::insert_heap(const List_entry& current,int low,int high){
    int large;
    large=2*low+1;
    while(large<=high){
        if(large<high&&entry[large]<entry[large+1]) large++;
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
void List<List_entry>::build_heap(){
    int low;
    for(low=cnt/2-1;low>=0;low--){
        List_entry current=entry[low];
        insert_heap(current,low,cnt-1);
    }
}

template <class List_entry>
void print(List_entry &x){
    cout<<x<<' ';
}

int main()
{
    List<int> p;
    int i,n,num;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>num;
        p.push_back(num);
    }
    p.heapsort();
    p.traverse(print);
    return 0;
}