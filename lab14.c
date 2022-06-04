#include <stdio.h>
//Вариант 13

int main(void)
{
    int n;
    scanf("%d", &n);
    int arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    int reverse = 0;
    int rang = 1;
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i][n - i - 1]);
    while(reverse < 2*(n - 1)){
        if(reverse % 2 == 0){
            for (int i = n - 1; i >= rang; i--)
                printf("%d ", arr[i - rang][n - i - 1]);
            for (int i = n - 1; i >= rang; i--)
                printf("%d ", arr[i][rang + (n - i) - 1]);
            rang++;
        }  
        else{
            for (int i = 0; i < n - rang; i++)
                printf("%d ", arr[i + rang][n - i - 1]);
            for (int i = 0; i < n - rang; i++)
                printf("%d ", arr[i][n - rang - (i + 1)]);
            rang++;
        }
        reverse++;
    }
    return 0;
}
