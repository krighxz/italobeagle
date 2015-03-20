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

#include "SignalLine.h"

hv_size_t sLine_init(SignalLine *o) {
#if HV_SIMD_AVX
  o->n = _mm_set1_epi32(0);
  o->x = _mm256_set1_ps(0.0f);
  o->m = _mm256_set1_ps(0.0f);
  o->t = _mm256_set1_ps(0.0f);
#elif HV_SIMD_SSE
  o->n = _mm_set1_epi32(0);
  o->x = _mm_set1_ps(0.0f);
  o->m = _mm_set1_ps(0.0f);
  o->t = _mm_set1_ps(0.0f);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
  o->n = 0;
  o->x = 0.0f;
  o->m = 0.0f;
  o->t = 0.0f;
#endif
  return 0;
}

void sLine_onMessage(HvBase *_c, SignalLine *o, int letIn, HvMessage *m, void *sendMessage) {
  if (msg_isFloat(m,0)) {
    if (msg_isFloat(m,1)) {
      // new ramp
      int n = ctx_millisecondsToSamples(_c, msg_getFloat(m,1));
#if HV_SIMD_AVX
      float x = (((o->n[3] & 0xFFFFFFFFL) >> 32) > 0) ? o->x[7] + (o->m[7]/8.0f) : o->t[7]; // current output value
      float s = (msg_getFloat(m,0) - x) / ((float) n); // slope per sample
      o->n = _mm_set_epi32(n-3, n-2, n-1, n);
      o->x = _mm256_set_ps(x+7.0f*s, x+6.0f*s, x+5.0f*s, x+4.0f*s, x+3.0f*s, x+2.0f*s, x+s, x);
      o->m = _mm256_set1_ps(8.0f*s);
      o->t = _mm256_set1_ps(msg_getFloat(m,0));
#elif HV_SIMD_SSE
      float x = (((o->n[1] & 0xFFFFFFFFL) >> 32) > 0) ? o->x[3] + (o->m[3]/4.0f) : o->t[3]; // current output value
      float s = (msg_getFloat(m,0) - x) / ((float) n); // slope per sample
      o->n = _mm_set_epi32(n-3, n-2, n-1, n);
      o->x = _mm_set_ps(x+3.0f*s, x+2.0f*s, x+s, x);
      o->m = _mm_set1_ps(4.0f*s);
      o->t = _mm_set1_ps(msg_getFloat(m,0));
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
      o->x = (o->n >= 0) ? o->x + o->m : o->t; // new current value
      o->n = n; // new distance to target
      o->m = (msg_getFloat(m,0) - o->x) / ((float) n); // slope per sample
      o->t = msg_getFloat(m,0);
#endif
    } else {
      // Jump to value
#if HV_SIMD_AVX
      o->n = _mm_set1_epi32(0);
      o->x = _mm256_set1_ps(msg_getFloat(m,0));
      o->m = _mm256_set1_ps(0.0f);
      o->t = _mm256_set1_ps(msg_getFloat(m,0));
#elif HV_SIMD_SSE
      o->n = _mm_set1_epi32(0);
      o->x = _mm_set1_ps(msg_getFloat(m,0));
      o->m = _mm_set1_ps(0.0f);
      o->t = _mm_set1_ps(msg_getFloat(m,0));
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
      o->n = 0;
      o->x = msg_getFloat(m,0);
      o->m = 0.0f;
      o->t = msg_getFloat(m,0);
#endif
    }
  } else if (msg_compareSymbol(m,0,"stop")) {
    // Stop line at current position
#if HV_SIMD_AVX
    float x = (((o->n[3] & 0xFFFFFFFFL) >> 32) > 0) ? o->x[7] + (o->m[7]/8.0f) : o->t[7]; // current output value
    o->n = _mm_set1_epi32(0);
    o->x = _mm256_set1_ps(x);
    o->m = _mm256_set1_ps(0.0f);
    o->t = _mm256_set1_ps(x);
#elif HV_SIMD_SSE
    float x = (((o->n[1] & 0xFFFFFFFFL) >> 32) > 0) ? o->x[3] + (o->m[3]/4.0f) : o->t[3]; // current output value
    o->n = _mm_set1_epi32(0);
    o->x = _mm_set1_ps(x);
    o->m = _mm_set1_ps(0.0f);
    o->t = _mm_set1_ps(x);
#elif HV_SIMD_NEON
#error todo implement me
#else // HV_SIMD_NONE
    o->n = 0;
    o->x += o->m;
    o->m = 0.0f;
    o->t = o->x;
#endif
  }
}
