#include <stdio.h>
#include <stdlib.h>

int n,r[20],intial,temp[20],size;

void fcfs()
{
        int i,current=intial,seek=0;

        for(i=0;i<n;i++)
        {
                seek+=abs(r[i]-current);
                current=r[i];
        }
        printf("total seek time in fcfs %d\n",seek);

}
void scan()
{
        int index=0,current=intial,i,j,seek=0,temp_v;

        //sorting
        for(i=0;i<n;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(temp[j]>temp[j+1])
                        {
                                temp_v=temp[j];
                                temp[j]=temp[j+1];
                                temp[j+1]=temp_v;
                        }
                }
        }

        for(i=0;i<n;i++)
        {
                if(current<temp[i])
                {
                        index=i;
                        break;
                }
        }

        for(i=index;i<n;i++)
        {
                seek+=abs(temp[i]-current);
                current=temp[i];
        }
        seek+= abs(size-1-current);
        current=size-1;

        for(i=index-1;i>=0;i--)
        {
                seek+=abs(current-temp[i]);
                current=temp[i];
        }
         printf("total seek time in scan %d\n",seek);
}
void cscan()
{
        int i,j,current=intial,seek=0,temp_v,index=0;

        for(i=0;i<n;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(temp[j]>temp[j+1])
                        {
                                temp_v=temp[j];
                                temp[j]=temp[j+1];
                                temp[j+1]=temp_v;
                        }
                }
        }
        for(i=0;i<n;i++)
        {
                if(current<temp[i])
                {
                        index=i;
                        break;
                }
        }
        for(i=index;i<n;i++)
        {
                seek+=abs(temp[i]-current);
                current=temp[i];
        }
        seek+=abs(size-1-current);
        current=size-1;

        seek+=current;
        current=0;

        for(i=0;i<index;i++)
        {
                seek+=abs(current-temp[i]);
                current=temp[i];
        }
         printf("total seek timei cscan %d\n",seek);
}
void main()
{
        int i;
        printf("Enter the no of disc");
        scanf("%d",&n);
        printf("ENter the disc nos\n");
        for(i=0;i<n;i++)
        {
                scanf("%d",&r[i]);
                temp[i]=r[i];
        }
        printf("ENter the initial no:");
        scanf("%d",&intial);
        printf("ENter the size");
        scanf("%d",&size);
        fcfs();
        scan();
        cscan();
}

