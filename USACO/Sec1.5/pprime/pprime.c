/*
ID: yuguess1
LANG: C
TASK: pprime 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static char* lastDigitNum[4] = {"1", "3", "7", "9"};

int isPrime(int n) {
    int i;
    int limit = sqrt(n) + 1;
    int count = 0;
    for (i = 3 ; i < limit; i+=2) {
        if (n % i == 0) {
            return 0; 
        }
    }
    return 1; 
}

int digitSize(int num) {
    char buffer[12];
    sprintf(buffer, "%d", num);
    return strlen(buffer); 
}

void reverseStr(char * revBuf, char *buf, int oddFlag) {
    int bufLen = strlen(buf); 
    int i;
    for (i = 1; i <= bufLen; i++) {
        revBuf[i - 1] = buf[bufLen - i];
    }

    if (oddFlag == 0) {
        revBuf[bufLen] = '\0';
    } else {
        revBuf[bufLen - 1] = '\0';
    }
}

void addZeros(int digit, int num, char *buffer) {
    int numDigit;
    int i;
    char tmp[12];
    numDigit = digitSize(num);
    int zeroCount = digit - numDigit;
    sprintf(tmp, "%d", num);
    for (i = 0; i < zeroCount; i++) 
        buffer[i] = '0';
    for (i = 0; i < numDigit; i++)
        buffer[i + zeroCount] = tmp[i]; 
    buffer[i + zeroCount] = '\0';
}

int * genPPNumByDigit(int digit, int *size) {
    int *retPtr = NULL;
    int tmp;
    int i;
    int limit;
    int oddFlag = 0;
    int j;
    int addZeroLimit = 0;
    char buffer[12];
    char reverseBuf[12];

    if (digit == 1) {
        retPtr = (int *)malloc(sizeof(int) * 2);        
        retPtr[0] = 5;
        retPtr[1] = 7;
        *size = 2;
        return retPtr;
    }
    if (digit == 2) {
        retPtr = (int *)malloc(sizeof(int) * 1);
        retPtr[0] = 11;
        *size = 1;
        return retPtr;
    }

    if (digit % 2 == 0) {
        tmp = digit / 2 - 1;
    } else {
        tmp = (digit + 1) / 2 - 1;
        oddFlag = 1;
    }

    limit = pow(10, tmp);
    addZeroLimit = pow(10, tmp - 1);
    *size = limit * 4; 
    /*
    printf("limit %d\n", limit);
    getchar();
    */
    retPtr = (int *)malloc(sizeof(int) * limit * 4);

    for (j = 0; j < 4; j++) {
        for (i = 0; i < limit; i++) {
            if (i / addZeroLimit == 0)
                addZeros(tmp, i, buffer);
            else 
                sprintf(buffer, "%d", i);   
            
            strcat(buffer, lastDigitNum[j]);
/*
            printf("%s\n", buffer);
            getchar();
*/
            reverseStr(reverseBuf, buffer, oddFlag);
/*
            printf("%s\n", reverseBuf);
            
            getchar();
 */           
            strcat(reverseBuf, buffer);
            if (strlen(reverseBuf) != digit)
                continue;
            retPtr[j * limit + i] = atoi(reverseBuf);
            //printf("%d:%d\n", j * limit + i, retPtr[j * limit + i]);
            /*
            
            getchar();
            */
            memset(reverseBuf, '\0', sizeof(char) * 12);
            memset(buffer, '\0', sizeof(char) * 12);
           // printf("here");
           // getchar();
        }
        
    }
    return retPtr;
    
}

int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int* genPPNum(int lowerBound, int upperBound, FILE *fout) {
    int i;
    int size;
    int *ppNum;
    int j;

    int lowDigitSize = digitSize(lowerBound);
    int upperDigitSize = digitSize(upperBound);

    int *result = (int *)malloc(sizeof(int) * 100000);
    int top = 0;

    for (i = lowDigitSize; i <= upperDigitSize; i++) {
        ppNum = genPPNumByDigit(i, &size); 
        
        //printf("size %d\n", size);
        //getchar();
        if (ppNum != NULL) {
            for (j = 0; j < size; j++) {
                
                if (ppNum[j] <= upperBound && ppNum[j] >= lowerBound) {
                    if (isPrime(ppNum[j])) { 
                        result[top] = ppNum[j];
                        top++;
                    }
                        
                }
            }
            free(ppNum);
        }
    }
    qsort(result, top, sizeof(int), compare); 
    for (i = 0; i < top; i++)
        fprintf(fout, "%d\n", result[i]);
    
    free(result);
}

int main () {
    
    FILE *fin = fopen("pprime.in", "r");
    FILE *fout = fopen("pprime.out", "w");

    int lowerBound;
    int upperBound;
    int *ppNum;
    int size;
    int i;

    fscanf(fin, "%d", &lowerBound);
    fscanf(fin, "%d", &upperBound);

    genPPNum(lowerBound, upperBound, fout);
    
    fclose(fin);
    fclose(fout);
    
}
