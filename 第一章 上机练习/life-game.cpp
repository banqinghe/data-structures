#include<stdio.h>
#include<string.h>

int main()
{
	int a,b,area[22][62];
	memset(area,0,sizeof(area));
	while(scanf("%d%d",&a,&b)==2){
		if(a==-1&&b==-1) break;
		area[a][b]=1;
	}
	int t,i,j,k,l;
	scanf("%d",&t);
	while(t--){
		for(i=1;i<21;i++){
			for(j=1;j<61;j++){
				int cnt=0;
				for(k=i-1;k<=i+1;k++){
					for(l=j-1;l<=j+1;l++){
						if(k==i&&l==j) continue;
						if(area[k][l]==1||area[k][l]==2) cnt++;
					}
				}
				if(area[i][j]==1){
					if(cnt=0||cnt==1||cnt>=4) area[i][j]=2;/*将死*/
					else area[i][j]=1;
				}
				else if(cnt==3) area[i][j]=3; /*将活*/
			}
		}
		for(i=1;i<21;i++){
			for(j=1;j<61;j++){
				if(area[i][j]==2) area[i][j]=0;
				else if(area[i][j]==3) area[i][j]=1;
			}
		}
	}
	for(i=1;i<21;i++){
		for(j=1;j<61;j++){
			if(area[i][j]==1) printf("*");
			else printf("-");
		}
		printf("\n");
	}
	return 0;
}