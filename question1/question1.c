#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TIMES 1000
float A[64][64] = {0};//save the data in A
float x[64];//v1 after normalization
float nx[64] = {0};//v1 before normalization
float k1[64]= {0};//(v1.T * A)
float kx = 0;//the result of k1
void Vgenerate();//the function to generate v1
void Kgenerate();//the function to generate k
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
  for(int i = 0; i < counter; i++)
    for(int j = 0; j < counter; j++)
      fscanf(fp,"%f",&A[i][j]);
  /*for(int i = 0; i < counter; i++){
    for(int j = 0; j < counter; j++)
      printf("%.4f\t",A[i][j]);
    printf("\n");
   }*/
  Vgenerate();
  printf("\n");
  Kgenerate();
  return 0;
}
void Vgenerate(){
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
  printf("v1 is :\n");
  for(int i = 0; i < counter; i++)
  printf("%f\t",x[i]);  
}

void Kgenerate(){
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
    printf("k1 is :%f\n",kx);
}
