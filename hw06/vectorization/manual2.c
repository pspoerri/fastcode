#include <immintrin.h>
#include <stdio.h>
void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size)
{
    int i;
    __m256 m0 = _mm256_set_ps(0.0,0.0,0.0,0.0, h0, h1, h2, h3);
    __m256 m1 = _mm256_set_ps(0.0,0.0,0.0, h0, h1, h2, h3,0.0);
    __m256 m2 = _mm256_set_ps(0.0,0.0, h0, h1, h2, h3,0.0,0.0);
    __m256 m3 = _mm256_set_ps(0.0, h0, h1, h2, h3,0.0,0.0,0.0);
   
    const int dpmask = 0xf1; 
    __m128 sel = _mm_set_ps(1.0,1.0,1.0,1.0);
    // use 32byte alignment
    __m128 k1 = _mm_load_ps(x);
    __m128 k2;
    for (i=0; i<size-3; i+=4)
    {
        k2 = _mm_loadu_ps(x+i+4);
        
        __m256 l; // = _mm256_loadu_ps(x+i);
        l = _mm256_insertf128_ps(l, k1, 0);
        l = _mm256_insertf128_ps(l, k2, 1);
        __m256 a0 = _mm256_mul_ps(l,m0); 
        __m256 a1 = _mm256_mul_ps(l,m1); 
        __m256 a2 = _mm256_mul_ps(l,m2); 
        __m256 a3 = _mm256_mul_ps(l,m3);

        __m128 z0 = _mm256_extractf128_ps(a0,0);

        __m128 al1 = _mm256_extractf128_ps (a1, 0);
        __m128 ar1 = _mm256_extractf128_ps (a1, 1);
        __m128 z1 = _mm_add_ps(al1, ar1);

        __m128 al2 = _mm256_extractf128_ps (a2, 0);
        __m128 ar2 = _mm256_extractf128_ps (a2, 1);
        __m128 z2 = _mm_add_ps(al2, ar2);

        __m128 al3 = _mm256_extractf128_ps (a3, 0);
        __m128 ar3 = _mm256_extractf128_ps (a3, 1);
        __m128 z3 = _mm_add_ps(al3, ar3);
        
        __m128 r0 = _mm_dp_ps(z0, sel, dpmask);
        __m128 r1 = _mm_dp_ps(z1, sel, dpmask);
        __m128 r2 = _mm_dp_ps(z2, sel, dpmask);
        __m128 r3 = _mm_dp_ps(z3, sel, dpmask);

        __m128 s0 =  _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1,0,2,0));
        __m128 s1 =  _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(1,0,2,0));
        __m128 res =  _mm_shuffle_ps(s0, s1, _MM_SHUFFLE(2,0,2,0));
        
        _mm_store_ps(y+i,res); // store it
        k1 = k2;
    }

//    printf("h0 %f, h1 %f, h2 %f, h3 %f\n", h0, h1, h2, h3);
//    printf("%f %f %f %f %f %f %f %f\n", y[0], y[1], y[2], y[3], y[4],y[5], y[6],y[7]);
}

