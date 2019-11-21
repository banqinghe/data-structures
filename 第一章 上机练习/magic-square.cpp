#include<stdio.h>
#include<string.h>

int main()
{
	int n,a[105][105];
	scanf("%d",&n);
	memset(a,0,sizeof(a));
	int x,y,i,j,tot;
	tot=a[x=0][y=n/2]=1;
	while(tot<n*n){
		if(x>0&&y<n-1&&a[x-1][y+1]==0) a[--x][++y]=++tot;
		else if(x>0&&y<n-1&&a[x-1][y+1]!=0) a[++x][y]=++tot;
		else if(x==0&&y<n-1) x=n;
		else if(x>0&&y==n-1) y=-1;
		else if(x==0&&y==n-1) a[++x][y]=++tot; 
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d",a[i][j]);
			if(j<n-1) printf("  ");
			else printf("\n");
		}
	}
	return 0;
}