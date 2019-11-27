#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

bool cmp(string a,string b){
        return a+b>b+a;
}

int main()                               {
        string line;
        getline(cin,line);                  
	stringstream str(line);      
	string temp,word[1005];
        int cnt=0;
        while(str>>temp){
                word[cnt++]=temp;
        }
        sort(word,word+cnt,cmp);
        for(int i=0;i<cnt;i++){
                cout<<word[i];
        }
        cout<<endl; return 0; }