#include<iostream>
using namespace std;

const int P = 5;


const int R = 4;
int i,j,p,k;

void calculateNeed(int need[P][R], int maxm[P][R],
                   int allot[P][R])
{
   for (i = 0 ; i < P ; i++)
        for (j = 0 ; j < R ; j++)

            need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int maxm[][R],
            int allot[][R])
{
    int need[P][R];
    calculateNeed(need, maxm, allot);

    bool finish[P] = {0};
    int safeSeq[P];

    int work[R];
    for (i = 0; i < R ; i++)
        work[i] = avail[i];
    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (p = 0; p < P; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == R)
                {
                    for (k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;

                    found = true;
                }
            }
        }
        if (found == false)
        {
            printf("System is not in safe state");   
            return false;
        }
    }
    printf("System is in safe state.\nsafe sequence is :");
    for (i = 0; i < P ; i++)
         printf("\t%d",safeSeq[i],"");   

    return true;
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {1, 5, 2, 0};

    int maxm[][R] = {{0, 0, 1, 2},
                     {1, 7, 5, 0},
                     {2, 3, 5, 6},
                     {0, 6, 5, 2},
                     {0, 6, 5, 6}};
    int allot[][R] = {{0, 0, 1, 2},
                      {1, 0, 0, 0},
                      {1, 3, 5, 4},
                      {0, 6, 3, 2},
                      {0, 0, 1, 4}};
    isSafe(processes, avail, maxm, allot);

    return 0;
}

