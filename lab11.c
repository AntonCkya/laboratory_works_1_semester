#include <stdio.h>
//Выделить все шестнадцатиричные числа, имеющие максимальное число цифр с 32-битной архитектуре
//Шестнадцатеричные числа в 32-битной архитектуре имеют максимум 8 цифр (без знака)
//Шестнадцатеричное число - число, состоящее из десятичных цифр и символов A B C D E F.

typedef enum {
    SEP,
    NUM,
    LITER,
    SIGN
} state;

int isNumber(int c){
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
}

unsigned long long getNumber(int c){
    if (c <= '9'){
        return c - '0';
    }
    return c - 'A' + 10;
}

unsigned long long toNumber(unsigned long long c){
    if (c <= 9){
        return c + '0';
    } else {
        return c - 10 + 'A';
    }
}

int isSep(int c){
    return (c == ' ' || c == 9 || c == EOF || c == ',' || c == '\n');
}

int isSign(int c){
    return (c == '+' || c == '-');
}

void to16(unsigned long long num, int sign){
    unsigned long long n;
    char a[8];
    int ch = 0;
    if (sign == -1){
        putchar('-');
    }
    while (num > 0){
        n = toNumber(num % 16);
        num /= 16;
        a[ch] = (char)n;
        ch++;
    }
    for(int i = 0; i < 8; i++){
        putchar(a[7-i]);
    }
    printf("\n");
}

int main() {
    int c, sign = 1;
    unsigned long long num = 0;
    state s = SEP;
    while ((c = getchar()) != EOF) {
        if (isNumber(c) && s != LITER){
            s = NUM;
            num += getNumber(c);
            num *= 16;
        } else if (isSep(c)){
            if (s == NUM){
                num /= 16;
                if(num >= 268435456 && num <= 4294967295){
                    to16(num, sign);
                }
            }
            sign = 1;
            num = 0;
            s = SEP;
        } else if (isSign(c) && s != NUM){
            s = SIGN;
            num = 0;
            sign = c == '+' ? 1 : -1;
        } else {
            num = 0;
            sign = 1;
            s = LITER;
        }
    }
    if (isNumber(c) && s != LITER){
        s = NUM;
        num += getNumber(c);
        num *= 16;
    } else if (isSep(c)){
        if (s == NUM){
            num /= 16;
            if(num >= 268435456 && num <= 4294967295){
                to16(num, sign);
            }
        }
        sign = 1;
        num = 0;
        s = SEP;
    }
    return 0;
}
