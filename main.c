#include <stdio.h>
#include <stdbool.h>

const int i0 = 1;
const int j0 = -30;
const int l0 = 1;

int max(int x, int y){
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int min(int x, int y){
    if (x > y) {
        return y;
    } else {
        return x;
    }
}

int sign(int x){
    if (x > 0) {
        return 1;
    } else if (x < 0){
        return -1;
    } else {
        return 0;
    }
}

int abs(int x){
    if (x < 0){
        x = -x;
    }
    return x;
}

int mod(int x, int y){
    if ((x > 0 && y > 0) || (x < 0 && y < 0) || x == (x / y) * y ){
        return x - x / y * y;
    } else {
        return x - y * (x / y - 1);
    }
}

bool checker(int i, int j){
    int len = (i - 10)*(i - 10) + (j - 10)*(j - 10);
    if (len < 100 && len > 25){
        return true;
    } else {
        return false;
    }
}

void success(int i, int j, int l){
    int i1, j1, l1, k;
    for(k = 0; k <= 50; k++){
        i1 = max(min(i + j - l - k, i - j + l - k), min(k + i - j - l, k - i - j + l));
        j1 = j + mod(l * sign(j), 20) + k * mod(sign(i), 10);
        l1 = abs(i - j + l - k) * sign(i) * sign(j);
        i = i1; j = j1; l = l1;
        if (checker(i, j)){
            printf("YES\nTIME: %d\nCOORDINATES: %d, %d\nl = %d", k, i, j, l);
            break;
        }
    }
    if (k > 50){
        printf("NO");
    }
}

int main() {
    //success(i0, j0, l0);
    int a, b;
    while (true) {
    scanf("%d%d", &a, &b);
    printf("%d\n", mod(a, b));
    }
    return 0;
}
