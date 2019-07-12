#include<stdio.h>
#define MAX_VALUE 1000000000;

int i,j,k,x;
int time;
int TQ;
int no_of_process;
int BurstTime[40];
int arrTime[40];
int TAT[40];
int waitTime[40];
int remBurstTime[40];
int queue[40];


void maintainQueueRT();
void maintainQueueAT();

int main()
{
    printf("Enter the no of Process : ");
    scanf("%d",&no_of_process);

    printf("Enter Burst Time of each Process \n");
    for(i=0;i<no_of_process;i++)
    {
        printf("Process %d : ",i);
        scanf("%d",&BurstTime[i]);
        remBurstTime[i] = BurstTime[i];
        waitTime[i]=0;
        TAT[i]=0;
    }

    printf("Enter Arrival Time of each Process \n");
    for(i=0;i<no_of_process;i++)
    {
        printf("Process %d : ",i);
        scanf("%d",&arrTime[i]);
    }

    time=0;

    TQ = 3;
    maintainQueueAT();
    for(i=0;i<no_of_process;i++)
    {
        x = queue[i];
        if(time < arrTime[x])
        {
            time = arrTime[x];
        }
        if(time >= arrTime[x] && remBurstTime[x]!=0)
        {
            waitTime[x] +=  time - arrTime[x];
            if(remBurstTime[x] < TQ)
            {
                time += remBurstTime[x];
                remBurstTime[x]=0;
            }
            else
            {
                time +=TQ;
                remBurstTime[x] -= TQ;
            }
            TAT[x] = time;
        }
    }

    TQ = 6;
    for(i=0;i<no_of_process;i++)
    {
        int x = queue[i];
        if(remBurstTime[x]!=0)
        {
            waitTime[x] += time - TAT[x];
            if(remBurstTime[x]<TQ)
            {
                time += remBurstTime[x];
                remBurstTime[x]=0;
            }
            else
            {
                time +=TQ;
                remBurstTime[x] -= TQ;
            }
            TAT[x] = time;
        }
    }

    maintainQueueRT();

    for(i=0;i<no_of_process;i++)
    {
        k = queue[i];

        if(remBurstTime[k] != 0)
        {
            waitTime[k] += time - TAT[k];
            time += remBurstTime[k];
            remBurstTime[k]=0;
            TAT[k] = time;
        }
    }

    printf("\n\nProcess\t|Turn around Time|Waiting Time\n\n");
    for(i=0;i<no_of_process;i++)
    {
        printf("P[%d]\t|\t%d\t|\t%d\n",i,TAT[i]-arrTime[i],waitTime[i]);
    }

}

void maintainQueueAT()
{
    int cpyArray[no_of_process];
    for(i=0;i<no_of_process;i++)
        {
            cpyArray[i]=arrTime[i];
        }

    int min,k;
    k=0;
    for(i=0;i<no_of_process;i++)
    {
        min = 0;
        for(j=0;j<no_of_process;j++)
        {
            if(cpyArray[j]<cpyArray[min])
                min = j;
        }
        queue[k++] = min;
        cpyArray[min] = MAX_VALUE;
    }
}
void maintainQueueRT()
{
    int cpyArray[no_of_process];
    for(i=0;i<no_of_process;i++)
        cpyArray[i]=remBurstTime[i];

    int max,k;
    k=0;
    for(i=0;i<no_of_process;i++)
    {
        max = 0;
        for(j=0;j<no_of_process;j++)
        {
            if(cpyArray[j]<cpyArray[max])
                max = j;
        }
        queue[k++]=max;
        cpyArray[max] = -1;
    }
}
