#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point{
    int x,y,quadrant;
};

bool cmp(const Point& p1,const Point& p2){
    double d1=sqrt(pow((double)p1.x,2.0)+pow((double)p1.y,2.0));
    double d2=sqrt(pow((double)p2.x,2.0)+pow((double)p2.y,2.0));
    if(d1!=d2) return d1<d2;
    return p1.quadrant<p2.quadrant;
}

int main()
{
    int k,cnt=0,a,b;
    cin>>k;
    Point point[1000];
    while(cin>>a>>b){
        point[cnt].x=a;
        point[cnt].y=b;
        if(a>0&&b>0) point[cnt].quadrant=1;
        else if(a<0&&b>0) point[cnt].quadrant=2;
        else if(a<0&&b<0) point[cnt].quadrant=3;
        else point[cnt].quadrant=4;
        cnt++;
    }
    sort(point,point+cnt,cmp);
    for(int i=0;i<k;i++)
        cout<<point[i].x<<' '<<point[i].y<<' ';
    cout<<endl;
    return 0;
}