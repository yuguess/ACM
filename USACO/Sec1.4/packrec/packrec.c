/*
ID: yuguess1
LANG: C
TASK: packrec
*/

#include <stdio.h>
#include <stdlib.h>
static int test[4] = {0, 1, 2, 3};
static minArea = 10000;
static minAreaWidth = 0;
static minAreaHeight = 0;
static stackSize = 20;
static stackTop = 0;

typedef struct {
    int width;
    int height;
} Rectangle;

static Rectangle stack[50];

inline int max(int a, int b) {
    return a > b ? a : b;
}

void swap(int *data, int a, int b) {
    int temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void rotateRectangle(Rectangle *rec, int index) {
    int temp = rec[index].width;
    rec[index].width = rec[index].height;
    rec[index].height = temp;
}

int isFull() {
    if (stackTop == stackSize) {
        return 1;
    } else {
        return 0;
    }
}

void pushStack(int width, int height) {
    //printf("push width %d, height %d\n", width, height);
    int i;
    int topElementValue = (stack[stackTop].width) * (stack[stackTop].height);
    int pushElementValue = width * height;
    if (topElementValue == 0)
        topElementValue = 10000;

    if (pushElementValue < topElementValue) {
        stackTop = 0;
        stack[stackTop].width = width;
        stack[stackTop].height = height;
    } 

    if (pushElementValue == topElementValue) {
        for (i = 0; i <= stackTop; i++) {
            if (stack[i].width == width && stack[i].height == height)
                return;
        }

        stackTop++; 
        if (!isFull()) {
            stack[stackTop].width = width;
            stack[stackTop].height = height;   
        } else {
            fprintf(stderr, "stack is full\n");
            exit(0);
        }
    } else {
        return ;
    }
}

void genSequence(int *seq, int begin, int end, Rectangle *rec) {
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int t = 0;
    /*
    for (t = 0; t < 4; t++) {
        printf("rec%d width:%d, height:%d\n", i, rec[t].width, rec[t].height);
    }
    getchar();
    */
    if (begin == end) {
       /* 
        for (i = 0; i < 4; i++)
            printf("%d", seq[i]);
        printf("\n");
        */
        
        for (j = 0; j < 2; j++) {
            if (j == 1) {
                rotateRectangle(rec, seq[3]);
            }
            for (k = 0; k < 2; k++) {
                if (k == 1) {
                    rotateRectangle(rec, seq[2]);
                }
                for (m = 0; m < 2; m++) {
                    if (m == 1) {
                        rotateRectangle(rec, seq[1]);
                    }
                    for (n = 0; n < 2; n++) {
                        if (n == 1) {
                            rotateRectangle(rec, seq[0]); 
                        }

                        /*
                        if (n ==1 & m ==1 & k ==1 & j ==1) {
                    for (i = 0; i < 4; i++) {
                    printf("i:%d seq %d width %d, height %d\n",i, seq[i], rec[seq[i]].width, rec[seq[i]].height);
                }

                            getchar();
                            printf("%d\n", minArea);
                        }*/

                        if (area1(rec, seq, &minAreaWidth, &minAreaHeight) <= minArea) {
                            minArea = area1(rec, seq, &minAreaWidth, 
                                    &minAreaHeight); 
                            if (minAreaWidth < minAreaHeight) {
                                pushStack(minAreaWidth, minAreaHeight);
                            } else {
                                pushStack(minAreaHeight, minAreaWidth);
                            }
                            
                            //printf("1 width:%d, height:%d, area:%d\n", 
                            //        minAreaWidth, minAreaHeight, minArea); 
                        }

                        if (area2(rec, seq, &minAreaWidth, &minAreaHeight) <= minArea) {
                            minArea = area2(rec, seq, &minAreaWidth, 
                                    &minAreaHeight); 
                            if (minAreaWidth < minAreaHeight) {
                                pushStack(minAreaWidth, minAreaHeight);
                            } else {
                                pushStack(minAreaHeight, minAreaWidth);
                            }
        //                    printf("2 width:%d, height:%d, area:%d\n", 
        //                            minAreaWidth, minAreaHeight, minArea); 
                        }
                        if (area3(rec, seq, &minAreaWidth, &minAreaHeight) <= minArea) {
                            minArea = area3(rec, seq, &minAreaWidth, 
                                    &minAreaHeight); 
                            if (minAreaWidth < minAreaHeight) {
                                pushStack(minAreaWidth, minAreaHeight);
                            } else {
                                pushStack(minAreaHeight, minAreaWidth);
                            }
      //                      printf("3 width:%d, height:%d, area:%d\n", 
      //                              minAreaWidth, minAreaHeight, minArea); 
                        }
                        if (area4(rec, seq, &minAreaWidth, &minAreaHeight) <= minArea) {
                            minArea = area4(rec, seq, &minAreaWidth, 
                                    &minAreaHeight); 
                            if (minAreaWidth < minAreaHeight) {
                                pushStack(minAreaWidth, minAreaHeight);
                            } else {
                                pushStack(minAreaHeight, minAreaWidth);
                            }
         //                   printf("4 width:%d, height:%d, area:%d\n", 
         //                           minAreaWidth, minAreaHeight, minArea); 
                        }
                        if (area6(rec, seq, &minAreaWidth, &minAreaHeight) <= minArea) {
                            minArea = area6(rec, seq, &minAreaWidth, 
                                    &minAreaHeight); 
                            if (minAreaWidth < minAreaHeight) {
                                pushStack(minAreaWidth, minAreaHeight);
                            } else {
                                pushStack(minAreaHeight, minAreaWidth);
                            }
                        //    printf("6 width:%d, height:%d, area:%d\n", 
                        //            minAreaWidth, minAreaHeight, minArea); 
                        }
/*
                        printf("area1: %d\n", area1(rec, seq));
                        printf("area2: %d\n", area2(rec, seq));
                        printf("area3: %d\n", area3(rec, seq));
                        printf("area4: %d\n", area4(rec, seq));
                        printf("area6: %d\n", area6(rec, seq));
                        */
                        if ( n == 1) {
                            rotateRectangle(rec, seq[0]);
                        }
                    }
                    if (m == 1) {
                        rotateRectangle(rec, seq[1]);
                    }
                }
                if (k == 1) {
                    rotateRectangle(rec, seq[2]);
                }
            }
            if (j == 1) {
                rotateRectangle(rec, seq[3]);
            }
        }

        return;
    }

    for (i = begin; i <= end; i++) {
        //printf("%d", data[i]);
        swap(seq, begin, i);
        genSequence(seq, begin + 1, end, rec); 
        swap(seq, i, begin);
    }
    //genSequence
}



int area1(Rectangle *rec, int *seq, int* minAreaWidth, int* minAreaHeight) {
    int i = 0;
    int maxHeight = 0;
    int sumWidth = 0;
    //printf("seq: %d\n", seq[i]);
    //printf("width:%d\n", rec[seq[i]].width);
    for (i = 0; i < 4; i++) {
        sumWidth += rec[seq[i]].width;
        if (rec[seq[i]].height > maxHeight)
            maxHeight = rec[seq[i]].height;
    }
    /*
    if (sumWidth == 200) {
        printf(" here width: %d\n", sumWidth);
        printf("height:%d\n", maxHeight);
        getchar();
    }*/
    *minAreaWidth = sumWidth; 
    *minAreaHeight = maxHeight;
    return  (*minAreaWidth) * (*minAreaHeight);
}

int area2(Rectangle *rec, int * seq, int* minAreaWidth, int* minAreaHeight) {
    int i;
    int sum3Width = 0;
    int max3Height = 0;
    for (i = 0; i < 3; i++) {
        sum3Width += rec[seq[i]].width;
        if (rec[seq[i]].height > max3Height)
            max3Height = rec[seq[i]].height;
    }
    *minAreaWidth = max(sum3Width, rec[seq[3]].width);
    *minAreaHeight = rec[seq[3]].height + max3Height; 
    return  (*minAreaWidth) * (*minAreaHeight);
}

int area3(Rectangle *rec, int * seq, int* minAreaWidth, int* minAreaHeight) {
    int i;
    int sum2Width = 0;
    int max2Height = 0;
    for (i = 0; i < 2; i++) {
        sum2Width += rec[seq[i]].width;
        if (rec[seq[i]].height > max2Height)
            max2Height = rec[seq[i]].height;
    }
    *minAreaWidth = max(rec[seq[3]].width, sum2Width) 
        + rec[seq[2]].width; 
    *minAreaHeight = max(max2Height + rec[seq[3]].height, 
            rec[seq[2]].height);

    return (*minAreaWidth) * (*minAreaHeight);
}

int area4(Rectangle *rec, int * seq, int* minAreaWidth, int* minAreaHeight) {
    int i;
    int sum2Height = 0;
    int max2Width = 0;

    for (i = 0; i < 2; i++) {
        sum2Height += rec[seq[i]].height;
        //printf("width %d seq %d\n", rec[seq[i]].width, i);
        if (rec[seq[i]].width > max2Width)
            max2Width = rec[seq[i]].width;
    }
    /*
    for (i = 0; i < 4; i++) {
        printf("seq %d\n", seq[i]);
        printf("%d width %d, height %d\n", seq[i], rec[seq[i]].width, rec[seq[i]].height);
    }*/
    
    //printf("maxWidth:%d, rec2 width %d, rec width %d\n", max2Width, rec[2].width, rec[3].width);
    *minAreaWidth = max2Width + rec[seq[2]].width + rec[seq[3]].width;
    
    *minAreaHeight = max(max(rec[seq[2]].height, rec[seq[3]].height), 
            sum2Height); 

    return (*minAreaWidth) * (*minAreaHeight);
}
/*
int area5(Rectangle *, int * seq) {

}*/

int area6(Rectangle *rec, int * seq, int* minAreaWidth, int* minAreaHeight) {
    int i;

    if (rec[seq[0]].height < rec[seq[1]].height) {
        if (rec[seq[2]].width <= rec[seq[0]].width) {
            if (rec[seq[2]].height + rec[seq[0]].height > rec[seq[1]].height) {
                if (rec[seq[2]].width + rec[seq[3]].width <= rec[seq[0]].width + rec[seq[1]].width) {
                    *minAreaWidth = rec[seq[0]].width + rec[seq[1]].width;
                    *minAreaHeight = max(rec[seq[0]].height + rec[seq[2]].height,
                                    rec[seq[1]].height + rec[seq[3]].height);           
                } else {
                    return 10000;        
                } 
            } else {
                *minAreaHeight = rec[seq[1]].height + rec[seq[3]].height; 
                *minAreaWidth = max(rec[seq[0]].width + rec[seq[1]].width, rec[seq[3]].width); 
                /*
                for (i = 0; i < 4; i++) {
                    printf("i:%d seq %d width %d, height %d\n",i, seq[i], rec[seq[i]].width, rec[seq[i]].height);
                }
                printf("width %d, height %d\n", (*minAreaWidth) , (*minAreaHeight));
                */
            }
            
        } else {
            return 10000; 
        }
    } else {
        if (rec[seq[0]].height == rec[seq[1]].height) {
            if (rec[seq[2]].width + rec[seq[3]].width <= rec[seq[0]].width + rec[seq[1]].width) {
                *minAreaWidth = rec[seq[0]].width + rec[seq[1]].width;
                *minAreaHeight = max(rec[seq[0]].height + rec[seq[2]].height,
                                rec[seq[1]].height + rec[seq[3]].height);
            } else {
                return 10000;
            }
        } else {
            return 10000;
        }
    }
/*
    for (i = 0; i < 4; i++) {
        printf("seq %d width %d, height %d\n", seq[i], rec[seq[i]].width, rec[seq[i]].height);
    }
    printf("width %d, height %d\n", (*minAreaWidth) , (*minAreaHeight));
    */
    
    /*
    *minAreaWidth = max(rec[seq[0]].width + rec[seq[1]].width, 
            rec[seq[2]].width + rec[seq[3]].width);
    *minAreaHeight = max(rec[seq[0]].height + rec[seq[2]].height,
            rec[seq[1]].height + rec[seq[3]].height);

    return (*minAreaWidth) * (*minAreaHeight);
    */
    /*
    *minAreaWidth = max(rec[seq[0]].width + rec[seq[1]].width, rec[seq[3]].width); 
    *minAreaHeight = max(rec[seq[0]].height + rec[seq[2]].height,
            rec[seq[1]].height + rec[seq[3]].height);

    int x3 =  rec[seq[0]].width + rec[seq[1]].width - rec[seq[3]].width; 
    int y3 = rec[seq[1]].height;
    int x2 = rec[seq[2]].width;
    int y2 = rec[seq[0]].height + rec[seq[2]].height;

    if (x2 > x3 && y2 > y3)
        return 2500;
    if (x2 > rec[seq[0]].width)
        return 2500;
    if (rec[seq[2]].width > rec[seq[0]].width)
        return 2500;

    
    for (i = 0; i < 4; i++) {
        printf("seq %d width %d, height %d\n", seq[i], rec[seq[i]].width, rec[seq[i]].height);
    }
    printf("width %d, height %d\n", (*minAreaWidth) , (*minAreaHeight));
    */
    
    return (*minAreaWidth) * (*minAreaHeight);
}

int compare(const void* a, const void* b) {
    return (((Rectangle *)a)->width  - ((Rectangle *)b)->width);
}

int main () {
    int i;
    ectangle rec[4];

    FILE *fin = fopen("packrec.in", "r");
    FILE *fout = fopen("packrec.out", "w");
    for (i = 0; i < 4; i++) {
       fscanf(fin, "%d %d", &(rec[i].width), &(rec[i].height)); 
    }
/*
    rec[0].width = 1;
    rec[0].height = 2;
    rec[1].width = 2;
    rec[1].height = 3;
    rec[2].width = 3;
    rec[2].height = 4;
    rec[3].width = 4;
    rec[3].height = 5;
    */
    
   /* 
    for (i = 0; i < 4; i++) {
        printf("rec%d width:%d, height:%d\n", i, rec[i].width, rec[i].height);
    }*/
    genSequence(test, 0, 3, rec);
    qsort(stack, stackTop + 1, sizeof(Rectangle), compare);
/*
    printf("%d\n", stack[0].width * stack[0].height);
    for (i = 0; i <= stackTop; i++) 
        printf("%d %d\n", stack[i].width, stack[i].height);
        */
    fprintf(fout, "%d\n", stack[0].width * stack[0].height);
    for (i = 0; i <= stackTop; i++) 
        fprintf(fout, "%d %d\n", stack[i].width, stack[i].height);
    exit(0);
}
