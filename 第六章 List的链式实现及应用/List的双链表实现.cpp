#include <iostream>
using namespace std;

enum Error_code{success,overflow,underflow};

template <class Node_entry>
struct Node{
    Node_entry entry;
    Node<Node_entry> *next;
    Node<Node_entry> *back;
//constructors
    Node();
    Node(Node_entry item,Node<Node_entry> *link_back=NULL,
    Node<Node_entry> *link_next=NULL);
};

template <class Node_entry>
Node<Node_entry>::Node(){
    next=NULL;
    back=NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry item,Node<Node_entry> *link_back,
Node<Node_entry> *link_next){
    entry=item;
    back=link_back;
    next=link_next;
}

template<class List_entry>
class List{
protected:
    int cnt;
    mutable int current_position;
    mutable Node<List_entry> *current;
    void set_position(int pos) const; 
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
};

template<class List_entry>
List<List_entry>::List(){
    cnt=0;
    current_position=0;
}

template<class List_entry>
List<List_entry>::~List(){
    while(!empty())
        remove(0);
}

template<class List_entry>
int List<List_entry>::size(){
    return cnt;
}

template<class List_entry>
bool List<List_entry>::empty(){
    return cnt==0;
}

template<class List_entry>
bool List<List_entry>::full(){
    Node<List_entry> *newptr=new Node<List_entry>();
    if(newptr==NULL) return true;
    delete newptr;
    return false;
}

template<class List_entry>
void List<List_entry>::set_position(int pos) const{
    if(current_position<=pos)
        for(;current_position!=pos;current_position++)
            current=current->next;
    else 
        for(;current_position!=pos;current_position--)
            current=current->back;
}

template<class List_entry>
Error_code List<List_entry>::insert(int pos, const List_entry &x){
    if(pos>cnt) return overflow;
    else if(pos<0) return underflow;
    Node<List_entry> *newptr,*following,*preceding;
    // newptr=new Node<List_entry>(x);
    if(pos==0){     //插入第一个位置
        if(cnt==0) following=NULL;
        else{
            set_position(0);
            following=current;
        }
        preceding=NULL;
    }
    else{       //不是在第一个位置插入
        set_position(pos-1);
        following=current->next;
        preceding=current;
    }
    newptr=new Node<List_entry>(x,preceding,following);
    // newptr->back=preceding;
    // newptr->next=following;
    if(newptr==NULL) return overflow;
    if(preceding!=NULL) preceding->next=newptr;
    if(following!=NULL) following->back=newptr;
    current=newptr;
    current_position=pos;
    cnt++;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::push_back(List_entry &x){
    return insert(cnt,x);
}

template<class List_entry>
Error_code List<List_entry>::remove(int pos){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    set_position(pos);
    Node<List_entry> *temp=current,*preceding,*following;
    preceding=current->back;
    following=current->next;
    if(preceding!=NULL) preceding->next=following;
    if(following!=NULL) following->back=preceding;
    if(pos!=cnt-1) current=following;
    else{
        current=preceding;
        current_position--;
    }
    delete temp;
    cnt--;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int pos, List_entry &x) const{
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    set_position(pos);
    x=current->entry;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int pos, const List_entry &x){
    if(pos>=cnt) return overflow;
    else if(pos<0) return underflow;
    set_position(pos);
    current->entry=x;
    return success;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
    set_position(0);
    for(Node<List_entry> *cur=current;cur!=NULL;cur=cur->next){
        (*visit)(cur->entry);
    }
    cout<<endl;
}

template<class List_entry>
void Print(List_entry &x){
    cout<<x<<' ';
}

int main()
{
    int num,a,b,c,d,e;
    List<int> test;
    while(cin>>num&&num!=-1)
        test.push_back(num);
    while(cin>>a>>b&&!(a==-1&&b==-1))
        test.insert(a,b);
    while(cin>>c&&c!=-1)
        test.remove(c);
    while(cin>>d>>e&&!(d==-1&&e==-1))
        test.replace(d,e);
    test.traverse(Print);
    for(int i=test.size()-1;i>=0;i--){
        test.retrieve(i,num);
        cout<<num<<' ';
    }
    cout<<endl;
    return 0;
}
