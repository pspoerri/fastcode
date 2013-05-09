#include <immintrin.h>
#include <stdio.h>
void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size)
{
    int i;
    __m256 m0 = _mm256_set_ps(0.0,0.0,0.0,0.0, h0, h1, h2, h3);
    __m256 m1 = _mm256_set_ps(0.0,0.0,0.0, h0, h1, h2, h3,0.0);
    __m256 m2 = _mm256_set_ps(0.0,0.0, h0, h1, h2, h3,0.0,0.0);
    __m256 m3 = _mm256_set_ps(0.0, h0, h1, h2, h3,0.0,0.0,0.0);
    
    // use 32byte alignment
    for (i=0; i<size-3; i+=4)
    {
        __m256 l = _mm256_loadu_ps(x+i);
        __m256 a0 = _mm256_mul_ps(l,m0); 
        __m256 a1 = _mm256_mul_ps(l,m1); 
        __m256 a2 = _mm256_mul_ps(l,m2); 
        __m256 a3 = _mm256_mul_ps(l,m3);

        // z0 is a0
        __m256 z1 = _mm256_hadd_ps(a1, _mm256_permute2f128_ps( a1 , a1 , 1));
        __m256 z2 = _mm256_hadd_ps(a2, _mm256_permute2f128_ps( a2 , a2 , 1));
        __m256 z3 = _mm256_hadd_ps(a3, _mm256_permute2f128_ps( a3 , a3 , 1));
        

        __m256 p0 = _mm256_hadd_ps(a0, z1);
        __m256 p1 = _mm256_hadd_ps(z2, z3);

        __m256 res = _mm256_hadd_ps(p0, p1);
        
        __m128 s = _mm256_extractf128_ps (res, 0);
        _mm_store_ps(y+i,s); // store it
    }

//    printf("h0 %f, h1 %f, h2 %f, h3 %f\n", h0, h1, h2, h3);
//    printf("%f %f %f %f %f %f %f %f\n", y[0], y[1], y[2], y[3], y[4],y[5], y[6],y[7]);
}

