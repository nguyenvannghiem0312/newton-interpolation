#include <stdio.h>
#include <math.h>
#include <malloc.h>
int main(){
    FILE *f;
    f = fopen("baitap22.txt", "r");
    int row, col;
    fscanf(f, "%d %d", &row, &col);
    double *matran = (double*) malloc(sizeof(double)*row*col);
    for(int i = 0; i < row*col; i++){
        fscanf(f, "%lf", matran + i);
    }
    printf("Ma tran la: \n");
    for(int i = 0; i < row*col; i++){
        printf("%-4.1lf ", *(matran + i));
        if((i + 1)% col == 0 && i != 0) printf("\n");
    }
}