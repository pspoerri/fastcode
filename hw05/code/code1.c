#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//register blocking
void compute() {
    const int MU = 2;
    const int NU = 2;
    int i,j,k, i1, j1, k1;
    for (i=0; i<NB; i+=MU)
    {
        for (j=0; j<NB; j+=NU)
        {
            for (k=0; k<NB; k++)
            {
//                for (i1=i; i1<i+MU;i1++)
//                {
//                    for (j1=j; j1<j+NU;j1++)
//                    {
//                        C[i1*NB+j1] += A[i1*NB+k] * B[k*NB+j1];
//                    }
//                }
                double C00, C01, C10, C11;
                double A00, A01, A10, A11;
                double B00, B01, B10, B11;
                
                int c00 = i*NB+j;
                int c01 = c00+1;
                int c10 = (i+1)*NB+j;
                int c11 = c10+1;

                int a00 = i*NB+k;
                int a01 = a00;
                int a10 = (i+1)*NB+k;
                int a11 = a10;

                int b00 = k*NB+j;
                int b01 = b00+1;
                int b10 = b00;
                int b11 = b01;

                C00 = C[c00];
                C01 = C[c01];
                C10 = C[c10];
                C11 = C[c11];

                A00 = A[a00];
                A01 = A[a01];
                A10 = A[a10];
                A11 = A[a11];
                
                B00 = B[b00];
                B01 = B[b01];
                B10 = B[b10];
                B11 = B[b11];

                C00 += A00*B00; 
                C01 += A01*B01; 
                C10 += A10*B10; 
                C11 += A11*B11; 

                C[c00] = C00;
                C[c01] = C01;
                C[c10] = C10;
                C[c11] = C11;
            }
        }
    }
}

