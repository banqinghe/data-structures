#include<iostream>
using namespace std;

const int N=100;

class MYSTACK{
public :
    MYSTACK(int n){
        cnt=0;
        arr=new int [n];
    }
    /*~MYSTACK{
        delete arr;
    }*/
    bool pop(int &n){
        if(cnt==0)
            return false;
        else{
            cnt--;
            n=arr[cnt];
            return true;
        }
    }
    bool push(int n){
        if(cnt>=N)
            return false;
        else{
            arr[cnt++]=n;
            return true;
        }
    }
    bool top(int &n){
        if(cnt==0) return false;
        else n=arr[cnt-1];
        return true;
    }
    int sizet(){
        return cnt;
    }
    void clearr(){
        cnt=0;
    }
    bool full(){
        if(cnt==100) return true;
        return false;
    }

private :
    int cnt;
    int *arr;
};

int main()
{
    MYSTACK *p=new MYSTACK(100);
    int n,cnt;
    while(cin>>n&&n!=-1){
        p->MYSTACK::push(n);
    }
    cnt =p-> MYSTACK::sizet();
    for(int i=0;i<cnt-1;++i)
    {
            p->MYSTACK::pop(n);
            cout << n <<" ";
    }
    p->MYSTACK::pop(n);
    cout<< n <<endl;
    p->MYSTACK::clearr();
    return 0;
}
