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
    Node* last;     //指向末尾的指针
    public:
    Node();
    Node(Node_entry item,Node *add_on=NULL);
    Error_code input(Node_entry n);
    Error_code output();
    Error_code Node_insert(Node_entry index,Node_entry num);
    Error_code Node_delete(Node_entry n);
    Error_code Node_add(int t);
    Error_code Node_outdata(int i,int j);
    Error_code Josephus(int n,int m);
    ~Node();
};

Node::Node(){
    next=NULL;
}

Node::Node(Node_entry item,Node *add_on){
    entry=item;
    next=add_on;
}

Error_code Node::input(int n){      //输入n个数据
    int num;
    if(n>0){
        cin>>num;
        head=new Node(num);
        Node* cur=head;
        last=cur;
        for(int i=1;i<n;i++){
            cin>>num;
            Node* newptr=new Node(num);
            // prev=cur;
            cur->next=newptr;
            cur=newptr;
            last=cur;
        }
    }
    return success;
}

Error_code Node::output(){      //输出所有数据
    for(Node*cur=head;cur!=NULL;cur=cur->next){
        cout<<cur->entry<<' ';
    }
    cout<<endl;
    return success;
}

// Error_code Node::Node_delete(int n){     //删除第n个节点
//     Node* cur=head;
//     if(t==0){
//         head=cur->next;
//         delete cur;
//     }
//     else{
//         for(int i=0;i<t;i++){
//             prev=cur;
//             cur=cur->next;
//         }
//         prev->next=cur->next;
//         delete cur;
//     }
//     return success;
// }

Error_code Node::Node_delete(Node_entry n){        //删除所有的n
    while(head!=NULL&&head->entry==n){
        prev=head;
        head=head->next;
        delete prev;
    }
    prev=head;
    if(head!=NULL){
        for(Node*cur=head->next;cur!=NULL;){
            if(cur->entry==n){
                prev->next=cur->next;
                delete cur;
                cur=prev->next;
            }
            else{
                prev=prev->next;
                cur=cur->next;
            }
        }
    }
    return success;
}

Error_code Node::Node_insert(Node_entry index,Node_entry num){  //插入
    Node *cur=head;
    for(int i=0;cur!=NULL;i++,prev=cur,cur=cur->next){
        if(cur->entry==index){
            Node *newptr=new Node(num);
            prev=cur;
            newptr->next=cur->next;
            prev->next=newptr;
            cout<<i+1<<' ';
        }
    }
    cout<<endl;
}
// Error_code Node::Node_insert(int t,Node_entry temp){      //第t位置插入temp
//     // Node *ptr=head;
//     if(t==0){
//         Node *newptr=new Node(temp);
//         newptr->next=head;
//         head=newptr;
//     }
//     else{
//         Node *newptr=new Node(temp);
//         Node *cur=head;
//         for(int i=1;i<t;i++){
//             prev=cur;
//             cur=cur->next;
//         }
//         prev=cur;
//         newptr->next=cur->next;
//         cur->next=newptr;
//     }
//     return success;
// }

Error_code Node::Node_add(int t){       //计算总和
    Node *cur=head;
    int sum=0;
    for(int i=0;i<t;i++){
        sum+=cur->entry;
        cur=cur->next;
    }
    cout<<sum<<endl;
    return success;
}

Error_code Node::Node_outdata(int i,int j){     //输出i到j之间的数据
    Node *cur=head;
    for(int k=0;k<i;k++){
        cur=cur->next;
    }
    for(int k=i;k<=j;k++){
        cout<<cur->entry<<' ';
        cur=cur->next;
    }
    cout<<endl;
    return success;
}

Node::~Node(){       //删除链表中所有节点/析构函数
    if(head!=NULL){
        Node *cur=head->next;
        prev=head;
        delete prev;
        for(;cur!=NULL&&cur!=head;cur=cur->next){
            prev=cur;
            delete prev;
        }
    }
}

Error_code Node::Josephus(int n,int m){       //Josephus问题
    int cnt=0;
    Node*newptr=new Node(1);
    prev=newptr;
    head=newptr;
    for(int i=1;i<n;i++){
        Node*newptr=new Node(i+1);
        prev->next=newptr;
        prev=newptr;
    }
    Node*cur=head;
    prev->next=head;
    while(prev!=cur){
        cnt++;
        if(cur->next==NULL){
            cur->next=head;
        }
        if(cnt==m){
            prev->next=cur->next;
            if(cur==head){
                head=cur->next;
            }
            delete cur;
            cur=prev->next;
            cnt=0;
        }
        else{
            prev=cur;
            cur=cur->next;
            prev->next=cur;
        }
    }
    cout<<cur->entry<<endl;
    return success;
}

int main()
{
    int n,m;
    cin>>n>>m;
    Node p;
    // p.Node::input(n);
    p.Node::Josephus(n,m);
    // Node_entry num;
    // cin>>num;
    // p.Node::Node_delete(num);
    // cin>>x>>y;
    // p.Node::Node_insert(x,y);
    // p.Node::Node_outdata(i,j);
    // p.Node::output();
    // p.Node::Node_add(n);
    // p.Node::Node_insert(5,9);
    // p.Node::Node_delet(0);
    return 0;
}