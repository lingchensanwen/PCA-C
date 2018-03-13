#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TIMES 2000
#define N 4
#define counter 4

int n = 0;//the size of data,n*N
float X[200][N];//save in x
float C[N][N];//C for v1,k1
float C2[N][N];//C2 for v2,k2
float C3[N][N];//C3 for v3,k3
float C4[N][N];//C4 for v4,k4
float x[N];//v1
float sh[N] = {0};//save as shallow
float nx[N] = {0};//v1 before normalnaize
float k1[N]= {0};//v1*A
float kx = 0;//k1
void Vgenerate(float A[N][N]);//make v1,v2...
void Kgenerate(float A[N][N]);//make k1,k2...
void Bgenerate(float B[N][N],float C[N][N]);//generate B
void Cgenerate(float X[200][N]);//generate C
void Shadow(float v[N]);//generate the Shadow save in sh
void CreateV_K_new_C_Sh(float C_new[N][N],float C_old[N][N]);//for convinent create C,k,v,S together
float average(float X[N]);//computer the average for normalnaize
int main(int agrc, char* agrv[]){
  FILE *fp;
  fp = fopen(agrv[1],"r");
  if(fp == NULL){
    printf("read files with error!\n");
  }
  char c;
  char s[100];
  while(1){
    c = getc(fp);
    if(c == EOF) break;
    if(c == '\n') n++;
  }
  printf("n is %d\n",n);
  fseek(fp,0L,SEEK_SET);
  printf("X is now as:\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < N; j++){
	fscanf(fp,"%f,%[,]",&X[i][j],&c);
      printf("%f\t",X[i][j]);}
    fscanf(fp,"%s\n",s);
    printf("\n");
  }
  Cgenerate(X);
  printf("C is :\n");
  for(int i = 0; i < counter; i++){
    for(int j = 0; j < counter; j++)
      printf("%f\t",C[i][j]);
    printf("\n");}
  Vgenerate(C);
  Kgenerate(C);
  printf("now create new C as:\n");
  CreateV_K_new_C_Sh(C2,C);
  CreateV_K_new_C_Sh(C3,C2);
  CreateV_K_new_C_Sh(C4,C3);
}
float average(float X[N]){
  float sum = 0;
  for(int i = 0; i < N; i++)
    sum = sum + X[i];
  return sum/N;
}
void Cgenerate(float X[200][N]){
  float sum;
  for(int i = 0 ; i < N ; i++)
    for(int j = 0; j < N; j++){
      sum = 0;
      for(int l = 0; l < N; l++){
          sum = sum + (X[i][l]-average(X[i]))*(X[j][l]-average(X[j]));
      }
      C[i][j] = sum/N-1;
    }
}
void Vgenerate(float A[N][N]){
  float sum;
  float sq_sum;
  for(int i = 0; i < N;i++)
    x[i] = 1;
  for(int j = 0; j < TIMES; j++){
    sq_sum = 0;
    for(int i = 0; i < N; i++){
	sum = 0;
	for(int k = 0; k < N; k++){
	  sum += A[i][k] * x[k];
	}
	nx[i] = sum;
	sq_sum+= nx[i]*nx[i];
    }
    for(int i = 0; i < N; i++){
      x[i] = nx[i]/sqrt(sq_sum);
    }
}
  printf("v as:\n");
  for(int i = 0; i < N; i++)
  printf("%f\t",x[i]);
  printf("\n");
}

void Kgenerate(float A[N][N]){
  float sum;
  for(int i = 0; i < N; i++){
       sum = 0;
       for(int k = 0; k < N; k++)
	 sum += x[k]* A[k][i];
       k1[i] = sum;
}
  sum = 0;
   for(int i = 0; i < N; i++){
      sum += k1[i] * x[i];
    }
      kx = sum;
      printf("k as %f\n",kx);
}
void Bgenerate(float B[N][N],float C[N][N]){
    printf("creat new C as:\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            B[i][j] = C[i][j]-kx*x[i]*x[j];
            printf("%.4f\t",B[i][j]);}
        printf("\n");
    }
}
void Shadow(float sh[200]){
    for(int i = 0; i < n; i++)
        sh[i] = 0;
    for(int i = 0; i < n; i++){
        float sum = 0;
        for(int j = 0; j < N; j++){
            sum = sum + X[i][j] * x[j];
        }
        sh[i] = sum;
    }
    printf("Shadow is: \n");
    for(int i = 0; i < n; i++)
        printf("%.4f\t",sh[i]);
    printf("\n");
}
void CreateV_K_new_C_Sh(float C_new[N][N],float C_old[N][N]){
    Bgenerate(C_new,C_old);
    Vgenerate(C_new);
    Kgenerate(C_new);
    Shadow(sh);
}




