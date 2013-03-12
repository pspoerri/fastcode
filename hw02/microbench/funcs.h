inline void cos_bench(double * x, double * y, long int n)
{
  long int i;

  for(i = 0; i < n; i++) {
    y[i] = cos(x[i]);
  }

}

//Add the microbenchmark functions here:
