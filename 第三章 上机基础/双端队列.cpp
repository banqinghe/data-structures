#include<iostream>
#include<cctype>
#define maxn 1000
using namespace std;

typedef char Queue_entry;

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
    Error_code push_back(const Queue_entry &x){        /*从后面入队*/
        if(!full()){
            rear=(rear+1)%maxn;
            myqueue[rear]=x;
            cnt++;
            return success;
        }
        else return overflow;
    }
    Error_code push_front(const Queue_entry &x){        /*从前面入队*/
        if(!full()){
            front=(front+maxn-1)%maxn;
            myqueue[front]=x;
            cnt++;
            return success;
        }
        else return overflow;
    }
    Error_code serve_front(){                 /*从前面出队*/
        if(!empty()){
            front=(front+1)%maxn;
            cnt--;
        }
        else return underflow;
    }
    Error_code serve_back(){                 /*从后面出队*/
        if(!empty()){
            rear=(rear+maxn-1)%maxn;
            cnt--;
        }
        else return underflow;
    }
    Error_code retrieve_front(Queue_entry &x) const{        /*访问队首*/
        if(!empty()){
            x=myqueue[front];
            return success;
        }
        return underflow;
    }
    Error_code retrieve_back(Queue_entry &x) const{        /*访问队尾*/
        if(!empty()){
            x=myqueue[rear];
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
    Queue test;
    Queue_entry c;
    int t;
    cin>>t;
    while((c=getchar())!=EOF)
        if(isupper(c)) test.Queue::push_front(c);
    for(int i=0;i<t&&!test.Queue::empty();i++){
        char character;
        test.Queue::retrieve_front(character);
        cout<<character<<' ';
        test.Queue::serve_front();
    }
    cout<<endl;
    return 0;
}