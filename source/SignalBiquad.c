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

#include "SignalBiquad.h"

// http://reanimator-web.appspot.com/articles/simdiir

hv_size_t sBiquad_init(SignalBiquad *o) {
  o->x1 = 0.0f;
  o->x2 = 0.0f;
  o->y1 = 0.0f;
  o->y2 = 0.0f;
  return 0;
}

void sBiquad_process(SignalBiquad *o, hv_bInf_t bIn, hv_bInf_t bX0, hv_bInf_t bX1, hv_bInf_t bX2, hv_bInf_t bY1, hv_bInf_t bY2, hv_bOutf_t bOut) {
  *bOut = bIn;
//#if __AVX__
//
//  static const __m256 HI_MASK = (__m256) {0x0, 0x0, 0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
//
//  __m256 x0 = _mm256_mul_ps(bIn, bX0);
//
//  __m128 a = _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(_mm256_castps256_ps128(bIn)), 4)); // lo
//  __m256 x1 = _mm256_castps128_ps256(_mm_or_ps(a, _mm_set_ss(o->x1)));
//  x1 = _mm256_andnot_ps(HI_MASK, x1);
//  __m128 b = _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(_mm256_extractf128_ps(bIn, 1)), 4)); // hi
//  b = _mm_or_ps(b, _mm_set_ss(bIn[3]));
//  __m256 x1b = _mm256_castps128_ps256(b);
//  x1b = _mm256_and_ps(HI_MASK, x1b);
////  x1 = _mm256_insertf128_ps(x1, _mm_add_ps(b, _mm_set_ss(bIn[3])), 1);
//  x1 = _mm256_or_ps(x1, x1b);
//  x1 = _mm256_mul_ps(x1, bX1);
//
//  __m256 x2 = _mm256_mul_ps(_mm256_set_ps(bIn[5], bIn[4], bIn[3], bIn[2], bIn[1], bIn[0], o->x1, o->x2), bX2);
//  __m256 n = _mm256_add_ps(_mm256_add_ps(x0, x1), x2);
//  float y0 = n[0] - o->y1*bY1[0] - o->y2*bY2[0];
//  float y1 = n[1] - y0*bY1[1] - o->y1*bY2[1];
//  float y2 = n[2] - y1*bY1[2] - y0*bY2[2];
//  float y3 = n[3] - y2*bY1[3] - y1*bY2[3];
//  float y4 = n[4] - y3*bY1[4] - y1*bY2[4];
//  float y5 = n[5] - y4*bY1[5] - y2*bY2[5];
//  float y6 = n[6] - y5*bY1[6] - y3*bY2[6];
//  float y7 = n[7] - y6*bY1[7] - y4*bY2[7];
//  *bOut = _mm256_set_ps(y7, y6, y5, y4, y3, y2, y1, y0);
//  o->x1 = bIn[7]; o->x2 = bIn[6];
//  o->y1 = y7; o->y2 = y7;
//
//
////  float y0 = bIn[0]*bX0[0] + o->x1*bX1[0] + o->x2*bX2[0] - o->y1*bY1[0] - o->y2*bY2[0];
////  float y1 = bIn[1]*bX0[1] + bIn[0]*bX1[1] + o->x1*bX2[1] - y0*bY1[1] - o->y1*bY2[1];
////  float y2 = bIn[2]*bX0[2] + bIn[1]*bX1[2] + bIn[0]*bX2[2] - y1*bY1[2] - y0*bY2[2];
////  float y3 = bIn[3]*bX0[3] + bIn[2]*bX1[3] + bIn[1]*bX2[3] - y2*bY1[3] - y1*bY2[3];
////  float y4 = bIn[4]*bX0[0] + bIn[3]*bX1[0] + bIn[2]*bX2[0] - y3*bY1[0] - y2*bY2[0];
////  float y5 = bIn[5]*bX0[1] + bIn[4]*bX1[1] + bIn[3]*bX2[1] - y4*bY1[1] - y3*bY2[1];
////  float y6 = bIn[6]*bX0[2] + bIn[5]*bX1[2] + bIn[4]*bX2[2] - y5*bY1[2] - y4*bY2[2];
////  float y7 = bIn[7]*bX0[3] + bIn[6]*bX1[3] + bIn[5]*bX2[3] - y6*bY1[3] - y5*bY2[3];
////  *bOut = _mm256_set_ps(y7, y6, y5, y4, y3, y2, y1, y0);
////  o->x1 = bIn[7]; o->x2 = bIn[6];
////  o->y1 = y7; o->y2 = y6;
//#elif __SSE__
//  // 21 operations for 4 output values (5.25 ops/value)
//  __m128 x0 = _mm_mul_ps(bIn, bX0);
//  __m128 x1 = _mm_mul_ps(_mm_set_ps(bIn[2], bIn[1], bIn[0], o->x1), bX1);
//  __m128 x2 = _mm_mul_ps(_mm_set_ps(bIn[1], bIn[0], o->x1, o->x2), bX2);
//  __m128 n = _mm_add_ps(_mm_add_ps(x0, x1), x2);
//  float y0 = n[0] - o->y1*bY1[0] - o->y2*bY2[0];
//  float y1 = n[1] - y0*bY1[1] - o->y1*bY2[1];
//  float y2 = n[2] - y1*bY1[2] - y0*bY2[2];
//  float y3 = n[3] - y2*bY1[3] - y1*bY2[3];
//  *bOut = _mm_set_ps(y3, y2, y1, y0);
//  o->x1 = bIn[3]; o->x2 = bIn[2];
//  o->y1 = y3; o->y2 = y2;
//#else
//  bOut[0] = bIn[0]*bX0[0] + o->x1*bX1[0] + o->x2*bX2[0] - o->y1*bY1[0] - o->y2*bY2[0];
//  bOut[1] = bIn[1]*bX0[1] + bIn[0]*bX1[1] + o->x1*bX2[1] - bOut[0]*bY1[1] - o->y1*bY2[1];
//  bOut[2] = bIn[2]*bX0[2] + bIn[1]*bX1[2] + bIn[0]*bX2[2] - bOut[1]*bY1[2] - bOut[0]*bY2[2];
//  bOut[3] = bIn[3]*bX0[3] + bIn[2]*bX1[3] + bIn[1]*bX2[3] - bOut[2]*bY1[3] - bOut[1]*bY2[3];
//  o->x1 = bIn[3]; o->x2 = bIn[2];
//  o->y1 = bOut[3]; o->y2 = bOut[2];
//#endif
}

static void sBiquad_k_updateCoefficients(SignalBiquad_k *const o) {
  // calculate all filter coefficients in the double domain
#if HV_SIMD_AVX || HV_SIMD_SSE
  double b0 = (double) o->b0;
  double b1 = (double) o->b1;
  double b2 = (double) o->b2;
  double a1 = (double) -o->a1;
  double a2 = (double) -o->a2;

  double coeffs[4][8] =
  {
    { 0,  0,  0,  b0, b1, b2, a1, a2 },
    { 0,  0,  b0, b1, b2, 0,  a2, 0  },
    { 0,  b0, b1, b2, 0,  0,  0,  0  },
    { b0, b1, b2, 0,  0,  0,  0,  0  },
  };

  for (int i = 0; i < 8; i++) {
    coeffs[1][i] += a1*coeffs[0][i];
    coeffs[2][i] += a1*coeffs[1][i] + a2*coeffs[0][i];
    coeffs[3][i] += a1*coeffs[2][i] + a2*coeffs[1][i];
  }

  o->coeff_xp3 = _mm_set_ps((float) coeffs[3][0], (float) coeffs[2][0], (float) coeffs[1][0], (float) coeffs[0][0]);
  o->coeff_xp2 = _mm_set_ps((float) coeffs[3][1], (float) coeffs[2][1], (float) coeffs[1][1], (float) coeffs[0][1]);
  o->coeff_xp1 = _mm_set_ps((float) coeffs[3][2], (float) coeffs[2][2], (float) coeffs[1][2], (float) coeffs[0][2]);
  o->coeff_x0 =  _mm_set_ps((float) coeffs[3][3], (float) coeffs[2][3], (float) coeffs[1][3], (float) coeffs[0][3]);
  o->coeff_xm1 = _mm_set_ps((float) coeffs[3][4], (float) coeffs[2][4], (float) coeffs[1][4], (float) coeffs[0][4]);
  o->coeff_xm2 = _mm_set_ps((float) coeffs[3][5], (float) coeffs[2][5], (float) coeffs[1][5], (float) coeffs[0][5]);
  o->coeff_ym1 = _mm_set_ps((float) coeffs[3][6], (float) coeffs[2][6], (float) coeffs[1][6], (float) coeffs[0][6]);
  o->coeff_ym2 = _mm_set_ps((float) coeffs[3][7], (float) coeffs[2][7], (float) coeffs[1][7], (float) coeffs[0][7]);
#elif HV_SIMD_NEON
#error // TODO(mhroth): implement this!
#endif
  // NOTE(mhroth): not necessary to calculate any coefficients for HV_SIMD_NONE case
}

hv_size_t sBiquad_k_init(SignalBiquad_k *o, float b0, float b1, float b2, float a1, float a2) {
  // initialise filter coefficients
  o->b0 = b0;
  o->b1 = b1;
  o->b2 = b2;
  o->a1 = a1;
  o->a2 = a2;
  sBiquad_k_updateCoefficients(o);

  // clear filter state
#if HV_SIMD_AVX || HV_SIMD_SSE
  o->xm1 = _mm_setzero_ps();
  o->xm2 = _mm_setzero_ps();
  o->ym1 = _mm_setzero_ps();
  o->ym2 = _mm_setzero_ps();
#elif HV_SIMD_NEON
#error // TODO(mhroth): implement this!
#else // HV_SIMD_NONE
  o->xm1 = 0.0f;
  o->xm2 = 0.0f;
  o->ym1 = 0.0f;
  o->ym2 = 0.0f;
#endif
  return 0;
}

void sBiquad_k_onMessage(SignalBiquad_k *o, int letIn, const HvMessage *const m) {
  if (msg_isFloat(m,0)) {
    switch (letIn) {
      case 1: o->b0 = msg_getFloat(m,0); break;
      case 2: o->b1 = msg_getFloat(m,0); break;
      case 3: o->b2 = msg_getFloat(m,0); break;
      case 4: o->a1 = msg_getFloat(m,0); break;
      case 5: o->a2 = msg_getFloat(m,0); break;
      default: return;
    }
    sBiquad_k_updateCoefficients(o);
  }
}
