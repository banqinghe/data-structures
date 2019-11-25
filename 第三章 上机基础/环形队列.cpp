#include<iostream>
#define maxn 100
using namespace std;

typedef  int Queue_entry;

enum Error_code{success,underflow,overflow};

class Queue{
public:
    Queue(){
        cnt=0;
        front=0;
        rear=maxn-1;
    }
    bool empty() const{
        if(cnt==0) return true;
        return false;
    }
    int size() const{
        return cnt;
    }
    bool full() const{
        if(cnt==maxn) return true;
        return false;
    }
    Error_code append(const Queue_entry &x){        /*入队*/
        if(!full()){
            myqueue[(++rear)%maxn]=x;
            cnt++;
            return success;
        }
        else return overflow;
    }
    Error_code serve(){                 /*出队*/
        if(!empty()){
            front++;
            cnt--;
        }
        else return underflow;
    }
    Error_code retrieve(Queue_entry &x) const{        /*访问队首*/
        if(!empty()){
            x=myqueue[front];
            return success;
        }
        return underflow;
    }
private:
    int cnt,front,rear;
    Queue_entry myqueue[maxn];
};

int main()
{
    Queue p;
    Queue_entry num;
    int cnt=0;
    while(cin>>num&&num!=-1){
        p.Queue::append(num);
        cnt++;
    }
    for(int i=0;i<cnt;i++){
        int n;
        p.Queue::retrieve(n);
        cout<<n<<' ';
        p.Queue::serve();
    }
    return 0;
}