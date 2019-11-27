#include <iostream>
using namespace std;

enum Error_code{success,overflow,underflow};

template <class Node_entry>
struct Node{
    Node_entry entry;
    Node<Node_entry> *next;
    Node();
    Node(Node_entry,Node<Node_entry>*link=NULL);
};

template <class Node_entry>
Node<Node_entry>::Node(){
    next=NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry item,Node<Node_entry>* link){
    entry=item;
    next=link;
}

template <class List_entry>
class List{
public:
    List();
    ~List();
    void traverse(void (*visit)(List_entry &));
    Error_code push_back(const List_entry &x);
    Error_code remove(int pos);
    Error_code insert(int pos,const List_entry &x);
    Error_code retrieve(int pos, List_entry &x) const;
    Error_code replace(int pos,const List_entry &x);
    Error_code insertion_sort();
    void mergesort();
    Node<List_entry>* divide_from(Node<List_entry> *sub_list);
    void recursive_mergesort(Node<List_entry>* &sub_list);
    Node<List_entry>* merge(Node<List_entry>* first, Node<List_entry>* second);
    bool empty();
    bool full();
    int size();
protected:
    mutable Node<List_entry>* cur;
    mutable int cur_position;
    Node<List_entry>* head;
    int cnt;
    bool first_print=true;
    int merge_cnt=0;
    void set_position(int pos) const;
};

template <class List_entry>
List<List_entry>::List(){
    cnt=0;
    head=NULL;
}

template <class List_entry>
List<List_entry>::~List(){
   while(!empty())
       remove(0);
}

template <class List_entry>
bool List<List_entry>::empty(){
    return cnt==0;
}

template <class List_entry>
int List<List_entry>::size(){
    return cnt;
}

template <class List_entry>
bool List<List_entry>::full(){
    Node<List_entry> *newptr=new Node<List_entry>();
    if(newptr!=NULL){
        delete newptr;
        return false;
    }
    return true;
}

template <class List_entry>
void List<List_entry>::set_position(int pos) const{
    if(pos<=cur_position){
        cur=head;
        cur_position=0;
    }
    for(;pos!=cur_position;cur_position++)
        cur=cur->next;
}

template <class List_entry>
Error_code List<List_entry>::push_back(const List_entry &x){
    return insert(cnt,x);
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry&)){
    for(Node<List_entry>* current=head;current!=NULL;current=current->next){
        (*visit)(current->entry);
    }
    cout<<endl;
}

template <class List_entry>
Error_code List<List_entry>::insert(int pos, const List_entry& x){
    if(pos>cnt||full()) return overflow;
    else if(pos<0) return underflow;
    if(pos<=cur_position) set_position(0);
    if(pos==0){
        Node<List_entry>* newptr=new Node<List_entry>(x);
        newptr->next=head;
        head=newptr;
        cur=newptr;
        cur_position=0;
    }
    else{
        set_position(pos-1);
        Node<List_entry>* newptr=new Node<List_entry>(x);
        newptr->next=cur->next;
        cur->next=newptr;
    }
    cnt++;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int pos){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    if(pos<=cur_position) set_position(0);
    if(pos==0){
        Node<List_entry>* temp=head;
        head=temp->next;
        delete temp;
    }
    else{
        set_position(pos-1);
        Node<List_entry>* temp=cur->next;
        if(temp==NULL)
            cur->next=NULL;
        else
            cur->next=temp->next;
        delete temp;
    }
    cnt--;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int pos, List_entry &x) const{
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    set_position(pos);
    x=cur->entry;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int pos,const List_entry &x){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    set_position(pos);
    cur->entry=x;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::insertion_sort(){
    Node<List_entry> *first_unsorted,
                    *last_sorted,
                    *current,
                    *trailing;
    if(head!=NULL){
        last_sorted=head;
        int cnt_insertion=0;
        while(last_sorted->next!=NULL){
            first_unsorted=last_sorted->next;
            if(first_unsorted->entry < head->entry){
                last_sorted->next=first_unsorted->next;
                first_unsorted->next=head;
                head=first_unsorted;
            }
            else{
                trailing=head;
                current=trailing->next;
                while(first_unsorted->entry>current->entry){
                    trailing=current;
                    current=trailing->next;
                }
                if(first_unsorted==current)
                    last_sorted=first_unsorted;
                else{
                    last_sorted->next=first_unsorted->next;
                    first_unsorted->next=current;
                    trailing->next=first_unsorted;
                }
            }
            cnt_insertion++;
            if(cnt_insertion==cnt/2-1){
                for(Node<List_entry> *temp=head;temp!=NULL;temp=temp->next){
                    cout<<temp->entry<<' ';
                }
                cout<<endl;
            }
        }
    }
}

template <class List_entry>
void List<List_entry>::mergesort(){
    recursive_mergesort(head);
}

template <class List_entry>
Node<List_entry>* List<List_entry>::divide_from(Node<List_entry> *sub_list){
    Node<List_entry> *position,*midpoint,*second_half;
    if((midpoint=sub_list)==NULL) return NULL;
    position=midpoint->next;
    while(position!=NULL){
        position=position->next;
        if(position!=NULL){
            midpoint=midpoint->next;
            position=position->next;
        }
    }
    second_half=midpoint->next;
    midpoint->next=NULL;        //截断
    return second_half;
}

template <class List_entry>
void List<List_entry>::recursive_mergesort(Node<List_entry>* &sub_list){
    if(sub_list!=NULL&&sub_list->next!=NULL){
        Node<List_entry>* second_half=divide_from(sub_list);
        recursive_mergesort(sub_list);
        recursive_mergesort(second_half);
        merge_cnt++;
        if(merge_cnt==cnt-1){
        for(Node<List_entry>* temp=sub_list;temp!=NULL;temp=temp->next)
            cout<<temp->entry<<' ';
        cout<<endl;
        for(Node<List_entry>* temp=second_half;temp!=NULL;temp=temp->next)
            cout<<temp->entry<<' ';
        cout<<endl;
        }
        sub_list=merge(sub_list,second_half);
    }
}

template <class List_entry>
Node<List_entry>* List<List_entry>::merge(Node<List_entry>* first, Node<List_entry>* second){
    Node<List_entry>* result;
    Node<List_entry> combined;
    result=&combined;
    while(first!=NULL&&second!=NULL){
        if(first->entry<=second->entry){
            result->next=first;
            result=first;
            first=first->next;
        }
        else{
            result->next=second;
            result=second;
            second=second->next;
        }
    }
    if(first==NULL)
        result->next=second;
    else
        result->next=first;
    return combined.next;
}

template <class List_entry>
void print(List_entry &x){
    cout<<x<<' ';
}

int main()
{
    List<int> p;
    int num,n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>num;
        p.push_back(num);
    }
    p.mergesort();
    p.traverse(print);
    return 0;
}