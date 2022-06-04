#include <stdio.h>
#include <math.h>

typedef double (*fun)(double);

typedef struct {
    double root;
    int iters;
    int success;
} result;   

double aabs(double x){
    if (x < 0)
        return -x;
    return x;
}

double fun13(double x){
    return x*tan(x) - 1/(double)3;
}

double fun14(double x){
    return tan(x/2) - (1/tan(x/2)) + x;
}

double diff (fun f, double x){
    double eps = pow(2, -26);
    return (f(x + eps) - f(x - eps)) / (2*eps);
}

double secondDiff (fun f, double x){
    double eps = pow(2, -13);
    return (f(x + eps) - 2*f(x) + f(x - eps)) / (eps*eps);
}

double equalFun13 (double x){
    return x - 0.35*fun13(x);
}

double equalFun14 (double x){
    return x - 0.3*fun14(x);
}

result dichotomy (fun f, double a, double b){
    double eps = pow(2, -26);
    result res;
    res.iters = 0;
    double c;
    while (b - a > eps){
        c = (a + b)/2;
        if (f(a)*f(c) < 0)
            b = c;
        else
            a = c;
        res.iters++;
    }
    res.root = (a+b)/2;
    res.success = 1;
    return res;
}

result iterations (fun f, double a, double b){
    result res;
    res.iters = 1;
    double eps = pow(2, -26);
    double x0 = (a + b)/2;
    double x1 = f(x0);
    if (diff(f, x0) >= 1){
        res.success = 0;
        return res;
    }
    while (aabs(x0 - x1) > eps){
        x0 = x1;
        if (diff(f, x0) >= 1){
            res.success = 0;
            return res;
        }
        x1 = f(x0);
        res.iters++;
    }
    res.root = x1;
    res.success = 1;
    return res;
    
}

result newton (fun f, double a, double b){
    result res;
    res.iters = 1;
    double x0 = (a+b)/2;
    double x1 = x0 - f(x0)/diff(f, x0);
    double eps = pow(2, -26);
    if (aabs(f(x0) * secondDiff(f, x0)) > diff(f, x0)*diff(f, x0)){
        res.success = 0;
        return res;
    }
    while (aabs(x0 - x1) > eps){
        x0 = x1;
        if (aabs(f(x0) * secondDiff(f, x0)) > diff(f, x0)*diff(f, x0)){
            res.success = 0;
            return res;
        }
        x1 = x0 - f(x0)/diff(f, x0);
        res.iters++;
    }
    res.root = x1;
    res.success = 1;
    return res;
    
}

int main(){
    result x1, x2, x3, x4, x5, x6;
        printf("|         Уравнение         |   Отрезок   |   Метод   |  Число итераций  |      Результат      |\n");
    x1 = dichotomy(fun13, 0.2, 1);
    if (x1.success)
        printf("|    x * tg(x) - 1/3 = 0    | [ 0.2 ; 1 ] | Дихотомия | %.16d | %.17f |\n", x1.iters, x1.root);
    x2 = iterations(equalFun13, 0.2, 1);
    if (x2.success)
        printf("|    x * tg(x) - 1/3 = 0    | [ 0.2 ; 1 ] |  Итераций | %.16d | %.17f |\n", x2.iters, x2.root);
    x3 = newton(fun13, 0.2, 1);
    if (x3.success)
        printf("|    x * tg(x) - 1/3 = 0    | [ 0.2 ; 1 ] |   Ньютон  | %.16d | %.17f |\n", x3.iters, x3.root);
    x4 = dichotomy(fun14, 1, 2);
    if (x4.success)
        printf("| tg(x/2) - ctg(x/2) + x = 0|  [ 1 ; 2 ]  | Дихотомия | %.16d | %.17f |\n", x4.iters, x4.root);
    x5 = iterations(equalFun14, 1, 2);
    if (x5.success)
        printf("| tg(x/2) - ctg(x/2) + x = 0|  [ 1 ; 2 ]  |  Итераций | %.16d | %.17f |\n", x5.iters, x5.root);
    x6 = newton(fun14, 1, 2);
    if (x6.success)
        printf("| tg(x/2) - ctg(x/2) + x = 0|  [ 1 ; 2 ]  |   Ньютон  | %.16d | %.17f |\n", x6.iters, x6.root);
    return 0;
}
