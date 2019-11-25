#include<iostream>
using namespace std;

typedef int Node_entry;

enum Error_code{success,overflow,underflow};

class Node{
    private:
    Node_entry entry;
    Node* next;
    Node* head;
    Node* prev;
    public:
    Node();
    Node(Node_entry item,Node *add_on=NULL);
    Error_code input(Node_entry n);
    Error_code output();
    Error_code Node_insert(int t,Node_entry temp);
    Error_code Node_delet(Node_entry t);
    Error_code Node_add(int t);
    Error_code Node_outdata(int i,int j);
    Error_code Node_delete();
};

Node::Node(){
    next=NULL;
}

Node::Node(Node_entry item,Node *add_on){
    entry=item;
    next=add_on;
}

Error_code Node::input(Node_entry n){
    int num;
    if(n>0){
        cin>>num;
        head=new Node(num);
        Node* cur=head;
        for(int i=1;i<n;i++){
            cin>>num;
            Node* newptr=new Node(num);
            // prev=cur;
            cur->next=newptr;
            cur=newptr;
        }
    }
    return success;
}

Error_code Node::output(){
    for(Node*p=head;p!=NULL;p=p->next){
        cout<<p->entry<<' ';
    }
    cout<<endl;
    return success;
}

Error_code Node::Node_delet(int t){     //删除
    Node* cur=head;
    if(t==0){
        head=cur->next;
        delete cur;
    }
    else{
        for(int i=0;i<t;i++){
            prev=cur;
            cur=cur->next;
        }
        prev->next=cur->next;
        delete cur;
    }
}

Error_code Node::Node_insert(int t,Node_entry temp){        //插入
    // Node *ptr=head;
    if(t==0){
        Node *newptr=new Node(temp);
        newptr->next=head;
        head=newptr;
    }
    else{
        Node *newptr=new Node(temp);
        Node *cur=head;
        for(int i=1;i<t;i++){
            prev=cur;
            cur=cur->next;
        }
        prev=cur;
        newptr->next=cur->next;
        cur->next=newptr;
    }
    return success;
}

Error_code Node::Node_add(int t){
    Node *cur=head;
    int sum=0;
    for(int i=0;i<t;i++){
        sum+=cur->entry;
        cur=cur->next;
    }
    cout<<sum<<endl;
}

Error_code Node::Node_outdata(int i,int j){
    Node *cur=head;
    for(int k=0;k<i;k++){
        cur=cur->next;
    }
    for(int k=i;k<=j;k++){
        cout<<cur->entry<<' ';
        cur=cur->next;
    }
    cout<<endl;
}

Error_code Node::Node_delete(){
    Node *cur=head->next;
    prev=head;
    delete prev;
    for(;cur!=NULL;cur=cur->next){
        prev=cur;
        delete prev;
    }
}

int main()
{
    int n;
    // int n,i,j;
    cin>>n;
    Node p;
    p.Node::input(n);
    // cin>>i>>j;
    // p.Node::Node_outdata(i,j);
    p.Node::Node_add(n);
    // p.Node::Node_insert(5,9);
    // p.Node::Node_delet(0);
    // p.Node::output();
    return 0;
}