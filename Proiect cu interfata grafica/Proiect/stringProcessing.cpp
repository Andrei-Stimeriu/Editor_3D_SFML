#include "stringProcessing.h"

void append(char* theString, char ch){
    int maxLength = menu.maxTextLength;

    char* p = theString;
    while(*p){ p++; }

    if(p - theString >= maxLength){ return; }
    if(ch >= '0' && ch <= '9'){
        *p = ch; p++;
        *p = 0; return;
    }
    if(ch == '.'){
        bool isDot = false, isDigit = false;
        for(char* q = theString; *q; q++){
            if(*q == '.'){
                isDot = true; break;
            }
            if(*q >= '0' && *q <= '9'){ isDigit = true; }
        }
        if(isDot){ return; }
        if(!isDigit){ return; }
        *p = ch; p++;
        *p = 0; return;
    }
    if(ch == '-'){
        if(p != theString){ return; }
        *p = ch; p++;
        *p = 0;
    }
}

void backOne(char* theString){
    char* p = theString;
    while(*p){ p++; }

    if(p == theString){ return; }
    p--; *p = 0;
}

float stringToFloat(char* theString){
    float result = 0.0f;
    char* p = theString;

    if(*p == 0){ return result; }

    int theSign = 1;
    if(*p == '-'){ theSign = -1; p++; }

    while(*p >= '0' && *p <= '9'){
        result *= 10; result += *p - '0';
        p++;
    }

    if(*p != '.'){ return result * theSign; }

    float coef = 1.0f;

    p++;
    while(*p >= '0' && *p <= '9'){
        coef /= 10; result += coef * (*p - '0');
        p++;
    }

    return result * theSign;
}

void floatToString(char* theString, float number){
    char* p = theString;
    if(number < 0){
        *p = '-'; p++;
        number = -number;
    }

    int point = 1;
    while(number >= 1){
        number /= 10; point++;
    }

    while(p - theString < menu.maxTextLength){
        number *= 10; point--;
        int digit = ((int)number) % 10;
        if(point != 0){
            *p = digit + '0'; p++;
        }
        else{
            if(p - theString < menu.maxTextLength - 1){
                if(p == theString){
                    *p = '0'; p++;
                }
                *p = '.'; p++;
                *p = digit + '0'; p++;
            }
        }
    }
    *p = 0;
}
