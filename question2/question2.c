#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TIMES 1000
float A[64][64] = {0};//A
float B[64][64] = {0};//B
float x[64];//v1 after normalizationここでは、更新可能、更新ならv2の正規化後の表示になる
float nx[64] = {0};//v1 before normalization、更新可能、更新ならv２の正規化前の表示になる
float k1[64]= {0};//v1*A、更新可能、更新なら、v２について処理
float kx = 0;//k1、更新可能、更新なら、k2
void Vgenerate(float A[64][64]);//make v1,v2...
void Kgenerate(float A[64][64]);//make k1,k2...
void Bgenerate(float B[64][64]);//make B,C...
int counter = 0;//counter the size of matrix
int main(int agrc, char* agrv[]){
  FILE *fp;
  fp = fopen(agrv[1],"r");
  if(fp == NULL){
    printf("read files with error!\n");
  }
  while(1){
    char c;
    c = getc(fp);
    if(c == EOF) break;
    if(c == '\n')counter++;
  }
  printf("counter is %d\n",counter);
  fseek(fp,0L,SEEK_SET);
  //printf("input A as :\n");
  for(int i = 0; i < counter; i++)
    for(int j = 0; j < counter; j++)
      fscanf(fp,"%f",&A[i][j]);
  //for(int i = 0; i < counter; i++){
    //for(int j = 0; j < counter; j++)
      //printf("%.4f\t",A[i][j]);
    //printf("\n");
  // }
  Vgenerate(A);
  Kgenerate(A);
  //printf("now create B as:\n");
  Bgenerate(B);
  Vgenerate(B);
  Kgenerate(B);
  return 0;
}
void Vgenerate(float A[64][64]){
  float sum;
  float sq_sum;
  for(int i = 0; i < counter;i++)
    x[i] = 1;
  for(int n = 0; n < TIMES; n++){
    sq_sum = 0;
    for(int i = 0; i < counter; i++){
	sum = 0;
	for(int k = 0; k < counter; k++){
	  sum += A[i][k] * x[k];
	}
	nx[i] = sum;
	sq_sum+= nx[i]*nx[i];
    }
    for(int i = 0; i < counter; i++){
      x[i] = nx[i]/sqrt(sq_sum);
    }
}
  printf("v as:\n");
  for(int i = 0; i < counter; i++)
  printf("%f\t",x[i]);
  printf("\n");
}

void Kgenerate(float A[64][64]){
  float sum;
  for(int i = 0; i < counter; i++){
       sum = 0;
       for(int k = 0; k < counter; k++)
	 sum += x[k]* A[k][i];
       k1[i] = sum;
}
  sum = 0;
   for(int i = 0; i < counter; i++){
      sum += k1[i] * x[i];
    }
      kx = sum;
      printf("k as %f\n",kx);
}
void Bgenerate(float B[64][64]){
    for(int i = 0; i < counter; i++){
        for(int j = 0; j < counter; j++){
            B[i][j] = A[i][j]-kx*x[i]*x[j];
            //printf("%.4f\t",B[i][j]);}
            //printf("\n");
            
        }
    }
}
