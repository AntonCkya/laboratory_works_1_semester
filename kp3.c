#include <stdio.h>
#include <math.h>

const long double a = 0.0;
const long double b = 1.0;

long double getEps (){
    long double eps = 1;
    while (1 + eps / 2 > 1)
        eps /= 2.0;
    return eps;
}

long double getTaylor (long double taylor, long double x, int n){
    return (-1 * taylor * x * x) / ((2*n + 1) * 2*n);
}

int main(){
    
    int split;
    long double step, eps = getEps(), x;
    
    long double taylorSum, taylorElem;
    int taylorNum;
    
    printf("Введите количество разбиений:\n");
    scanf("%d", &split);
    step = (b - a) / split;
    
    printf("Машинное эпсилон: %.64Lf\n", eps);
    printf("|    x    |        sin(x)         |        Taylor         |   steps   |\n");
    
    for (int i = 0; i <= split; i++){
        x = a + i*step;
        
        taylorNum = 0;
        taylorElem = x;
        taylorSum = taylorElem;
        
        while ( taylorNum <= 100 && (taylorElem > eps || taylorElem < -eps) ){
            taylorNum++;
            taylorElem = getTaylor(taylorElem, x, taylorNum);
            taylorSum += taylorElem;
        }
        
        printf("| %.5Lf | %.19lf | %.19Lf | %.9d |\n", x, sin(x), taylorSum, taylorNum);
    }
    
    return 0;
}
