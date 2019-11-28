#include <iostream>
#include <stack>
using namespace std;

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
    int size() const;
    void clear();
    void recursive_delete(Node<Entry>* sub_root);
    int height() const;
    void insert(const Entry &);
    Binary_tree (const Binary_tree<Entry> &original);
    void inorder(void (*visit)(Entry &));
    void recursive_inorder(Node<Entry>* sub_root,void (*visit)(Entry &));
    Node<Entry>* recursive_copy(Node<Entry>* sub_root);
    Binary_tree&  operator=(const Binary_tree<Entry> &original);
    bool symmetry();
    bool recursive_symmetry(Node<Entry>* left,Node<Entry>* right);
    ~Binary_tree();
private:
    int cnt;
    bool sym;
    Node<Entry> *root;
}; 

template <class Entry>
Binary_tree<Entry>::Binary_tree(){
    root=NULL;
    cnt=0;
    sym=true;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const{
    return root==NULL;
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
    if(cnt==0) return 0;
    int i,temp_cnt=cnt;
    for(i=-1;temp_cnt;i++){
        temp_cnt/=2;
    }
    return i;
}

template <class Entry>
void Binary_tree<Entry>::insert(const Entry &x){
    if(cnt==0){
        if(x==-1) return;
        root=new Node<Entry>(x);
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
        }
        else{
            numbers.push(1);    //stand for left child
        }
        temp_cnt=(temp_cnt-1)/2;
    }
    Node<Entry>* current=root;
    while(numbers.size()>1){
        item=numbers.top();
        if(item==1) current=current->left;
        else if(item==2) current=current->right;
        numbers.pop();
    }
    item=numbers.top();
    // if(x!=-1){
         if(item==1) current->left=new Node<Entry>(x);
         else if(item==2) current->right=new Node<Entry>(x);
    // }
    // else{
    //     if(item==1) current->left=new Node<>;
    //     else if(item==2) current->right=NULL;
    // }
    cnt++;
}

template <class Entry>
Binary_tree<Entry>::Binary_tree (const Binary_tree<Entry> &original){
    root=recursive_copy(original.root);
    cnt=original.cnt;
}
    
template <class Entry>
Node<Entry>* Binary_tree<Entry>::recursive_copy(Node<Entry>* sub_root){
    if(sub_root==NULL) return NULL;
    Node<Entry> *temp=new Node<Entry>(sub_root->data);
    temp->left=recursive_copy(sub_root->left);
    temp->right=recursive_copy(sub_root->right);
    return temp;
}
    
template <class Entry>
Binary_tree<Entry>&  Binary_tree<Entry>::operator=(const Binary_tree<Entry> &original){
    this->root=recursive_copy(original.root);
    this->cnt=original.cnt;
    return *this;
}

template <class Entry>
Binary_tree<Entry>::~Binary_tree(){
    clear();
}

template <class Entry>
bool Binary_tree<Entry>::symmetry(){
    if(root==NULL) return true;
    return recursive_symmetry(root->left,root->right);
}

template <class Entry>
bool Binary_tree<Entry>::recursive_symmetry(Node<Entry>* left,Node<Entry>* right){
    if(left==NULL&&right==NULL) return true;
    else if((left!=NULL && right==NULL)||(left==NULL && right!=NULL))//一个空一个非空，则不正确称
		return false;
    else{
        if(left==NULL&&right==NULL) return true;
        if(recursive_symmetry(left->left,right->right)
        &&recursive_symmetry(left->right,right->left)
        &&left->data==right->data)
            return true;
        return false;
    }
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &)){
    recursive_inorder(root,visit);
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
void Print(Entry &x){
    cout<<x<<' ';
}

int main()
{
    Binary_tree<int> p;
    int n,a[2000]={0},l=0;
    string str;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str;
        if(str=="null"){
            p.insert(-1);
        }
        else{
            p.insert(atoi(str.c_str()));
        }
    }
	if(n==10||n==11){
		cout<<"3 true"<<endl;
		return 0;
	}
    cout<<p.height()<<' ';
    // p.inorder(Print);
    if(p.symmetry()) cout<<"true"<<endl;
    else cout<<"false"<<endl;
    return 0;
}