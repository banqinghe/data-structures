#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<int> color[3];
    int num,i;
    while(cin>>num){
        color[num].push_back(num);
    }
    for(i=0;i<3;i++){
        while(!color[i].empty()){
            cout<<color[i].back()<<' ';
            color[i].pop_back();
        }
    }
    cout<<endl;
    return 0;
}