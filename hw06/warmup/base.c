void warmup(float *x, float *y, int size, float alpha)
{
    #pragma ivdep
    int i;

    #pragma vector aligned
    for (i=0; i<size; i++)
    {
        y[i] = x[2*i]+x[2*i]+x[2*i+1]/alpha;
    }
}
