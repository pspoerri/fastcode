#include <immintrin.h>
void warmup(float *x, float *y, int size, float alpha)
{
    int i;
    __m256 m = _mm256_set_ps(
            2.0, 0.5/alpha, 
            2.0, 0.5/alpha, 
            2.0, 0.5/alpha, 
            2.0, 0.5/alpha);
    __m256 zero = _mm256_load_ps(
            0 , 0
            0 , 0
            0 , 0
            0 , 0);
    
    for (i=0; i<size; i+=4)
    {
        __m256 t = _mm256_load_ps(x+2*i);
        __m256 l = _mm256_mul_ps(t, m); // premultiply
        __m256 r = _mm256_permute2f128_ps( x , x , 1); // swap lower and higher 128 bits
        __m256 res = _mm256_hadd_ps(l, r);
        __m128 s = _mm256_extractf128_ps (res, s);
        _mm_store_ps(y+i,s); // store it
    }
}
