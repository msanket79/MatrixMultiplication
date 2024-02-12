// In this we have implemented the matrix multiplication using three nested loops
//We are multiplying two matrices of 4096*4096
#include<iostream>
#include<omp.h>
#define A_val 4.0
#define B_val 3.0
template<int M,int K,int N>
void matMul(float *A,float*B,float*C){
    for(int m=0;m<M;m++){
        for(int n=0;n<N;n++){
            for(int k=0;k<K;k++){
                C[m*K+n]+=A[m*K+k]*B[k*N+n];
            }
        }
    }
}
void InitVal(float *A,int val,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            A[i*n+j]=val;
        }
    }
}
void printMat(float *A,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            std::cout<<A[i*n+j]<<" ";

        }
        std::cout<<"\n";
    }
}
int main(){
    float *A=(float *)malloc(sizeof(float)*4096*4096);
    float *B=(float *)malloc(sizeof(float)*4096*4096);
    float *C=(float *)malloc(sizeof(float)*4096*4096);
    InitVal(A,A_val,4096,4096);
    InitVal(B,B_val,4096,4096);
    InitVal(C,0.0,4096,4096);
    double t1=omp_get_wtime();
    matMul<4096,4096,4096>(A,B,C);
    double t2=omp_get_wtime();
        printf("Time taken to execute: %f s or %f minutes | FlOPS : %f MFlops\n",(t2-t1),(t2-t1)/60,(2.0*4096*4096*4096)/(t2-t1)/1000000);

    // printMat(C,100,100);
    return 0;
}