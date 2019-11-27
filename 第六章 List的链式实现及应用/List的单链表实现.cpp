#include <iostream>
using namespace std;

enum Error_code{success,overflow,underflow};

template <class Node_entry>
struct Node{
    Node_entry entry;
    Node<Node_entry> *next;

    Node();
    Node(Node_entry x,Node<Node_entry> *link=NULL);
};

template <class Node_entry>
Node<Node_entry>::Node(){
    next=NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry x,Node<Node_entry> *link){
    entry=x;
    next=link;
}

template <class List_entry>
class List{
public:
    List();
    ~List();
    void traverse(void (*visit)(List_entry &));
    Error_code insert(int pos, const List_entry &x);
    Error_code remove(int pos);
    Error_code retrieve(int pos, List_entry &x) const;
    Error_code replace(int pos, const List_entry &x);
    Error_code push_back(List_entry &x);
    int size();
    bool empty();
    bool full();
protected:
    int cnt;
    mutable int current_position;   //记录最后一次使用的下标
    Node<List_entry> *head;
    mutable Node<List_entry> *current;  //记录最后一次使用的下标的地址
    void set_position(int pos) const;
};

template <class List_entry>
List<List_entry>::List(){
    cnt=0;
    head=NULL;
}

template <class List_entry>
List<List_entry>::~List(){
    while(!empty()){
        remove(0);
    }
}

template <class List_entry>
void List<List_entry>::set_position(int pos) const{
    if(pos<=current_position){
        current_position=0;
        current=head;
    }
    for(;current_position!=pos;current_position++)
        current=current->next;
}

template <class List_entry>
int List<List_entry>::size(){
    return cnt;
}

template <class List_entry>
bool List<List_entry>::empty(){
    return cnt==0;
}

template <class List_entry>
bool List<List_entry>::full(){
    Node<List_entry> *new_node(1);
    if(new_node!=NULL){
        delete new_node;
        return false;
    }
    return true;
}

template <class List_entry>
Error_code List<List_entry>::remove(int pos){
    if(pos<0) return underflow;
    else if(pos>cnt) return overflow;
    if(pos<=current_position)
    current_position--;
    if(pos==0){
        Node<List_entry> *temp=head;
        head=head->next;
        delete temp;
    }
    else{
        set_position(pos-1);
        Node<List_entry> *temp=current->next;
        current->next=temp->next;
        delete temp;
    }
    cnt--;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::push_back(List_entry &x){
    if(cnt==0){
        head=new Node<List_entry>(x);
    }
    else{
        set_position(cnt-1);
        Node<List_entry> *newptr=new Node<List_entry>(x);
        current->next=newptr;
    }
    cnt++;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int pos, const List_entry &x){
    if(pos<0) return underflow;
    else if(pos>cnt) return overflow;
    Node<List_entry> *new_node,*following;
    if(pos<=current_position)
        current_position++;
    new_node=new Node<List_entry>(x);
    if(pos>0){
        set_position(pos-1);
        following=current->next;
        current->next=new_node;
    }
    else{
        following =head;
    }
    new_node->next=following;
    if(new_node==NULL)
        return overflow;
    if(pos==0)
        head=new_node;
    cnt++;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int pos, List_entry &x) const{
    if(pos<0) return underflow;
    else if(pos>cnt) return overflow;
    set_position(pos);
    x=current->entry;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int pos, const List_entry &x){
    if(pos<0) return underflow;
    else if(pos>cnt) return overflow;
    set_position(pos);
    current->entry=x;
    return success;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
    for(Node<List_entry> *cur=head;cur!=NULL;cur=cur->next){
        (*visit)(cur->entry);
    }
    cout<<endl;
}

template <class List_entry>
void print(List_entry &x)
{
    cout<<x<<' ';
}

int main()
{
    List<int> test;
    int num,a,b,c,d,e;
    while(cin>>num&&num!=-1)
        test.push_back(num);
    while(cin>>a>>b&&!(a==-1&&b==-1))
        test.insert(a,b);
    while(cin>>c&&c!=-1)
        test.remove(c);
    while(cin>>d>>e&&!(d==-1&&e==-1))
        test.replace(d,e);
    test.traverse(print);
    return 0;
}