//In pervious method we were accessing C[i][j] in every iteration of k to it will be saved in cache and then will hit every time in cache
//But we can optimize it storing it in a varaible which is used again n again so it will saved in a register and will only take a single cycle for the value
//We are multiplying two matrices of 4096*4096
#include<iostream>
#include<omp.h>
#define A_val 4.0
#define B_val 3.0
const int s=128;
template<int M,int K,int N>
void matMul(float *A,float*B,float*C){
    #pragma omp parallel for
    for(int mm=0;mm<M;mm+=s){
    #pragma omp parallel for
        for(int nn=0;nn<N;nn+=s){
            for(int kk=0;kk<K;kk+=s){
                for(int m=0;m<s;m++){
                        for(int k=0;k<s;k++){
                    for(int n=0;n<s;n++){
                            C[(mm+m)*K+nn+n]+=A[(mm+m)*K+kk+k]*B[(kk+k)*N+n];
                        }
                    }
                }
            }
        }
    }

    // for(int m=0;m<M;m++){
    //     for(int n=0;n<N;n++){
    //         int x=0;
    //         for(int k=0;k<K;k++){
            
    //           x+=A[m*K+k]*B[k*N+n];
    //         }
    //         C[m*K+n]=x;
             
    //     }
    // }
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
    double t1,t2;
    float *A=(float *)malloc(sizeof(float)*4096*4096);
    float *B=(float *)malloc(sizeof(float)*4096*4096);
    float *C=(float *)malloc(sizeof(float)*4096*4096);
    InitVal(A,A_val,4096,4096);
    InitVal(B,B_val,4096,4096);
    InitVal(C,0.0,4096,4096);
    // for(int i=8;i<256;i=i*2){
    t1=omp_get_wtime();
    matMul<4096,4096,4096>(A,B,C);
    t2=omp_get_wtime();
    // std::cout<<"Time taken to execute for tilling "<<i<<" : "<<(t2-t1)<<"s \n";
    std::cout<<"Time taken to execute for tilling : "<<(t2-t1)<<"s \n";
    // std::cout<<i<<" ";
    // }
    // printMat(C,128,128);
    return 0;
}