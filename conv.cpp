#include<iostream>
#include<omp.h>
#include<stdlib.h>
#define A_val 4.0
#define B_val 3.0
void InitVal(float *A,int val,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            A[i*n+j]=val;
        }
    }
}
int M,N,P,Q;
inline void conv(float*A,float*B,float*C){
    //simply loop over the image and applying filter using pointwise multiplication
    int M_modified=M-P+1;
    int N_modified=N-Q+1;
    for(int m=0;m<M_modified;m++){
        for(int n=0;n<N_modified;n++){
            int ans=0;
            for(int p=0;p<P;p++){
                for(int q=0;q<Q;q++){
                    ans+=A[(m+p)*N+n+q]*B[p*Q+q];
                }
            }
            C[m*(N_modified)+n]=ans;
        }
    }
    
}
inline void printMat(float*A,int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            std::cout<<A[i*n+j]<<" ";
        }
        std::cout<<"\n";
    }
}
int main(int argc,char* argv[]){
    M=8,N=8,P=3,Q=3;
    if(argc==5){
        M=std::stoi(argv[1]);
        N=std::stoi(argv[2]);
        P=std::stoi(argv[3]);
        Q=std::stoi(argv[4]);
    }
    float* A=(float *)malloc(sizeof(float)*M*N);
    float* B=(float *)malloc(sizeof(float)*P*Q);
    float* C=(float *)malloc(sizeof(float)*(N-Q+1)*(M-P+1));
    InitVal(A,A_val,M,N);
    InitVal(B,B_val,P,Q);
    InitVal(C,0.0,N-Q+1,M-P+1);
    conv(A,B,C);
    printMat(C,N-Q+1,M-P+1);


    
}