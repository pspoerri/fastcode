#include "main.h"
#include "microbench.h"
#include <vector>
#include <iostream>
void fill_data(double *x, double *y, long int n, double val) {
    for(long int j = 0; j < n; j++) x[j] = val;
    for(long int j = 0; j < n; j++) y[j] = val;
}

void test_sin(double *x, double *y, long int n, double val) {
    double dest, r;
    fill_data(x,y,n, val);
    r = microbench_sin(x,y,&dest, n);
    r = r/(double(n));
    std::cerr << "dest=" << dest << std::endl;
    std::cerr << "Time for sin(" << val << "): " << r << std::endl;
    std::cout << "sin " << val << " " << r << std::endl;
}

void test_log(double *x, double *y, long int n, double val) {
    double dest, r;
    fill_data(x,y,n, val);
    r = microbench_log(x,y,&dest, n);
    r = r/(double(n));
    std::cerr << "dest=" << dest << std::endl;
    std::cerr << "Time for log(" << val << "+0.1): " << r << std::endl;
    std::cout << "log " << val << " " << r << std::endl;
}

void test_exp(double *x, double *y, long int n, double val) {
    double dest, r;
    fill_data(x,y,n, val);
    r = microbench_exp(x,y,&dest, n);
    r = r/(double(n));
    std::cerr << "dest=" << dest << std::endl;
    std::cerr << "Time for exp(" << val << "): " << r << std::endl;
    std::cout << "exp " << val << " " << r << std::endl;
}

void test_oneover(double *x, double *y, long int n, double val) {
    double dest, r;
    fill_data(x,y,n, val);
    r = microbench_oneover(x,y,&dest, n);
    r = r/(double(n));
    std::cerr << "dest=" << dest << std::endl;
    std::cerr << "Time for 1/(" << val << "+1.0): " << r <<  std::endl;
    std::cout << "oneover " << val << " " << r << std::endl;

}

void test_squared(double *x, double *y, long int n, double val) {
    double dest, r;
    fill_data(x,y,n, val);
    r = microbench_squared(x,y,&dest, n);
    r = r/(double(n));
    std::cerr << "dest=" << dest << std::endl;
    std::cerr << "Time for (" << val << "^2): " << r << std::endl;
    std::cout << "squared " << val << " " << r << std::endl;
}

void run_tests(double *x, double *y, long int n, double val) {
    std::cout << "Running tests with " << val << std::endl;
    test_sin(x, y, n, val);
    test_log(x, y, n, val);
    test_exp(x, y, n, val);
    test_oneover(x, y, n, val);
    test_squared(x, y, n, val);
}
int main(int argc, char **argv){
  
  long int i, j, n;
  double *x,*y, dest, r;
  
  n = 32*1024/8/2;
  x = (double*)malloc(n*sizeof(double));
  y = (double*)malloc(n*sizeof(double));

  
  // Positions with no measurements are filled with 0s.
  run_tests(x,y,n, 0.0);  
  run_tests(x,y,n, 0.9);  
  run_tests(x,y,n, 1.1);  
  run_tests(x,y,n, 4.12345);  
    
  free(x);
  free(y); 
  return 0;
}
