#include<bits/stdc++.h>
using namespace std;

char a[12][12];
int vis[12][12];
const int d[][2]={{0,-1},{0,1},{1,0},{-1,0}};
int ans=1e9;

void dfs(int x, int y, int now)
{
    if(a[x][y]=='E'){
        ans=min(ans,now);
        return ;
    }
    for(int i = 0; i < 4; ++i){
        int nx=x+d[i][0];
        int ny=y+d[i][1];
        if(nx>=0&&ny>=0&&nx<12&&ny<12&&a[nx][ny]!='W'&&!vis[nx][ny]){
            vis[nx][ny]=1;
            dfs(nx,ny,now+1);
            vis[nx][ny]=0;
        }
    }
}

int main()
{
    int x=0,y=0;
    for(int i=0; i<12; ++i)
    for(int j=0; j<12; ++j) cin>>a[i][j];
    for(int i = 0; i < 3; i++) {
        char ch;
        cin>>ch>>x>>ch>>y>>ch;
        dfs(x,y,1);
        if(1e9==ans)cout << -1;
        else cout << ans ;
        ans=1e9;
        cout << ' ';
    }
    cout<<endl;
}