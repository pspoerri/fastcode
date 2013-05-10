#include <immintrin.h>
#include <stdio.h>
void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size)
{
    int i;
    __m128 m0 = _mm_set_ps(h3,h3,h3,h3);
    __m128 m1 = _mm_set_ps(h2,h2,h2,h2);
    __m128 m2 = _mm_set_ps(h1,h1,h1,h1);
    __m128 m3 = _mm_set_ps(h0,h0,h0,h0);
    __m128 l, r, a0, a1, a2, a3, b0, b1, b2, b3;
    __m128i il, ir;
    
    l = _mm_load_ps(x+i);
    il = _mm_castps_si128(l);
    for (i=0; i<size-3; i+=4)
    {
        r = _mm_load_ps(x+i+4);
        ir = _mm_castps_si128(r);
        
        a0 = l;
        a1 = _mm_castsi128_ps(_mm_alignr_epi8(ir,il,4));
        a2 = _mm_castsi128_ps(_mm_alignr_epi8(ir,il,8));
        a3 = _mm_castsi128_ps(_mm_alignr_epi8(ir,il,12));
        b0 = _mm_mul_ps(a0,m0);
        b1 = _mm_mul_ps(a1,m1);
        b2 = _mm_mul_ps(a2,m2);
        b3 = _mm_mul_ps(a3,m3);

        __m128 s1 = _mm_add_ps(b0,b1);
        __m128 s2 = _mm_add_ps(b2,b3);
        __m128 s = _mm_add_ps(s1,s2);
        _mm_store_ps(y+i,s); // store it

        l = r;
        il = ir;
    }
}

