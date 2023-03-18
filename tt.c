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
    int sum = 0;
    int j = 0;
    char   tmp[101];
	char	tmp2[101];
    int i = 0;
    char MESSAGE[101];
    scanf("%[^\n]", MESSAGE);
    // while (MESSAGE[j])
    // {
    //     sum += (int)MESSAGE[j];
    //     j++;
    // }
	// printf("sum = %d\n", sum);
    j = 0;
    while (i < 101)
    {
        tmp[i] = '\0';
        i++;
    }
    i = 0;
	j = 0;
	sum = (int)MESSAGE[i];
	printf("sum out= %d\n", sum);
    while (i < strlen(MESSAGE))
    {
        tmp[j] = (char)sum % 2 + 48;
        sum = sum / 2;
		printf("tmp = %c\n", tmp[j]);
		printf("sum = %d", sum);
		if (sum == 0)
		{
			// tmp[j] = (char)sum % 2 + 48;
        	i++;
			sum = (int)MESSAGE[i];
		}
		j++;
    }
	// printf("j = %d\n", j);
	j--;
	i = 0;
	while (j >= 0)
	{
		tmp2[i] = tmp[j];
		j--;
		i++;
	}
	i = 0;
	printf("tmp2 = %s\n", tmp2);
	// j =
	while (tmp2[i])
	{
		if (tmp2[i] == '1')
		{
			printf("0 ");
			while (tmp2[i] && tmp2[i] == '1')
			{
				printf("0");
				i++;
			}
			if (tmp2[i] != '\0')
				printf(" ");
		}
		if (tmp2[i] == '0')
		{
			printf("00 ");
			while (tmp2[i] && tmp2[i] == '0')
			{
				printf("0");
				i++;
			}
			if (tmp2[i] != '\0')
				printf(" ");
		}
		// i++;
	}
	// printf("tmp2 = %s\n", tmp2);
    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    // printf("tmp = %s\n", tmp);

    return 0;
}