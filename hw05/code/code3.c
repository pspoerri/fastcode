#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//unrolling 4
void compute() {
    const int MU = 1;
    const int NU = 8;
    const int KU = 2;
    int i,j,k, i1, j1, k1;
    for (i=0; i<NB; i+=MU)
    {
        for (j=0; j<NB; j+=NU)
        {
            for (k=0; k<NB; k+=KU)
            {
//                for (k1=k; k1<k+KU; k1++)
//                {
//                    for (i1=i; i1<i+MU;i1++)
//                    {
//                        for (j1=j; j1<j+NU;j1++)
//                        {
//                            C[i1*NB+j1] += A[i1*NB+k1] * B[k1*NB+j1];
//                        }
//                    }
//                }
                int c0 = i*NB + j;
                int c1 = c0 + 1;
                int c2 = c1 + 1;
                int c3 = c2 + 1;
                int c4 = c3 + 1;
                int c5 = c4 + 1;
                int c6 = c5 + 1;
                int c7 = c6 + 1;

                int a0 = i*NB+k;
                int a1 = a0+1; // k

                int b00 = k*NB + j;
                int b10 = b00 + 1;
                int b20 = b10 + 1;
                int b30 = b20 + 1;
                int b40 = b30 + 1;
                int b50 = b40 + 1;
                int b60 = b50 + 1;
                int b70 = b60 + 1;
                int b01 = (k+1)*NB + j;
                int b11 = b01 + 1;
                int b21 = b11 + 1;
                int b31 = b21 + 1;
                int b41 = b31 + 1;
                int b51 = b41 + 1;
                int b61 = b51 + 1;
                int b71 = b61 + 1;

                double C0 = C[c0];
                double C1 = C[c1];
                double C2 = C[c2];
                double C3 = C[c3];
                double C4 = C[c4];
                double C5 = C[c5];
                double C6 = C[c6];
                double C7 = C[c7];

                double A0 = A[a0];
                double A1 = A[a1];

                double B00 = B[b00];
                double B10 = B[b10];
                double B20 = B[b20];
                double B30 = B[b30];
                double B40 = B[b40];
                double B50 = B[b50];
                double B60 = B[b60];
                double B70 = B[b70];
                double B01 = B[b01];
                double B11 = B[b11];
                double B21 = B[b21];
                double B31 = B[b31];
                double B41 = B[b41];
                double B51 = B[b51];
                double B61 = B[b61];
                double B71 = B[b71];
            
                C0 += A0*B00;
                C1 += A0*B10;
                C2 += A0*B20;
                C3 += A0*B30;
                C4 += A0*B40;
                C5 += A0*B50;
                C6 += A0*B60;
                C7 += A0*B70;
                C0 += A1*B01;
                C1 += A1*B11;
                C2 += A1*B21;
                C3 += A1*B31;
                C4 += A1*B41;
                C5 += A1*B51;
                C6 += A1*B61;
                C7 += A1*B71;

                C[c0] = C0;
                C[c1] = C1;
                C[c2] = C2;
                C[c3] = C3;
                C[c4] = C4;
                C[c5] = C5;
                C[c6] = C6;
                C[c7] = C7;
            }
        }
    }
          
}

