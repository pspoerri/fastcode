void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size)
{
    #pragma ivdep
    int i;

    #pragma vector aligned
    for (i=0; i<size-3; i++)
    {
        y[i] = h3*x[i] + h2*x[i+1] + h1*x[i+2] + h0*x[i+3];
    }
}

