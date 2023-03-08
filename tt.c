#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    int k = 0;
    int sum;
    scanf("%d", &n); fgetc(stdin);
    for (int i = 0; i < n; i++) {
        char fruits[1025];
        scanf("%[^\n]", fruits); fgetc(stdin);
         if (fruits[0] == 'l')
            sum += 100;
        else if (fruits[0] == 'p')
            sum += 75;
        else if (fruits[0] == 'z')
            sum += 25;
        // k++;
    }
	printf("%d", sum);
}