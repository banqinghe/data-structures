#include<iostream>
using namespace std;

struct elem{
    int coe,index;      //coe为系数 index为指数
    bool ok;
    elem* next;
    // elem();
    elem(int a,int b,elem* add_on=NULL);
};

elem::elem(int a,int b,elem* add_on){
    coe=a;
    index=b;
    ok=true;
    add_on=NULL;
}

class Polynomial{
public:
    elem* head;
    elem* rear;
    int size;       //初始值为0
    
    Polynomial();
    ~Polynomial();
    // bool isempty();
    void read();
    void print();
};

Polynomial::Polynomial(){
    head=NULL;
    rear=NULL;
    size=0;
}

// bool Polynomial::isempty(){
//     return size==0;
// }

void Polynomial::read(){
    int a,b;
    while(cin>>a>>b&&(a||b)){
        if(size==0){
            head=new elem(a,b);
            rear=head;
            size++;
        }
        else{
            elem* newptr=new elem(a,b);
            rear->next=newptr;
            rear=newptr;
            size++;
        }
    }
    return ;
}

void Polynomial::print(){
    bool flag=true;      //判断是不是要输出的第一个元素
    for(elem* cur=head;cur!=NULL;cur=cur->next){
        if(cur->coe==0) continue;
        
        if(!flag)
            if(cur->coe>0) cout<<'+';
        if(flag) flag=false;
        
        if(cur->index==0){
            cout<<cur->coe;
            continue;
        }

        if(cur->coe==-1) cout<<'-';
        else if(cur->coe!=1) cout<<cur->coe;
        cout<<'X';

        if(cur->index!=1) cout<<'^'<<cur->index;

    }
    if(flag) cout<<'0';
    cout<<endl;
    return ;
}

Polynomial::~Polynomial(){
    elem* cur=head;
    elem* prev=NULL;
    while(cur!=head){
        prev=cur;
        delete prev;
        cur=cur->next;
    }
}

Polynomial add(Polynomial &p,Polynomial &q){
    Polynomial r;
    for(elem* cur1=p.head;cur1!=NULL;cur1=cur1->next){
        bool flag=false;
        for(elem* cur2=q.head;cur2!=NULL;cur2=cur2->next){
            if(cur2->next==NULL) flag=true;
            if(cur1->index==cur2->index){           //指数相同 进行运算
                cur1->ok=false;
                cur2->ok=false;
                if(r.size==0){
                    r.head=new elem(cur1->coe+cur2->coe,cur1->index);
                    r.rear=r.head;
                    r.size++;
                }
                else{
                    elem* newptr=new elem(cur1->coe+cur2->coe,cur1->index);
                    r.rear->next=newptr;
                    r.rear=newptr;
                    r.size++;
                }
                break;
            }
            else if(cur1->index < cur2->index){
                if(cur2->ok==false){
                    continue;
                }
                else if(cur2->ok==true){
                    cur2->ok=false;
                    if(r.size==0){
                        r.head=new elem(cur2->coe,cur2->index);
                        r.rear=r.head;
                        r.size++;
                    }
                    else{
                        elem* newptr=new elem(cur2->coe,cur2->index);
                        r.rear->next=newptr;
                        r.rear=newptr;
                        r.size++;
                    }
                    continue;
                }
            }
            else{
                cur1->ok=false;
                if(r.size==0){
                    r.head=new elem(cur1->coe,cur1->index);
                    r.rear=r.head;
                    r.size++;
                }
                else{
                    elem* newptr=new elem(cur1->coe,cur1->index);
                    r.rear->next=newptr;
                    r.rear=newptr;
                    r.size++;
                }
                break;
            }
            
        }
        if(cur1->ok==true&&flag==true){
            cur1->ok=false;
            if(r.size==0){
                r.head=new elem(cur1->coe,cur1->index);
                r.rear=r.head;
                r.size++;
            }
            else{
                elem* newptr=new elem(cur1->coe,cur1->index);
                r.rear->next=newptr;
                r.rear=newptr;
                r.size++;
            }
        }
    }
    for(elem* cur2=q.head;cur2!=NULL;cur2=cur2->next){
        if(cur2->ok==true){
            cur2->ok=false;
            if(r.size==0){
                r.head=new elem(cur2->coe,cur2->index);
                r.rear=r.head;
                r.size++;
            }
            else{
                elem* newptr=new elem(cur2->coe,cur2->index);
                r.rear->next=newptr;
                r.rear=newptr;
                r.size++;
            }
        }
    }
    return r;
}

Polynomial minus2(Polynomial &p,Polynomial &q){
    Polynomial r;
    for(elem* cur2=q.head;cur2!=NULL;cur2=cur2->next){
        cur2->coe=-cur2->coe;
    }
    r=add(p,q);
    return r;
}

Polynomial branch_multiply(int b_coe,int b_index,Polynomial p){
    Polynomial r;
    r.head=new elem(b_coe*p.head->coe,b_index+p.head->index);
    r.rear=r.head;
    r.size=1;
    if(p.size!=1){
        for(elem* cur=p.head->next;cur!=NULL;cur=cur->next){
            elem* newptr=new elem(b_coe*cur->coe,b_index+cur->index);
            r.rear->next=newptr;
            r.rear=newptr;
            r.size++;
        }
    }
    return r;
}

Polynomial multiply(Polynomial &p,Polynomial &q){
    Polynomial r;
    int sum=p.size;
    Polynomial poly[sum];
    elem* cur=p.head ;
    for(int i=0;i<sum ;i++){
        // cout<<"cur->coe="<<cur->coe<<" cur->index="<<cur->index<<endl;
        poly[i]=branch_multiply(cur->coe,cur->index,q);
        cur=cur->next;
    }
    r=poly[0];
    for(int i=1;i<sum;i++){
        r=add(r,poly[i]);
    }
    return r;
}

Polynomial do_commend(char commend,Polynomial &p,Polynomial &q){
    Polynomial r;
    switch (commend){
        case '+':
            r=add(p,q);
            break;
        case '-':
            r=minus2(p,q);
            break;
        case '*':
            r=multiply(p,q);
            break;
        default:
            cout<<"wrong commend!"<<endl;
    }
    return r;
}


int main()
{
    char commend;
    cin>>commend;
    Polynomial p,q,r;
    p.read();
    q.read();
    r=do_commend(commend,p,q);
    r.print();
    // p.print();
    // q.print();
    return 0;
}