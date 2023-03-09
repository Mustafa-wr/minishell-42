#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int time;
    int F;
    scanf("%d", &F);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int A;
        scanf("%d", &A);
        if (N == 0 && !A)
        {
            printf("11");
            time = F * 3;
            printf("%d", time);
            return (0);
        }
        else if (N && A)
        {
            printf("22");
            time = F * 3 + N * 2 + A * 2;
            printf("%d", time);
        }
        
    }
}