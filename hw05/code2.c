#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//unrolling 2
void compute() {
    const int MU = 2;
    const int NU = 2;
    int i,j,k, i1, j1, k1;
    for (i=0; i<NB; i+=MU)
    {
        for (j=0; j<NB; j+=NU)
        {
            for (k=0; k<NB; k+=2)
            {
//                for (i1=i; i1<i+MU;i1++)
//                {
//                    for (j1=j; j1<j+NU;j1++)
//                    {
//                        C[i1*NB+j1] += A[i1*NB+k] * B[k*NB+j1];
//                    }
//                }
                
                int c00 = i*NB+j;
                int c01 = c00+1;
                int c10 = (i+1)*NB+j;
                int c11 = c10+1;

                int a000 = i*NB+k;
                int a010 = a000;
                int a100 = (i+1)*NB+k;
                int a110 = a100;

                int a001 = i*NB+k+1;
                int a011 = a001;
                int a101 = (i+1)*NB+k+1;
                int a111 = a101;

                int b000 = k*NB+j;
                int b010 = b000+1;
                int b100 = b000;
                int b110 = b010;
                int b001 = (k+1)*NB+j;
                int b011 = b001+1;
                int b101 = b001;
                int b111 = b011;

                double C00 = C[c00];
                double C01 = C[c01];
                double C10 = C[c10];
                double C11 = C[c11];

                double A000 = A[a000];
                double A010 = A[a010];
                double A100 = A[a100];
                double A110 = A[a110];
                double A001 = A[a001];
                double A011 = A[a011];
                double A101 = A[a101];
                double A111 = A[a111];
                
                double B000 = B[b000];
                double B010 = B[b010];
                double B100 = B[b100];
                double B110 = B[b110];
                double B001 = B[b001];
                double B011 = B[b011];
                double B101 = B[b101];
                double B111 = B[b111];

                C00 += A000*B000; 
                C01 += A010*B010; 
                C10 += A100*B100; 
                C11 += A110*B110; 
                C00 += A001*B001; 
                C01 += A011*B011; 
                C10 += A101*B101; 
                C11 += A111*B111; 
                
                C[c00] = C00;
                C[c01] = C01;
                C[c10] = C10;
                C[c11] = C11;
            }
        }
    }
}

