inline void cos_bench(double * x, double * y, long int n)
{
  long int i;

  for(i = 0; i < n; i++) {
    y[i] = cos(x[i]);
  }

}

inline void sin_bench(double * x, double * y, long int n)
{
    long int i;
    
    for(i = 0; i < n; i++) {
        y[i] = sin(x[i]);
    }
    
}

inline void log_bench(double * x, double * y, long int n)
{
    long int i;
    
    for(i = 0; i < n; i++) {
        y[i] = log(x[i]+0.1);
    }
    
}

inline void exp_bench(double * x, double * y, long int n)
{
    long int i;
    
    for(i = 0; i < n; i++) {
        y[i] = exp(x[i]);
    }
    
}

inline void oneover_bench(double * x, double * y, long int n)
{
    long int i;
    
    for(i = 0; i < n; i++) {
        y[i] = 1.0/(x[i]+1.0);
    }
    
}

inline void squared_bench(double * x, double * y, long int n)
{
    long int i;
    
    for(i = 0; i < n; i++) {
        y[i] = x[i]*x[i];
    }
    
}


//Add the microbenchmark functions here:
