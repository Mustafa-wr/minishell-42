#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int i = 0;
    int k = 0;
    int tmp = 0;
    char    o[100] = "0000000\0";
    char    out[100] = "0000000\0";
    char MESSAGE[101];
    scanf("%[^\n]", MESSAGE);

    while (MESSAGE[i])
    {
        tmp = (int)MESSAGE[i];
        k = 0;
        while (k < 32)
        {
            out[k] = tmp % 2 + 48;
            tmp = tmp / 2;
            k++;
        }
        out[k] = '\0';
        tmp = 0;
        k--;
        while (k >= 0)
        {
            o[tmp] = out[k];
            k--;
            tmp++;
        }
        k = 0;
        while (o[k])
        {
            if (o[k] == '1')
            {
                printf("0 ");
                while (o[k] == '1')
                {
                    // if (k >= 5)
                    //     printf("k =  %d\n", k);
                    printf("0");
                    k++;
                    if (o[k] == '\0')
                    {
                        printf("0");
                    }
					else
             		   printf(" ");
                }
            }
            if (o[k] == '0')
            {
                 printf("00 ");
                while (o[k] == '0')
                {
                    printf("0");
                    k++;
                }
                printf(" ");
            }
            k++;
        }
		printf("        ");
        i++;
    }
    // printf("out. = %s", o);
    // printf("0");
    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    // printf("answer\n");

    return 0;
}