#include<iostream>
#define imaxlen 100
using namespace std;

enum Error_code{success,overflow,underflow};

struct Node{
    Node *next;
    int entry;
    Node();
    Node(int num,Node* add_on=NULL);
};

class LinkedStack{
private:
    Node* Node_top;
    //Node* head;
    int maxlen;
    int stack_size;
public:
    LinkedStack();
    ~LinkedStack();
    bool isempty();
    bool isfull();
    Error_code pop();
    Error_code push(int num);
    int top();
    int size();
};

Node::Node(int num,Node*add_on){
    entry=num;
    next=add_on;
}

LinkedStack::LinkedStack(){
    stack_size=0;
    maxlen=imaxlen;
    Node_top=NULL;
}

bool LinkedStack::isempty(){
    if(stack_size==0) return true;
    return false;
}

bool LinkedStack::isfull(){
    if(stack_size==maxlen) return true;
    return false;
}

int LinkedStack::size(){
    return stack_size;
}

Error_code LinkedStack::push(int num){
    if(isfull()) return overflow;
    if(isempty()){
        //Node* newptr;
        Node_top=new Node(num);
        stack_size++;
    }
    else{
        Node* newptr=new Node(num);
        newptr->next=Node_top;
        Node_top=newptr;
        stack_size++;
    }
    return success;
}

Error_code LinkedStack::pop(){
    if(isempty()) return underflow;
    Node*prev=Node_top;
    Node_top=Node_top->next;
    delete prev;
    stack_size--;
    return success;
}

int LinkedStack::top(){
    if(isempty()) return underflow;
    return Node_top->entry;
}

LinkedStack::~LinkedStack(){
    while(!isempty()){
        pop();
    }
}

int main()
{
    LinkedStack test;
    int num;
    while(cin>>num&&num!=-1){
        test.LinkedStack::push(num);
    }
    while(!test.LinkedStack::isempty()){
        cout<<test.LinkedStack::top()<<' ';
        test.LinkedStack::pop();
    }
    cout<<endl;
    return 0;
}

