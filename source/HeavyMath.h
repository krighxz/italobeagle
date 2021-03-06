/**
 * Copyright (c) 2014,2015 Enzien Audio, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, and/or
 * sublicense copies of the Software, strictly on a non-commercial basis,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef _HEAVY_MATH_H_
#define _HEAVY_MATH_H_

#include "Utils.h"

// https://software.intel.com/sites/landingpage/IntrinsicsGuide/

static inline void __hv_zero_f(hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_setzero_ps();
#elif HV_SIMD_SSE
  *bOut = _mm_setzero_ps();
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = 0.0f;
#endif
}

static inline void __hv_load_f(float *bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_load_ps(bIn);
#elif HV_SIMD_SSE
  *bOut = _mm_load_ps(bIn);
#elif HV_SIMD_NEON
  *bOut = vld1q_f32(bIn);
#else // HV_SIMD_NONE
  *bOut = *bIn;
#endif
}

static inline void __hv_store_f(float *bOut, hv_bInf_t bIn) {
#if HV_SIMD_AVX
  _mm256_store_ps(bOut, bIn);
#elif HV_SIMD_SSE
  _mm_store_ps(bOut, bIn);
#elif HV_SIMD_NEON
  vst1q_f32(bOut, bIn);
#else // HV_SIMD_NONE
  *bOut = bIn;
#endif
}

static inline void sLog_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn > 0.0f) ? hv_log_f(bIn) : 0.0f;
#endif
}

static inline void sLog10_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn > 0.0f) ? hv_log10_f(bIn) : 0.0f;
#endif
}

static inline void sLog2_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn > 0.0f) ? hv_log2_f(bIn) : 0.0f;
#endif
}

// NOTE(mhroth): this is a pretty ghetto implementation
static inline void __hv_cos_f(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_set_ps(
      hv_cos_f(bIn[7]), hv_cos_f(bIn[6]), hv_cos_f(bIn[5]), hv_cos_f(bIn[4]),
      hv_cos_f(bIn[3]), hv_cos_f(bIn[2]), hv_cos_f(bIn[1]), hv_cos_f(bIn[0]));
#elif HV_SIMD_SSE
  *bOut = _mm_set_ps(hv_cos_f(bIn[3]), hv_cos_f(bIn[2]), hv_cos_f(bIn[1]), hv_cos_f(bIn[0]));
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_cos_f(bIn);
#endif
}

static inline void sAcos_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_acos_f(bIn);
#endif
}

static inline void sCosh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_cosh_f(bIn);
#endif
}

static inline void sAcosh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_acosh_f(bIn);
#endif
}

static inline void sSin_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_sin_f(bIn);
#endif
}

static inline void sAsin_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_asin_f(bIn);
#endif
}

static inline void sSinh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_sinh_f(bIn);
#endif
}

static inline void sAsinh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_asinh_f(bIn);
#endif
}

static inline void sTan_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_tan_f(bIn);
#endif
}

static inline void sAtan_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_atan_f(bIn);
#endif
}

static inline void sAtan2_process(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_atan2_f(bIn0, bIn1);
#endif
}

static inline void sTanh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_tanh_f(bIn);
#endif
}

static inline void sAtanh_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_atanh_f(bIn);
#endif
}

// NOTE(mhroth): use of sqrt is absolute and total MURDER. Make do with recipocal sqrt if possible!!
static inline void __hv_sqrt_f(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  static const __m256 zero = (__m256) {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  *bOut = _mm256_sqrt_ps(_mm256_max_ps(zero, bIn));
#elif HV_SIMD_SSE
  static const __m128 zero = (__m128) {0.0f, 0.0f, 0.0f, 0.0f};
  *bOut = _mm_sqrt_ps(_mm_max_ps(zero, bIn)); // ensure that all values are positive
#elif HV_SIMD_NEON
  *bOut = vsqrtq_f32(bIn);
#else // HV_SIMD_NONE
  *bOut = hv_sqrt_f(hv_max_f(0.0f, bIn));
#endif
}

static inline void __hv_abs_f(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  static const __m256 mask = (__m256) {-0.0f, -0.0f, -0.0f, -0.0f, -0.0f, -0.0f, -0.0f, -0.0f};
  *bOut = _mm256_andnot_ps(mask, bIn);
#elif HV_SIMD_SSE
  static const __m128 mask = (__m128) {-0.0f, -0.0f, -0.0f, -0.0f}; // == 1 << 31
  *bOut = _mm_andnot_ps(mask, bIn);
#elif HV_SIMD_NEON
  *bOut = vabsq_f32(hv_bInf_t);
#else // HV_SIMD_NONE
  *bOut = hv_abs_f(bIn);
#endif
}

static inline void sExp_process(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_exp_f(bIn);
#endif
}

static inline void __hv_ceil_f(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_ceil_ps(bIn);
#elif HV_SIMD_SSE
  *bOut = _mm_ceil_ps(bIn);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_ceil_f(bIn);
#endif
}

static inline void __hv_floor_f(hv_bInf_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_floor_ps(bIn);
#elif HV_SIMD_SSE
  *bOut = _mm_floor_ps(bIn);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_floor_f(bIn);
#endif
}

// __add~f
static inline void __hv_add_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_add_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_add_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vaddq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = bIn0 + bIn1;
#endif
}

// __add~i
static inline void __hv_add_i(hv_bIni_t bIn0, hv_bIni_t bIn1, hv_bOuti_t bOut) {
#if HV_SIMD_AVX
  __m128i x = _mm_add_epi32(_mm256_castsi256_si128(bIn0), _mm256_castsi256_si128(bIn1));
  __m128i y = _mm_add_epi32(_mm256_extractf128_si256(bIn0, 1), _mm256_extractf128_si256(bIn1, 1));
  *bOut = _mm256_insertf128_si256(_mm256_castsi128_si256(x), y, 1);
#elif HV_SIMD_SSE
  *bOut = _mm_add_epi32(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vaddq_s32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = bIn0 + bIn1;
#endif
}

// __sub~f
static inline void __hv_sub_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_sub_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_sub_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vsubq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = bIn0 - bIn1;
#endif
}

// __mul~f
static inline void __hv_mul_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_mul_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_mul_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vmulq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = bIn0 * bIn1;
#endif
}

// __*~i
static inline void __hv_mul_i(hv_bIni_t bIn0, hv_bIni_t bIn1, hv_bOuti_t bOut) {
#if HV_SIMD_AVX
  __m128i x = _mm_mullo_epi32(_mm256_castsi256_si128(bIn0), _mm256_castsi256_si128(bIn1));
  __m128i y = _mm_mullo_epi32(_mm256_extractf128_si256(bIn0, 1), _mm256_extractf128_si256(bIn1, 1));
  *bOut = _mm256_insertf128_si256(_mm256_castsi128_si256(x), y, 1);
#elif HV_SIMD_SSE
  *bOut = _mm_mullo_epi32(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vmulq_s32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = bIn0 * bIn1;
#endif
}

// __cast~if
static inline void __hv_cast_if(hv_bIni_t bIn, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cvtepi32_ps(bIn);
#elif HV_SIMD_SSE
  *bOut = _mm_cvtepi32_ps(bIn);
#elif HV_SIMD_NEON
  *bOut = vcvtq_f32_s32(bIn);
#else // HV_SIMD_NONE
  *bOut = (float) bIn;
#endif
}

// __cast~fi
static inline void __hv_cast_fi(hv_bInf_t bIn, hv_bOuti_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cvtps_epi32(bIn);
#elif HV_SIMD_SSE
  *bOut = _mm_cvtps_epi32(bIn);
#elif HV_SIMD_NEON
  *bOut = vcvtq_s32_f32(bIn);
#else // HV_SIMD_NONE
  *bOut = (int) bIn;
#endif
}

static inline void __hv_div_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_div_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_div_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vdivq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = (bIn1 != 0.0f) ? (bIn0 / bIn1) : 0.0f;
#endif
}

static inline void __hv_min_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_min_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_min_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vminq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = hv_min_f(bIn0, bIn1);
#endif
}

static inline void __hv_max_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_max_ps(bIn0, bIn1);
#elif HV_SIMD_SSE
  *bOut = _mm_max_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
  *bOut = vmaxq_f32(bIn0, bIn1);
#else // HV_SIMD_NONE
  *bOut = hv_max_f(bIn0, bIn1);
#endif
}

static inline void __hv_pow_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_set_ps(
      hv_pow_f(bIn0[7], bIn1[7]),
      hv_pow_f(bIn0[6], bIn1[6]),
      hv_pow_f(bIn0[5], bIn1[5]),
      hv_pow_f(bIn0[4], bIn1[4]),
      hv_pow_f(bIn0[3], bIn1[3]),
      hv_pow_f(bIn0[2], bIn1[2]),
      hv_pow_f(bIn0[1], bIn1[1]),
      hv_pow_f(bIn0[0], bIn1[0]));
#elif HV_SIMD_SSE
  *bOut = _mm_set_ps(
      hv_pow_f(bIn0[3], bIn1[3]),
      hv_pow_f(bIn0[2], bIn1[2]),
      hv_pow_f(bIn0[1], bIn1[1]),
      hv_pow_f(bIn0[0], bIn1[0]));
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = hv_pow_f(bIn0, bIn1);
#endif
}

static inline void __hv_gt_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cmp_ps(bIn0, bIn1, _CMP_GT_OQ);
#elif HV_SIMD_SSE
  *bOut = _mm_cmpgt_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn0 > bIn1) ? 1.0f : 0.0f;
#endif
}

static inline void __hv_gte_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cmp_ps(bIn0, bIn1, _CMP_GE_OQ);
#elif HV_SIMD_SSE
  *bOut = _mm_cmpge_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn0 >= bIn1) ? 1.0f : 0.0f;
#endif
}

static inline void __hv_lt_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cmp_ps(bIn0, bIn1, _CMP_LT_OQ);
#elif HV_SIMD_SSE
  *bOut = _mm_cmplt_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn0 < bIn1) ? 1.0f : 0.0f;
#endif
}

static inline void __hv_lte_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_cmp_ps(bIn0, bIn1, _CMP_LE_OQ);
#elif HV_SIMD_SSE
  *bOut = _mm_cmple_ps(bIn0, bIn1);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (bIn0 <= bIn1) ? 1.0f : 0.0f;
#endif
}

static inline void sBitwiseXor_process(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
//#error todo implement me
#elif HV_SIMD_SSE
//#error todo implement me
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  *bOut = (float) (((int) bIn0) ^ ((int) bIn1));
#endif
}

static inline void __hv_and_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  *bOut = _mm256_and_ps(bIn1, bIn0);
#elif HV_SIMD_SSE
  *bOut = _mm_and_ps(bIn1, bIn0);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  if (bIn0 == 0.0f || bIn1 == 0.0f) *bOut = 0.0f;
  else if (bIn0 == 1.0f) *bOut = bIn1;
  else if (bIn1 == 1.0f) *bOut = bIn0;
  else hv_assert(0); // TODO(mhroth): floating point & is pretty much a bad idea, only used for if~
#endif
}

static inline void __hv_fma_f(hv_bInf_t bIn0, hv_bInf_t bIn1, hv_bInf_t bIn2, hv_bOutf_t bOut) {
#if HV_SIMD_AVX
  #if HV_SIMD_FMA
    *bOut = _mm256_fmadd_ps(bIn0, bIn1, bIn2);
  #else
    *bOut = _mm256_add_ps(_mm256_mul_ps(bIn0, bIn1), bIn2);
  #endif // HV_SIMD_FMA
#elif HV_SIMD_SSE
  #if HV_SIMD_FMA
    *bOut = _mm_fmadd_ps(bIn0, bIn1, bIn2);
  #else
    *bOut = _mm_add_ps(_mm_mul_ps(bIn0, bIn1), bIn2);
  #endif // HV_SIMD_FMA
#elif HV_SIMD_NEON
  *bOut = vfmaq_f32(bIn0, bIn1, bIn2);
#else // HV_SIMD_NONE
  *bOut = hv_fma_f(bIn0, bIn0, bIn2); // (bIn0 * bIn1) + bIn2;
#endif
}

#endif // _HEAVY_MATH_H_
