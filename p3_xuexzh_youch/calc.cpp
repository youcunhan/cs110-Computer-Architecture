#include <omp.h>
#include <emmintrin.h>
#include <iostream>
#include <immintrin.h>
#include <xmmintrin.h>
#include <string.h>


#define muladd(q)\
ta1 = _mm256_loadu_si256((__m256i *)(at + q));\
ta2 = _mm256_loadu_si256((__m256i *)(at + q + 1));\
ta3 = _mm256_loadu_si256((__m256i *)(at + q + 2));\
ta4 = _mm256_loadu_si256((__m256i *)(at + q + 3));\
ta5 = _mm256_loadu_si256((__m256i *)(at + q + 4));\
ta6 = _mm256_loadu_si256((__m256i *)(at + q + 5));\
ta7 = _mm256_loadu_si256((__m256i *)(at + q + 6));\
ta8 = _mm256_loadu_si256((__m256i *)(at + q + 7));\
tb  = _mm256_loadu_si256((__m256i *)(bt + q));\
res1 = _mm256_mullo_epi16(ta1, tb);\
res2 = _mm256_mullo_epi16(ta2, tb);\
res3 = _mm256_mullo_epi16(ta3, tb);\
res4 = _mm256_mullo_epi16(ta4, tb);\
res5 = _mm256_mullo_epi16(ta5, tb);\
res6 = _mm256_mullo_epi16(ta6, tb);\
res7 = _mm256_mullo_epi16(ta7, tb);\
res8 = _mm256_mullo_epi16(ta8, tb);\
sum[0] = _mm256_add_epi16(sum[0],res1);\
sum[1] = _mm256_add_epi16(sum[1],res2);\
sum[2] = _mm256_add_epi16(sum[2],res3);\
sum[3] = _mm256_add_epi16(sum[3],res4);\
sum[4] = _mm256_add_epi16(sum[4],res5);\
sum[5] = _mm256_add_epi16(sum[5],res6);\
sum[6] = _mm256_add_epi16(sum[6],res7);\
sum[7] = _mm256_add_epi16(sum[7],res8)


void calc(int n, const int *a, const int *b, int *c)
{
    int16_t *a_16 = (int16_t *)malloc(n * sizeof(int16_t));
    int16_t *b_16 = (int16_t *)malloc(n * sizeof(int16_t));
    for (int i = 0; i < n >> 3 << 3; i += 8){
        a_16[i] = a[i];
        a_16[i + 1] = a[i + 1];
        a_16[i + 2] = a[i + 2];
        a_16[i + 3] = a[i + 3];
        a_16[i + 4] = a[i + 4];
        a_16[i + 5] = a[i + 5];
        a_16[i + 6] = a[i + 6];
        a_16[i + 7] = a[i + 7];
        b_16[i] = b[i];
        b_16[i + 1] = b[i + 1];
        b_16[i + 2] = b[i + 2];
        b_16[i + 3] = b[i + 3];
        b_16[i + 4] = b[i + 4];
        b_16[i + 5] = b[i + 5];
        b_16[i + 6] = b[i + 6];
        b_16[i + 7] = b[i + 7];
    }

    for (int i = n >> 3 << 3; i < n; i++){
        a_16[i] = a[i];
        b_16[i] = b[i];
    }

#pragma omp parallel for schedule(dynamic)
    for (int k = 0; k < n >> 3 << 3; k += 8)
    {
        int m = n - k - 7;
        register int buffer = 0;
        register int buffer1 = 0;
        register int buffer2 = 0;
        register int buffer3 = 0;
        register int buffer4 = 0;
        register int buffer5 = 0;
        register int buffer6 = 0;
        register int buffer7 = 0;
        __m256i ta1;
        __m256i ta2;
        __m256i ta3;
        __m256i ta4;
        __m256i ta5;
        __m256i ta6;
        __m256i ta7;
        __m256i ta8;
        __m256i tb;

        __m256i res1;
        __m256i res2;
        __m256i res3;
        __m256i res4;
        __m256i res5;
        __m256i res6;
        __m256i res7;
        __m256i res8;
        __m256i sum[8];
        for (int i = 0; i < 8; i++){
            sum[i] = _mm256_setzero_si256();
        }
        for (int i = 0; i < m >> 7 << 7; i += 128){
            const int16_t *at = a_16 + i + k;
            const int16_t *bt = b_16 + i;

            muladd(0);
            muladd(16);
            muladd(32);
            muladd(48);
            muladd(64);
            muladd(80);
            muladd(96);
            muladd(112);

            if (i % 1024 == 0){
                __m256i tmp = _mm256_hadd_epi16(_mm256_hadd_epi16(_mm256_hadd_epi16(sum[0],sum[1]),_mm256_hadd_epi16(sum[2],sum[3])),_mm256_hadd_epi16(_mm256_hadd_epi16(sum[4],sum[5]),_mm256_hadd_epi16(sum[6],sum[7])));
                buffer  += _mm256_extract_epi16(tmp,0) + _mm256_extract_epi16(tmp,8);
                buffer1 += _mm256_extract_epi16(tmp,1) + _mm256_extract_epi16(tmp,9);
                buffer2 += _mm256_extract_epi16(tmp,2) + _mm256_extract_epi16(tmp,10);
                buffer3 += _mm256_extract_epi16(tmp,3) + _mm256_extract_epi16(tmp,11);
                buffer4 += _mm256_extract_epi16(tmp,4) + _mm256_extract_epi16(tmp,12);
                buffer5 += _mm256_extract_epi16(tmp,5) + _mm256_extract_epi16(tmp,13);
                buffer6 += _mm256_extract_epi16(tmp,6) + _mm256_extract_epi16(tmp,14);
                buffer7 += _mm256_extract_epi16(tmp,7) + _mm256_extract_epi16(tmp,15);
                sum[0] = _mm256_setzero_si256();
                sum[1] = _mm256_setzero_si256();
                sum[2] = _mm256_setzero_si256();
                sum[3] = _mm256_setzero_si256();
                sum[4] = _mm256_setzero_si256();
                sum[5] = _mm256_setzero_si256();
                sum[6] = _mm256_setzero_si256();
                sum[7] = _mm256_setzero_si256();

            }
        }
        __m256i tmp = _mm256_hadd_epi16(_mm256_hadd_epi16(_mm256_hadd_epi16(sum[0],sum[1]),_mm256_hadd_epi16(sum[2],sum[3])),_mm256_hadd_epi16(_mm256_hadd_epi16(sum[4],sum[5]),_mm256_hadd_epi16(sum[6],sum[7])));
        buffer  += _mm256_extract_epi16(tmp,0) + _mm256_extract_epi16(tmp,8);
        buffer1 += _mm256_extract_epi16(tmp,1) + _mm256_extract_epi16(tmp,9);
        buffer2 += _mm256_extract_epi16(tmp,2) + _mm256_extract_epi16(tmp,10);
        buffer3 += _mm256_extract_epi16(tmp,3) + _mm256_extract_epi16(tmp,11);
        buffer4 += _mm256_extract_epi16(tmp,4) + _mm256_extract_epi16(tmp,12);
        buffer5 += _mm256_extract_epi16(tmp,5) + _mm256_extract_epi16(tmp,13);
        buffer6 += _mm256_extract_epi16(tmp,6) + _mm256_extract_epi16(tmp,14);
        buffer7 += _mm256_extract_epi16(tmp,7) + _mm256_extract_epi16(tmp,15);
        sum[0] = _mm256_setzero_si256();
        sum[1] = _mm256_setzero_si256();
        sum[2] = _mm256_setzero_si256();
        sum[3] = _mm256_setzero_si256();
        sum[4] = _mm256_setzero_si256();
        sum[5] = _mm256_setzero_si256();
        sum[6] = _mm256_setzero_si256();
        sum[7] = _mm256_setzero_si256();
        for (int i = m >> 7 << 7; i < m; ++i){
            int tmpb = b_16[i];
            buffer  += a_16[i + k]     * tmpb;
            buffer1 += a_16[i + k + 1] * tmpb;
            buffer2 += a_16[i + k + 2] * tmpb;
            buffer3 += a_16[i + k + 3] * tmpb;
            buffer4 += a_16[i + k + 4] * tmpb;
            buffer5 += a_16[i + k + 5] * tmpb;
            buffer6 += a_16[i + k + 6] * tmpb;
            buffer7 += a_16[i + k + 7] * tmpb;
        }

        int a7 = a_16[n - 7],
            a6 = a_16[n - 6],
            a5 = a_16[n - 5],
            a4 = a_16[n - 4],
            a3 = a_16[n - 3],
            a2 = a_16[n - 2],
            a1 = a_16[n - 1],
            b0   = b_16[m],
            b1 = b_16[m + 1],
            b2 = b_16[m + 2],
            b3 = b_16[m + 3],
            b4 = b_16[m + 4],
            b5 = b_16[m + 5],
            b6 = b_16[m + 6];

        buffer   += a7 * b0;
        buffer1 += a6 * b0;
        buffer2 += a5 * b0;
        buffer3 += a4 * b0;
        buffer4 += a3 * b0;
        buffer5 += a2 * b0;
        buffer6 += a1 * b0;

        buffer   += a6 * b1;
        buffer1 += a5 * b1;
        buffer2 += a4 * b1;
        buffer3 += a3 * b1;
        buffer4 += a2 * b1;
        buffer5 += a1 * b1;

        buffer   += a5 * b2;
        buffer1 += a4 * b2;
        buffer2 += a3 * b2;
        buffer3 += a2 * b2;
        buffer4 += a1 * b2;

        buffer   += a4 * b3;
        buffer1 += a3 * b3;
        buffer2 += a2 * b3;
        buffer3 += a1 * b3;

        buffer   += a3 * b4;
        buffer1 += a2 * b4;
        buffer2 += a1 * b4;

        buffer   += a2 * b5;
        buffer1 += a1 * b5;

        buffer   += a1 * b6;


        c[k]     = buffer;
        c[k + 1] = buffer1;
        c[k + 2] = buffer2;
        c[k + 3] = buffer3;
        c[k + 4] = buffer4;
        c[k + 5] = buffer5;
        c[k + 6] = buffer6;
        c[k + 7] = buffer7;
    }


    for (int k = n >> 3 << 3; k < n; k++){
        for (int i = 0; i < n - k; ++i){
            c[k] += a[i + k] * b[i];
        }
    }

}



// void
// calc (int n, const int *a, const int *b, int *c)
// {

//     #pragma omp parallel for
//     for (int k = 0; k < n; k+=20){

//         int m = n - k - 19;
//         __m512i ta;
//         __m512i tb;
//         __m512i sum[20];
//         for (int k = 0; k < 20; k++)
//             sum[k] = _mm512_setzero_epi32();
//         for( int i = 0; i < m/16*16; i+=16){
//             for( int kk = k; kk < k + 20 && kk < n; kk++){
//                 int index = kk - k;
//                 const int* at = a + kk;
//                 ta = _mm512_load_epi32((__m512i*)(at + i));
//                 tb = _mm512_load_epi32((__m512i*)(b + i));
//                 ta = _mm512_mullo_epi32(ta, tb);
//                 sum = _mm512_add_epi32(sum, ta);

//             }
//         }
//         for( int kk = k; kk < k + 20 && kk < n; kk++){
//             int index = kk - k;
//             int *result = new int[16];
//             _mm512_storeu_si512(result ,sum);
//             const int* at = a + kk;

//             int res = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7] + result[8] + result[9] + result[10] + result[11] + result[12] + result[13] + result[14] + result[15];
//             for (int i = m/16*16; i < n - kk ;i++)
//             {
//                 res+=at[i]*b[i]; 
//             }
//             c[kk] = res;
//         }
        
//     }
// }



