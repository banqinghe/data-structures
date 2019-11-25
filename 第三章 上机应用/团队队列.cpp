#include<iostream>
using namespace std;

struct Team{
    int teamnum,id;
};

int main()
{
    int t,cas=1;
    while(cin>>t&&t){
        cout<<"Scenario #"<<cas++<<endl; 
        Team team[1000],temp,*p=&team[0];
        string commend;
        int cnt=0;
        while(cin>>commend&&commend!="STOP"){
            if(commend=="ENQUEUE"){
                cin>>team[cnt].teamnum>>team[cnt].id;
                for(int i=cnt-1;i>=0&&(&team[i]>=p);i--){
                    if(team[i].teamnum==team[cnt].teamnum){ /*如果有相同队伍的*/
                        temp=team[cnt];
                        for(int j=cnt;j>i+1;j--){
                            team[j]=team[j-1];
                        }
                        team[i+1]=temp;
                        break;
                    }
                }
                cnt++;
            }
            else if(commend=="DEQUEUE"){
                cout<<p->id<<endl;
                p++;
            }
		}
		cout<<endl;
	}
	return 0;
}