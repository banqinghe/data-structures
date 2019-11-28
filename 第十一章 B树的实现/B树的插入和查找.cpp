#include <iostream>
using namespace std;

enum Error_code{success,not_present,duplicate_error,overflow};

template <class Entry>
struct B_node{
    int cnt;
    Entry data[1000];
    B_node<Entry> *branch[1000];
    B_node(){
        cnt=0;
    }
};

template <class Entry>
class B_tree{
public:
    B_tree(int &m);

    Error_code search_tree(Entry &target);
    Error_code recursive_search_tree(B_node<Entry> *current,Entry &target);
    Error_code search_node(B_node<Entry> *current,const Entry &target,int &position);

    Error_code insert(const Entry &new_entry);
    Error_code push_down(B_node<Entry>* current,const Entry &new_entry,
    Entry &median,B_node<Entry>* &right_branch);
    void push_in(B_node<Entry>* current,const Entry &entry,B_node<Entry>* right_branch,
    int position);
    void split_node(B_node<Entry>* current, const Entry &extra_entry,
        B_node<Entry> *extra_branch, int position,
        B_node<Entry>* &right_half, Entry  &median);
private:
    int order;
    bool searching;
    B_node<Entry> *root;
};

template <class Entry>
B_tree<Entry>::B_tree(int &m){
    order=m;
    root=NULL;
    searching=false;
}

template <class Entry>
Error_code B_tree<Entry>::search_tree(Entry &target){
    searching=true;
    return recursive_search_tree(root,target);
}

template <class Entry>
Error_code B_tree<Entry>::recursive_search_tree(B_node<Entry> *current,Entry &target){
    Error_code result=not_present;
    int position;
    if(current!=NULL){
        result=search_node(current,target,position);
        if(result==not_present)
            result=recursive_search_tree(current->branch[position],target);
        else
            target = current->data[position];
    }
    return result;
}

template <class Entry>
Error_code B_tree<Entry>::search_node(B_node<Entry> *current,const Entry &target,int &position){
    position = 0;
    // if(searching && position<current->cnt && target < current->data[position])
    //     cout<<current->data[position]<<' ';
    while(position < current->cnt && target > current->data[position]) {
        if(searching)
            cout<<current->data[position]<<' ';
        position++;
    }
    if(searching && position<current->cnt && target < current->data[position])
        cout<<current->data[position]<<' ';
    if(position < current->cnt && target == current->data[position]) return success;
    return not_present;
}

template <class Entry>
Error_code B_tree<Entry>::insert(const Entry &new_entry){
    Entry median;
    B_node<Entry> *right_branch,*new_root;
    Error_code result=push_down(root,new_entry,median,right_branch);
    if(result==overflow){
        new_root=new B_node<Entry>;
        new_root->cnt=1;
        new_root->data[0]=median;
        new_root->branch[0]=root;
        new_root->branch[1]=right_branch;
        root=new_root;
        result=success;
    }
    return result;
}

template <class Entry>
Error_code B_tree<Entry>::push_down(B_node<Entry>* current,const Entry &new_entry,
Entry &median,B_node<Entry>* &right_branch) {
    Error_code result;
    int position;
    if(current==NULL){
        median=new_entry;
        right_branch=NULL;
        result=overflow;
    }
    else {
        if(search_node(current,new_entry,position)==success)
            result=duplicate_error;
        else {
            Entry extra_entry;
            B_node<Entry> *extra_branch;
            result=push_down(current->branch[position],new_entry,extra_entry,extra_branch);
            if(result==overflow) {
                if(current->cnt<order-1) {
                    result=success;
                    push_in(current,extra_entry,extra_branch,position);
                }
                else
                    split_node(current,extra_entry,extra_branch,position,right_branch,median);
            }
        }
    }
    return result;
}

template <class Entry>
void B_tree<Entry>::push_in(B_node<Entry>* current,const Entry &entry,
B_node<Entry>* right_branch,int position){
    for(int i=current->cnt;i>position;i--){
        current->data[i]=current->data[i-1];
        current->branch[i+1]=current->branch[i];
    }
    current->data[position]=entry;
    current->branch[position+1]=right_branch;
    current->cnt++;
}

template <class Entry>
void B_tree<Entry>::split_node(B_node<Entry>* current, const Entry &extra_entry,
        B_node<Entry> *extra_branch, int position,
        B_node<Entry>* &right_half, Entry  &median){
    right_half=new B_node<Entry>;
    int mid=order/2;
    if(position<=mid) {
        for(int i=mid;i<order-1;i++){
            right_half->data[i-mid]=current->data[i];
            right_half->branch[i+1-mid]=current->branch[i+1];
        }
        current->cnt=mid;
        right_half->cnt=order-1-mid;
        push_in(current,extra_entry,extra_branch,position);
    }
    else {
        mid++;
        for(int i=mid;i<order-1;i++) {
            right_half->data[i-mid]=current->data[i];
            right_half->branch[i+1-mid]=current->branch[i+1];
        }
        current->cnt=mid;
        right_half->cnt=order-1-mid;
        push_in(right_half,extra_entry,extra_branch,position-mid);
    }
    median=current->data[current->cnt-1];
    right_half->branch[0]=current->branch[current->cnt];
    current->cnt--;
}

int main()
{
    int num,m;
    Error_code result;
    cin>>m;
    B_tree<int> p(m);
    while(cin>>num&&num!=-1)
        p.insert(num);
    int target;
    cin>>target;
    result=p.search_tree(target);
    if(result==not_present) cout<<-1<<endl;
    else if(result==success) cout<<target<<endl;
    cin>>target;
    result=p.search_tree(target);
    if(result==not_present) cout<<-1<<endl;
    else if(result==success) cout<<target<<endl;
}