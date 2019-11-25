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

class LinkedQueue{
private:
    Node* Node_front;
    Node* rear;
    int maxlen;
    int queue_size;
public:
    LinkedQueue();
    ~LinkedQueue();
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

LinkedQueue::LinkedQueue(){
    queue_size=0;
    maxlen=imaxlen;
    Node_front=NULL;
    rear=NULL;
}

bool LinkedQueue::isempty(){
    if(queue_size==0) return true;
    return false;
}

bool LinkedQueue::isfull(){
    if(queue_size==maxlen) return true;
    return false;
}

int LinkedQueue::size(){
    return queue_size;
}

Error_code LinkedQueue::push(int num){
    if(isfull()) return overflow;
    //Node*prev;
    if(isempty()){
        //Node* newptr;
        Node_front=new Node(num);
        rear=Node_front;
        queue_size++;
    }
    else{
        Node* newptr=new Node(num);
        rear->next=newptr;
        rear=newptr;
        queue_size++;
    }
    return success;
}

Error_code LinkedQueue::pop(){
    if(isempty()) return underflow;
    Node*prev=Node_front;
    Node_front=Node_front->next;
    delete prev;
    queue_size--;
    return success;
}

int LinkedQueue::top(){
    if(isempty()) return underflow;
    return Node_front->entry;
}

LinkedQueue::~LinkedQueue(){
    while(!isempty()){
        pop();
    }
}

int main()
{
    LinkedQueue test;
    int num;
    while(cin>>num&&num!=-1){
        test.LinkedQueue::push(num);
    }
    while(!test.LinkedQueue::isempty()){
        cout<<test.LinkedQueue::top()<<' ';
        test.LinkedQueue::pop();
    }
    cout<<endl;
    return 0;
}
