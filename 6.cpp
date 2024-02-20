#include<iostream>
#include<omp.h>
#define A_val 4.0
#define B_val 3.0
#define convert(A,r,c) (A+(r*cols+c)*N/2)
// const int s=128;
template<int cols,int threshold>
void matMul(float *A,float*B,float*C,int N){
    if(N==threshold){
        for(int i=0;i<N;i++){
            for(int k=0;k<N;k++){
                for(int j=0;j<N;j++){
                    C[i*cols+j]+=A[i*cols+k]*B[k*cols+j];
                }
            }
        }
    }
    else{
        #pragma omp task
        matMul<cols,threshold>(convert(A,0,0),convert(B,0,0),convert(C,0,0),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,0,0),convert(B,1,0),convert(C,0,1),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,1,0),convert(B,0,0),convert(C,1,0),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,1,0),convert(B,0,1),convert(C,1,1),N/2);
        #pragma omp taskwait

        #pragma omp task
        matMul<cols,threshold>(convert(A,0,1),convert(B,1,0),convert(C,0,0),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,0,1),convert(B,1,1),convert(C,0,1),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,1,1),convert(B,1,0),convert(C,1,0),N/2);
        #pragma omp task
        matMul<cols,threshold>(convert(A,1,1),convert(B,1,1),convert(C,1,1),N/2);
        #pragma omp taskwait

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
    int flag=0;
    int ans=n*A_val*B_val;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            // std::cout<<A[i*n+j]<<" ";
            if(A[i*n+j]!=ans){
                flag=1;
                break;
            }
        }
    }
        if(flag==0) std::cout<<"Correct Answer\n";
        else
        std::cout<<"Wrong answer";
}
int main(){
    double t1,t2;
    float *A=(float *)malloc(sizeof(float)*4096*4096);
    float *B=(float *)malloc(sizeof(float)*4096*4096);
    float *C=(float *)malloc(sizeof(float)*4096*4096);
    InitVal(A,A_val,4096,4096);
    InitVal(B,B_val,4096,4096);
    InitVal(C,0.0,4096,4096);
    // for(int i=8;i<256;i=i*2){
    #pragma omp parallel
    #pragma omp single
    {
    t1=omp_get_wtime();
    matMul<4096,128>(A,B,C,4096);
    t2=omp_get_wtime();
    }
    // std::cout<<"Time taken to execute for tilling "<<i<<" : "<<(t2-t1)<<"s \n";
    std::cout<<"Time taken to execute for divide and conquer : "<<(t2-t1)<<"s \n";
    // std::cout<<i<<" ";
    // }
    printMat(C,4096,4096);
    return 0;
}