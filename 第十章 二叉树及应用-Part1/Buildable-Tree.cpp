#include <iostream>
#include <stack>
#include <list>
using namespace std;

struct Record{
    string key,other;
    bool operator<(const Record &item){
        return key<item.key;
    }
    bool operator<=(const Record &item){
        return (key<item.key)||(key==item.key);
    }
    bool operator>(const Record &item){
        return key>item.key;
    }
    bool operator==(const Record &item){
        return key==item.key;
    }
    Record& operator=(const Record &item){
        this->key=item.key;
        this->other=item.other;
        return *this;
    }
};

ostream& operator<<(ostream &out, Record &item){
    out<<item.key<<' '<<item.other;
}

template <class Node_entry>
struct Node{
    Node_entry data;
    Node<Node_entry> *left;
    Node<Node_entry> *right;
    Node();
    Node(const Node_entry &);
};

template <class Node_entry>
Node<Node_entry>::Node(){
    left=NULL;
    right=NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(const Node_entry &x){
    data=x;
    left=NULL;
    right=NULL;
}

template <class Entry>
class Binary_tree{
public:
    Binary_tree();
    bool empty() const;
    void preorder(void (*visit)(Entry &));
    void recursive_preorder(Node<Entry>* sub_root,void (*visit)(Entry &));
    void inorder(void (*visit)(Entry &));
    void recursive_inorder(Node<Entry>* sub_root,void (*visit)(Entry &));
    void postorder(void (*visit)(Entry &));
    void recursive_postorder(Node<Entry>* sub_root,void (*visit)(Entry &));
    int size() const;
    void clear();
    void recursive_delete(Node<Entry>* sub_root);
    int height() const;
    void insert(const Entry &);
    Binary_tree (const Binary_tree<Entry> &original);
    Binary_tree & operator=(const Binary_tree<Entry> &original);
    ~Binary_tree();
// protected:
    int cnt;
    Node<Entry> *root;
};

template <class Entry>
Binary_tree<Entry>::Binary_tree(){
    root=NULL;
    cnt=0;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const{
    return root==NULL;
}

template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &)){
    recursive_preorder(root,visit);
    cout<<endl;
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Node<Entry>* sub_root,void (*visit)(Entry &)){
    if(sub_root!=NULL){
        (*visit)(sub_root->data);
        recursive_preorder(sub_root->left,visit);
        recursive_preorder(sub_root->right,visit);
    }
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &)){
    recursive_inorder(root,visit);
    cout<<endl;
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Node<Entry>* sub_root,void (*visit)(Entry &)){
    if(sub_root!=NULL){
        recursive_inorder(sub_root->left,visit);
        (*visit)(sub_root->data);
        recursive_inorder(sub_root->right,visit);
    }
}

template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &)){
    recursive_postorder(root,visit);
    cout<<endl;
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Node<Entry> *sub_root,void (*visit)(Entry &)){
    if(sub_root!=NULL){
        recursive_postorder(sub_root->left,visit);
        recursive_postorder(sub_root->right,visit);
        (*visit)(sub_root->data);
    }
}

template <class Entry>
int Binary_tree<Entry>::size() const{
    return cnt;
}

template <class Entry>
void Binary_tree<Entry>::clear(){
    recursive_delete(root);
}

template <class Entry>
void Binary_tree<Entry>::recursive_delete(Node<Entry>* sub_root){
    if(sub_root!=NULL){
        recursive_delete(sub_root->left);
        recursive_delete(sub_root->right);
        delete sub_root;
    }
}

template <class Entry>
int Binary_tree<Entry>::height() const{
    int i,temp_cnt=cnt;
    for(i=-1;temp_cnt;i++){
        temp_cnt/=2;
    }
    return i;
}

template <class Entry>
void Binary_tree<Entry>::insert(const Entry &x){
    if(cnt==0){
        root=new Node<Entry>(x);
        // cout<<"It is a root node"<<endl;
        cnt++;
        return;
    }
    stack<int> numbers;
    int item=0,temp_cnt=cnt;
    while(temp_cnt>0){
        int a=(temp_cnt-1)/2;
        int b=(temp_cnt-2)/2;
        if(temp_cnt>1 && a==b){ //right child
            numbers.push(2);    //stand for right child
            cout<<"It is right a node"<<endl;
        }
        else{
            numbers.push(1);    //stand for left child
            // cout<<"It is left a node"<<endl;
        }
        temp_cnt=(temp_cnt-1)/2;
    }
    // cout<<"-------------"<<endl;
    Node<Entry>* current=root;
    while(numbers.size()>1){
        item=numbers.top();
        if(item==1) current=current->left;
        else if(item==2) current=current->right;
        numbers.pop();
    }
    item=numbers.top();
    if(item==1) current->left=new Node<Entry>(x);
    else if(item==2) current->right=new Node<Entry>(x);
    cnt++;
}

template <class Entry>
Binary_tree<Entry>::~Binary_tree(){
    clear();
}

template <class Entry>
void Print(Entry &x){
    cout<<x<<' ';
}

template <class Entry>
class Search_tree : public Binary_tree<Entry>{
public:
    void insert(const Entry& new_data);
    void remove(const Entry &target);
    void search_and_insert(Node<Entry>* &,const Entry&);
    void remove_root(Node<Entry>* &sub_root);
    void search_and_destroy(Node<Entry>* &sub_root,const Entry &target);
    void search(const Entry& target);
    void search_and_display(Node<Entry>* sub_root,const Entry &target);
private:
};

template <class Entry>
void Search_tree<Entry>::insert(const Entry& new_data){
    search_and_insert(this->root,new_data);
}

template <class Entry>
void Search_tree<Entry>::search_and_insert(Node<Entry>* &sub_root,const Entry &new_data){
    if(sub_root==NULL)
        sub_root=new Node<Entry>(new_data);
    else if(sub_root->data>new_data)
        search_and_insert(sub_root->left,new_data);
    else if(sub_root->data<new_data)
        search_and_insert(sub_root->right,new_data);
}


template <class Entry>
void Search_tree<Entry>::remove(const Entry &target){
    search_and_destroy(this->root,target);
    this->cnt--;
}

//Page456 分三种情况进行删除操作
template <class Entry>
void Search_tree<Entry>::remove_root(Node<Entry>* &sub_root){
    if(sub_root==NULL) return;
    Node<Entry> *to_delete=sub_root;
    if(sub_root->right==NULL) sub_root=sub_root->left;
    else if(sub_root->left==NULL) sub_root=sub_root->right;
    else{
        to_delete=sub_root->left;
        Node<Entry>* parent=sub_root;
        while(to_delete->right!=NULL){
            parent=to_delete;
            to_delete=to_delete->right;
        }
        sub_root->data=to_delete->data;
        if(parent==sub_root) sub_root->left=to_delete->left;
        else parent->right=to_delete->left;
    }
    delete to_delete;
}

template <class Entry>
void Search_tree<Entry>::search_and_destroy(Node<Entry>*& sub_root,const Entry &target){
    if(sub_root==NULL||sub_root->data==target)
        remove_root(sub_root);
    else if(sub_root->data<target)
        search_and_destroy(sub_root->right,target);
    else
        search_and_destroy(sub_root->left,target);
}

template <class Entry>
void Search_tree<Entry>::search(const Entry& target){
    if(this->root==NULL){
        cout<<"NULL"<<endl;
        return;
    }
    search_and_display(this->root,target);
}

template <class Entry>
void Search_tree<Entry>::search_and_display(Node<Entry>* sub_root,const Entry &target){
    if(sub_root->data==target)
        cout<<sub_root->data<<endl;
    else if(sub_root->right!=NULL&&sub_root->data<target){
        cout<<sub_root->data.key<<' ';
        search_and_display(sub_root->right,target);
    }
    else if(sub_root->right==NULL&&sub_root->data<target){
        cout<<sub_root->data.key<<" NULL"<<endl;
    }
    else if(sub_root->left!=NULL&&sub_root->data>target){
        cout<<sub_root->data.key<<' ';
        search_and_display(sub_root->left,target);
    }
    else if(sub_root->left==NULL&&sub_root->data>target){
        cout<<sub_root->data.key<<" NULL"<<endl;
    }
}

template <class Entry>
class Buildable_tree : public Search_tree<Entry>{
public:
    void build_tree(const list<Entry> &supply);
    void build_insert(int cnt,const Entry &new_data,list<Node<Entry>* > &last_node);
    Node<Entry>* find_root(list<Node<Entry>* > &last_node);
    void connect_trees(const list<Node<Entry>* > &last_node);
private:
};

template <class Entry>
void Buildable_tree<Entry>::build_tree(const list<Entry> &supply){
    int cnt=0;
    Entry x,last_x;
    list< Node<Entry>* > last_node; // 指针链表
    Node<Entry>* none=NULL;
    last_node.insert(last_node.begin(),none);   // 先把指针链表首位置赋为0
    
    while(cnt<supply.size()){   // last_x是上一个x
        typename list<Entry>::const_iterator it=supply.begin();   // 指向待建树的list的迭代器it
        advance(it,cnt);
        x=*it;
        // cout<<x<<endl;
        if(cnt>0&&x<=last_x){
            break;
        }
        build_insert(++cnt,x,last_node);
        last_x=x;
    }
    this->cnt=cnt;
    this->root=find_root(last_node);
    connect_trees(last_node);
}

template <class Entry>
void Buildable_tree<Entry>::build_insert(int cnt,const Entry &new_data,list<Node<Entry>* > &last_node){
    int level;
    // cout<<"the cnt is "<<cnt<<' ';
    for(level=1;cnt%2==0;level++)
        cnt/=2; // 通过能整除2的几次方来判断所属层数
    // cout<<"the level is "<<level<<endl;
    Node<Entry> *next_node=new Node<Entry>(new_data),*parent;
    typename list<Node<Entry>* >::iterator it=last_node.begin();
    advance(it,level-1);
    next_node->left=*it;    // 放置左节点
    typename list<Node<Entry>* >::iterator it1=last_node.begin();
    advance(it1,level);
    if(last_node.size()<=level)
        last_node.insert(it1,next_node);
    else
        *it1=next_node;
    if(last_node.size()>level+1){
        typename list<Node<Entry>* >::iterator it2=last_node.begin();
        advance(it2,level+1);
        parent=*it2;
        if(parent->right==NULL)
            parent->right=next_node;
    }
}

template <class Entry>
Node<Entry>* Buildable_tree<Entry>::find_root(list<Node<Entry>* > &last_node){
    Node<Entry>* high_node;
    typename list<Node<Entry>* >::iterator it=last_node.begin();
    advance(it,last_node.size()-1);
    high_node=*it;
    return high_node;
}

template <class Entry>
void Buildable_tree<Entry>::connect_trees(const list<Node<Entry>* > &last_node){
    Node<Entry> *high_node,*low_node;
    int high_level=last_node.size()-1, low_level;
    while(high_level>2){
        typename list<Node<Entry>* >::const_iterator it=last_node.begin();
        advance(it,high_level);
        high_node=*it;
        if(high_node->right!=NULL)
            high_level--;
        else{
            low_level=high_level;
            do{
                typename list<Node<Entry>* >::const_iterator it=last_node.begin();
                advance(it,--low_level);
                low_node=*it;
            }
            while(low_node!=NULL&&low_node->data < high_node->data);
            high_node->right=low_node;
            high_level=low_level;
        }
    }
}

int main()
{
    list<Record> supply;
    string key,other;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>key>>other;
        supply.push_back({key,other});
    }
    Buildable_tree<Record> p;
    p.build_tree(supply);
    cin>>key;
    p.search({key,other});
    cin>>key;
    p.search({key,other});
    return 0;
}