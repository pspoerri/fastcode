#ifndef N
#error N is not defined
#endif

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being N x N matrices
void compute() {

    const int MU = 1;
    const int NU = 8;
    const int KU = 2;

    int i0, j0, k0;
    int i,j,k, i1, j1, k1;
    for (i0=0; i0<N; i0+=NB)
    {
        for (j0=0; j0<N; j0+=NB)
        {
            for (k0=0; k0<N; k0+=NB) 
            {
                for (i=i0; i<i0+NB; i+=MU)
                {
                    for (j=j0; j<j0+NB; j+=NU)
                    {
                        double C0 = C[i*N + j    ];
                        double C1 = C[i*N + j + 1];
                        double C2 = C[i*N + j + 2];
                        double C3 = C[i*N + j + 3];
                        double C4 = C[i*N + j + 4];
                        double C5 = C[i*N + j + 5];
                        double C6 = C[i*N + j + 6];
                        double C7 = C[i*N + j + 7];
                        for (k=k0; k<k0+NB; k+=KU)
                        {

                            double A0 = A[i*N+k];
                            double A1 = A[i*N+k+1];

                            double B00 = B[k*N + j        ];
                            double B10 = B[k*N + j + 1    ];
                            double B20 = B[k*N + j + 2    ];
                            double B30 = B[k*N + j + 3    ];
                            double B40 = B[k*N + j + 4    ];
                            double B50 = B[k*N + j + 5    ];
                            double B60 = B[k*N + j + 6    ];
                            double B70 = B[k*N + j + 7    ];
                            double B01 = B[(k+1)*N + j    ];
                            double B11 = B[(k+1)*N + j + 1];
                            double B21 = B[(k+1)*N + j + 2];
                            double B31 = B[(k+1)*N + j + 3];
                            double B41 = B[(k+1)*N + j + 4];
                            double B51 = B[(k+1)*N + j + 5];
                            double B61 = B[(k+1)*N + j + 6];
                            double B71 = B[(k+1)*N + j + 7];
                        
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


                        }
                        C[i*N + j    ] = C0;
                        C[i*N + j + 1] = C1;
                        C[i*N + j + 2] = C2;
                        C[i*N + j + 3] = C3;
                        C[i*N + j + 4] = C4;
                        C[i*N + j + 5] = C5;
                        C[i*N + j + 6] = C6;
                        C[i*N + j + 7] = C7;
                    }
                }
            }
        }
    }
}
