#include <iostream>
#include <list>
using namespace std;

int main(){
    int num;
    list<int> list1,list2;
    while(cin>>num&&num!=-1)
        list1.push_back(num);
    while(cin>>num&&num!=-1)
        list2.push_back(num);
    list<int>::iterator it1=list1.begin();
    list<int>::iterator it2=list2.begin();
    while(it1!=list1.end()&&it2!=list2.end()){
        if(*it1<=*it2){
            cout<<*it1<<' ';
            it1++;
        }
        else{
            cout<<*it2<<' ';
            it2++;
        }
    }
    while(it1!=list1.end()){
        cout<<*it1<<' ';
        it1++;
    }
    while(it2!=list2.end()){
        cout<<*it2<<' ';
        it2++;
    }
    cout<<endl;
    return 0;
}

