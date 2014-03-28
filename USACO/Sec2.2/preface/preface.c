/*
ID: yuguess1
LANG: C
TASK: preface 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int histogram[7];

char num2roman(int num) {
    switch (num) {
        case 1: return 'I';
        case 5: return 'V';
        case 10: return 'X';
        case 50: return 'L';
        case 100: return 'C';
        case 500: return 'D';
        case 1000: return 'M';
        default : fprintf(stderr, "error\n");
    }
}

void roman_string_form(char *str, int num, int measure_num) {
    int i;
    if (num <= 3) {
        for (i = 0; i < num; i++)    
            str[i] = num2roman(measure_num); 
        str[i] = '\0';
        return;
    }

    if (num == 4) {
        str[0] = num2roman(measure_num);
        str[1] = num2roman(measure_num * 5);
        str[2] = '\0';
        return;
    }

    if (num == 5) {
        str[0] = num2roman(measure_num * 5);
        str[1] = '\0';
        return;
    }

    if (num > 5 && num < 9) {
        str[0] = num2roman(measure_num * 5);
        for (i = 0; i < num - 5; i++)
            str[i + 1] = num2roman(measure_num);
        str[i + 1] = '\0';
        return;
    }

    if (num == 9) {
        str[0] = num2roman(measure_num);
        str[1] = num2roman(measure_num * 10);
        str[2] = '\0';
        return;
    }
}



int roman2num(char c) {
   switch (c) {
        case 'I': return 0;
        case 'V': return 1;
        case 'X': return 2;
        case 'L': return 3;
        case 'C': return 4;
        case 'D': return 5;
        case 'M': return 6;
        default : fprintf(stderr, "error\n");
    } 
}

void character_histogram(char * str) {
    int length = strlen(str);
    int i;
    int temp = 0;
    for (i = 0; i < length; i++) {
        temp = roman2num(str[i]);
        histogram[temp]++;
    }
}

void roman_numeral(int num) {
    int measure_num = 0;
    int temp, i;
    char string[15];
    char roman_string[15];
    memset(roman_string, 0, sizeof(char) * 15);
    for (i = 3; i >= 0; i--) {
        measure_num = pow(10, i); 
        temp = num / measure_num;
        if (temp != 0) {
            roman_string_form(string, temp, measure_num);
            strcat(roman_string, string); 
            memset(string, 0, sizeof(char) * 15);
            num -= temp * measure_num;    
        }
        
    }
    character_histogram(roman_string);
}

int main () {
    int  N, i;
    char roman_character[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    FILE *fin = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");

    fscanf(fin, "%d", &N);
    
    for (i = 0; i < 7; i++)
        histogram[i] = 0;

    for (i = 1; i <= N; i++)
        roman_numeral(i); 

    for (i = 0; i < 7; i++) {
        if (histogram[i] != 0)
            fprintf(fout, "%c %d\n", roman_character[i], histogram[i]);
        else { 
            fclose(fin);
            fclose(fout);
            return 0;
        }
    }
    fclose(fin);
    fclose(fout);
}
