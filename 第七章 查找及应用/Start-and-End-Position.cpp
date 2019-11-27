#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Ans{
    int min,max;
};

void binarysearch_low(const vector<int> &text,int target,int bottom,int top,Ans &ans){
    if(bottom<=top){
        int mid=(top-bottom)/2+bottom;
        if(text[mid]==target){
            ans.min=mid;
            return binarysearch_low(text,target,bottom,mid-1,ans);
        }
        else if(text[mid]<target)
            return binarysearch_low(text,target,mid+1,top,ans);
        return binarysearch_low(text,target,bottom,mid-1,ans);
    }
}

void binarysearch_up(const vector<int> &text,int target,int bottom,int top,Ans &ans){
    if(bottom<=top){
        int mid=(top-bottom)/2+bottom;
        if(text[mid]==target){
            ans.max=mid;
            return binarysearch_up(text,target,mid+1,top,ans);
        }
        else if(text[mid]<target)
            return binarysearch_up(text,target,mid+1,top,ans);
        return binarysearch_up(text,target,bottom,mid-1,ans);
    }
}

int main()
{
    Ans ans;
    ans.min=-1;
    ans.max=-1;
    int target,temp;
    cin>>target;
    vector<int> text;
    while(cin>>temp&&temp!=-1){
        text.push_back(temp);
    }
    binarysearch_low(text,target,0,text.size()-1,ans);
    binarysearch_up(text,target,0,text.size()-1,ans);
    cout<<'['<<ans.min<<','<<ans.max<<']'<<endl;
    return 0;
}