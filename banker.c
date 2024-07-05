                                                                                                                                                                                                               bankeral.c                                                                                                                                                                                                                              #include <stdio.h>
#include<stdlib.h>

int alloc[10][10],max[10][10],need[10][10],i,j,n,m;
void read(int a[10][10])
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        scanf("%d",&a[i][j]);
                }
        }
}
void display(int b[10][10])
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        printf("%d\t",b[i][j]);
                }
                printf("\n");
        }

}
void calculate()
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        need[i][j]=max[i][j]-alloc[i][j];
                }
        }

}
void banker()
{
        int avail[10],finished[10],flag,k,s,safeseq[10],index=0;

        for(i=0;i<n;i++)
        {
                finished[i]=0;
        }
        printf("Enter the available resoures\n");
        for(i=0;i<m;i++)
        {
                scanf("%d",&avail[i]);
        }
        for(s=0;s<n;s++)
        {
                for(i=0;i<n;i++)
                {
                        flag=0;
                        if(finished[i]==0)
                        {
                                for(j=0;j<m;j++)
                                {
                                        if(need[i][j]>avail[j])
                                        {
                                                flag=1;
                                                break;
                                        }
                                }
                                if(flag==0)
                                {
                                         finished[i]=1;
                                        safeseq[index]=i;
                                        index++;
                                        for(k=0;k<m;k++)
                                        {
                                                avail[k]+=alloc[i][k];
                                        }
                                }
                        }
                }



        }
        flag=1;
        for(i=0;i<n;i++)
        {
                if(finished[i]==0)
                {
                        printf("The system are not in safe state\n");

                        flag=0;
                        break;
                }
        }
        if(flag==1)
        {
                printf("The system are in safe state\n");
                for(i=0;i<n;i++)
                {
                        printf("p%d\t",safeseq[i]);
                }
        }

}
void main()
{
        printf("Enter the no process:");
        scanf("%d",&n);
        printf("ENter the no of resorces:");
        scanf("%d",&m);
        printf("ENter the alloc matrix\n");
        read(alloc);
        display(alloc);
        printf("ENter the max matrix\n");
        read(max);
        display(max);
        printf("Enter the need alloc\n");
        calculate();
        display(need);
        banker();
}

