#include<stdio.h>

int main()
{
	int line[64]={0},coor,i,j,t;
	while(scanf("%d",&coor)==1&&coor!=-1)
		line[coor+1]=1;
	scanf("%d",&t);
	while(t--){
		for(i=2;i<62;i++){
			int cnt=0;
			for(j=i-2;j<=i+2;j++){
				if(j==i) continue;
				if(line[j]==1||line[j]==2) cnt++;
			}
			if(line[i]==1&&(cnt==0||cnt==1||cnt==3)) line[i]=2;
			else if(line[i]==0&&(cnt==2||cnt==3)) line[i]=3;
		}
		for(i=2;i<62;i++){
			if(line[i]==2) line[i]=0;
			else if(line[i]==3) line[i]=1;
		}
	}
	for(i=2;i<62;i++){
		if(line[i]==1) printf("*");
		else if(line[i]==0) printf("-");
	}
	printf("\n");
	return 0;
}