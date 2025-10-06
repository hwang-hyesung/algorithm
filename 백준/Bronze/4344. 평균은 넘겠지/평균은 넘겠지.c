#include <stdio.h>
#include <stdlib.h>

int main()
{
   int i, j, C, N, sum=0,a=0;
   float average=0, percent;
   scanf(" %d", &C);
   for(i=0;i<C;i++){
        scanf(" %d ", &N);
        int str[N];

        for(j=0;j<N;j++){
            scanf(" %d", &str[j]);
            sum += str[j];
        }
        average = sum*1.0/ N;
        for(j=0;j<N;j++){
            if(str[j]>average){
                a++;
            }else
                continue;
        }
        percent = a*100.0/N;
        printf("%.3f%%\n", percent);
        a=0;
        sum=0;
   }



}
