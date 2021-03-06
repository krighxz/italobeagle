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
 *
 * DO NOT MODIFY. THIS CODE IS MACHINE GENERATED BY THE SECTION6 HEAVY COMPILER.
 */

#ifndef _HEAVYCONTEXT_BEAGLESEQUENCER_H_
#define _HEAVYCONTEXT_BEAGLESEQUENCER_H_

#include "HvBase.h"

#define Context(_x) ((Hv_beagleSequencer *) (_x))

// object includes
#include "ControlSystem.h"
#include "SignalVar.h"
#include "ControlCast.h"
#include "HvTable.h"
#include "SignalTabread.h"
#include "ControlSlice.h"
#include "SignalLine.h"
#include "HeavyMath.h"
#include "ControlBinop.h"
#include "ControlVar.h"
#include "ControlDelay.h"
#include "SignalBiquad.h"
#include "SignalPhasor.h"

typedef struct Hv_beagleSequencer {
  HvBase base;

  // objects
  SignalPhasor sPhasor_lilf8;
  SignalVarf sVarf_QAnql;
  SignalVarf sVarf_YNx0S;
  SignalVarf sVarf_GQlkK;
  SignalTabread sTabread_mhivH;
  SignalVarf sVarf_uWDTi;
  SignalVarf sVarf_uxp6Y;
  SignalTabread sTabread_M74JU;
  SignalVarf sVarf_5qXGc;
  SignalVarf sVarf_q0QEn;
  SignalPhasor sPhasor_Sx4VZ;
  SignalVarf sVarf_xzcF6;
  SignalPhasor sPhasor_vPem0;
  SignalVarf sVarf_Wyaci;
  SignalBiquad_k sBiquad_k_0VbRT;
  SignalLine sLine_JLlzI;
  SignalVarf sVarf_STrlj;
  SignalPhasor sPhasor_otQ4B;
  SignalVarf sVarf_VWGyU;
  SignalVarf sVarf_1Luc2;
  SignalVarf sVarf_9wWH8;
  SignalTabread sTabread_MwVG3;
  SignalVarf sVarf_g0m6j;
  SignalVarf sVarf_2P8UJ;
  SignalTabread sTabread_wW8Qf;
  SignalVarf sVarf_xuwhD;
  SignalVarf sVarf_xRHVO;
  SignalPhasor sPhasor_3McXl;
  SignalVarf sVarf_aYVN6;
  SignalPhasor sPhasor_x0Sjs;
  SignalVarf sVarf_Rdzf0;
  SignalBiquad_k sBiquad_k_o9d4y;
  SignalLine sLine_KLAjq;
  SignalVarf sVarf_a6nq5;
  SignalPhasor sPhasor_qeBQy;
  SignalVarf sVarf_HAJuH;
  SignalVarf sVarf_84HEb;
  SignalVarf sVarf_iLwmQ;
  SignalTabread sTabread_meNCp;
  SignalVarf sVarf_gnGbk;
  SignalVarf sVarf_JFlgK;
  SignalTabread sTabread_Dva00;
  SignalVarf sVarf_G8EFC;
  SignalVarf sVarf_XZIVG;
  SignalPhasor sPhasor_JRyYE;
  SignalVarf sVarf_Vrp1Z;
  SignalPhasor sPhasor_i50Mh;
  SignalVarf sVarf_AGuz5;
  SignalBiquad_k sBiquad_k_4uoNn;
  SignalLine sLine_FaBVL;
  SignalVarf sVarf_x0hPt;
  SignalPhasor sPhasor_CHeID;
  SignalVarf sVarf_Wjqos;
  SignalVarf sVarf_WqUdS;
  SignalVarf sVarf_KSjOC;
  SignalTabread sTabread_Q6mVD;
  SignalVarf sVarf_Sgacq;
  SignalVarf sVarf_G8fTD;
  SignalTabread sTabread_5bM9D;
  SignalVarf sVarf_YnG8s;
  SignalVarf sVarf_XgALR;
  SignalPhasor sPhasor_1jxAg;
  SignalVarf sVarf_gLPIB;
  SignalPhasor sPhasor_g1fhO;
  SignalVarf sVarf_MX5O5;
  SignalBiquad_k sBiquad_k_W3fnL;
  SignalLine sLine_Zhnka;
  SignalVarf sVarf_pZfNq;
  SignalPhasor sPhasor_3B3wv;
  SignalLine sLine_TBr8i;
  SignalVarf sVarf_UAbaZ;
  ControlSlice cSlice_3b7NL;
  ControlSlice cSlice_thH2t;
  ControlBinop cBinop_I3lHZ;
  ControlBinop cBinop_RrJpk;
  ControlBinop cBinop_ty02A;
  ControlBinop cBinop_kMfou;
  ControlBinop cBinop_K11vO;
  ControlVar cVar_2cHVS;
  ControlBinop cBinop_OR0LY;
  ControlVar cVar_W7Dr6;
  ControlBinop cBinop_5meE1;
  ControlDelay cDelay_G3JUc;
  ControlBinop cBinop_PU6QN;
  ControlBinop cBinop_FoLos;
  ControlVar cVar_Lhsvv;
  ControlBinop cBinop_wF1Cm;
  ControlVar cVar_xl6Bb;
  ControlBinop cBinop_3VWLj;
  ControlVar cVar_XTRAT;
  ControlBinop cBinop_WqRlQ;
  ControlBinop cBinop_lw1Ox;
  ControlBinop cBinop_9zpjv;
  ControlVar cVar_1VwXr;
  ControlVar cVar_0SrWC;
  ControlBinop cBinop_MFPaN;
  ControlSlice cSlice_IVBYL;
  ControlSlice cSlice_Kasuc;
  ControlSlice cSlice_MWDv0;
  ControlBinop cBinop_J5UGP;
  ControlVar cVar_cB2S7;
  ControlBinop cBinop_zzwzv;
  ControlVar cVar_tSdiM;
  ControlVar cVar_DAID3;
  ControlBinop cBinop_bmzPw;
  ControlBinop cBinop_K6Z2g;
  ControlBinop cBinop_mCOYe;
  ControlBinop cBinop_d73k0;
  ControlBinop cBinop_svJyr;
  ControlVar cVar_BIaRq;
  ControlVar cVar_UusUX;
  ControlSlice cSlice_1NNks;
  ControlSlice cSlice_SWtnx;
  ControlSlice cSlice_vgovP;
  ControlSlice cSlice_vHbcx;
  ControlSlice cSlice_zdQRB;
  ControlSlice cSlice_aujDD;
  ControlSlice cSlice_7QBdM;
  ControlSlice cSlice_h8qpL;
  ControlSlice cSlice_AHNo0;
  ControlSlice cSlice_v8hYx;
  ControlSlice cSlice_8Mg2z;
  ControlSlice cSlice_0mfXo;
  ControlBinop cBinop_y28I0;
  ControlVar cVar_ACiuq;
  ControlVar cVar_qBDkX;
  ControlDelay cDelay_AOFFN;
  ControlBinop cBinop_KiRgh;
  ControlBinop cBinop_CfnW0;
  ControlVar cVar_Wp3NU;
  ControlBinop cBinop_D0wj0;
  ControlBinop cBinop_jlY0C;
  ControlBinop cBinop_7UcTP;
  ControlVar cVar_mzUZs;
  ControlBinop cBinop_6pFnN;
  ControlBinop cBinop_BojCg;
  ControlDelay cDelay_NYkNZ;
  ControlBinop cBinop_VCDCA;
  ControlBinop cBinop_h0vPw;
  ControlVar cVar_DwFdN;
  ControlBinop cBinop_ZuJE3;
  ControlBinop cBinop_uD0QP;
  ControlVar cVar_cZCG6;
  ControlVar cVar_j1E73;
  ControlSlice cSlice_znkkX;
  ControlSlice cSlice_ZnAsn;
  ControlVar cVar_4a7BU;
  ControlVar cVar_C8P86;
  ControlBinop cBinop_NegX4;
  ControlSlice cSlice_CWova;
  ControlSlice cSlice_Zkf2p;
  ControlBinop cBinop_QwuX7;
  ControlBinop cBinop_bMQQV;
  ControlBinop cBinop_ahTcp;
  ControlBinop cBinop_SBtxs;
  ControlVar cVar_75r4L;
  ControlBinop cBinop_aFRLD;
  ControlBinop cBinop_h78jO;
  ControlBinop cBinop_ljvQA;
  ControlBinop cBinop_7yKAU;
  ControlBinop cBinop_7hHMB;
  ControlBinop cBinop_MIunB;
  ControlBinop cBinop_fYCNK;
  ControlSlice cSlice_t0LLh;
  ControlVar cVar_vOLsi;
  ControlVar cVar_I6AhL;
  ControlVar cVar_rHzdb;
  ControlDelay cDelay_PUzwg;
  ControlVar cVar_zHW8v;
  ControlVar cVar_O45x8;
  ControlVar cVar_u9tOF;
  ControlVar cVar_cYXuz;
  ControlSlice cSlice_AAUcd;
  ControlBinop cBinop_eZOuE;
  ControlBinop cBinop_etiKc;
  ControlBinop cBinop_89iMt;
  ControlBinop cBinop_3EBg2;
  ControlBinop cBinop_xgMNq;
  ControlSlice cSlice_XxcbP;
  ControlSlice cSlice_E3CBm;
  ControlSlice cSlice_jGz3w;
  ControlSlice cSlice_PqrWv;
  ControlSlice cSlice_ftq56;
  ControlSlice cSlice_xYQfX;
  ControlSlice cSlice_mZ7HJ;
  ControlSlice cSlice_NJjtx;
  ControlSlice cSlice_LSESN;
  ControlSlice cSlice_ybv29;
  ControlSlice cSlice_FXfb2;
  ControlSlice cSlice_Rl9p6;
  ControlBinop cBinop_D8JEX;
  ControlVar cVar_TXELp;
  ControlBinop cBinop_9KPMR;
  ControlSlice cSlice_uZIwv;
  ControlBinop cBinop_dxKdK;
  ControlBinop cBinop_LxPrk;
  ControlVar cVar_gziVT;
  ControlSlice cSlice_9gs7I;
  ControlBinop cBinop_4qnB0;
  ControlVar cVar_itjnB;
  ControlDelay cDelay_8Ysky;
  ControlBinop cBinop_33wWn;
  ControlBinop cBinop_2qZeT;
  ControlBinop cBinop_S2eOw;
  ControlVar cVar_K0OLa;
  ControlBinop cBinop_NHTqK;
  ControlBinop cBinop_SFA9g;
  ControlVar cVar_I8cYa;
  ControlVar cVar_4vT8G;
  ControlBinop cBinop_sJgQS;
  ControlBinop cBinop_650eq;
  ControlVar cVar_FJ2mZ;
  ControlBinop cBinop_F7KOr;
  ControlVar cVar_RQEG4;
  ControlSlice cSlice_s9LGt;
  ControlSlice cSlice_hr3ZB;
  ControlBinop cBinop_kzr3N;
  ControlBinop cBinop_06TP1;
  ControlBinop cBinop_hmF2r;
  ControlBinop cBinop_KbjVw;
  ControlVar cVar_CXckv;
  ControlDelay cDelay_ztbsD;
  ControlVar cVar_QLvTS;
  ControlBinop cBinop_5KVwx;
  ControlBinop cBinop_Qh1fy;
  ControlBinop cBinop_CuLWP;
  ControlBinop cBinop_RZTMe;
  ControlBinop cBinop_4VhE6;
  ControlVar cVar_MAvam;
  ControlBinop cBinop_9MH4f;
  ControlBinop cBinop_SKvvD;
  ControlBinop cBinop_91dPG;
  ControlBinop cBinop_QwBuN;
  ControlVar cVar_A1t7B;
  ControlBinop cBinop_Wt3Cv;
  ControlVar cVar_WSEWE;
  ControlSlice cSlice_rVmSM;
  ControlDelay cDelay_IkAA7;
  ControlBinop cBinop_NObUX;
  ControlBinop cBinop_0azdM;
  ControlBinop cBinop_K9R9t;
  ControlVar cVar_RN9zf;
  ControlBinop cBinop_BxHT4;
  ControlVar cVar_PtZka;
  ControlVar cVar_v0uvW;
  ControlBinop cBinop_8BWb6;
  ControlBinop cBinop_yHn5q;
  ControlBinop cBinop_oHJSu;
  ControlBinop cBinop_gF4DV;
  ControlVar cVar_xAB45;
  ControlBinop cBinop_b8OwB;
  ControlVar cVar_blZUD;
  ControlBinop cBinop_YSpZ1;
  ControlSlice cSlice_AcdqA;
  ControlSlice cSlice_V56iB;
  ControlSlice cSlice_0RvCV;
  ControlBinop cBinop_821d3;
  ControlVar cVar_5Gi0S;
  ControlBinop cBinop_oUByw;
  ControlVar cVar_jGiHI;
  ControlBinop cBinop_A0wyW;
  ControlDelay cDelay_Blrh9;
  ControlBinop cBinop_uf2Wh;
  ControlVar cVar_OAzdE;
  ControlSlice cSlice_zHifD;
  HvTable hTable_bMLHk;
  ControlVar cVar_SLW32;
  ControlVar cVar_wYCc2;
  ControlVar cVar_O8nYG;
  ControlSlice cSlice_YkdUt;
  ControlBinop cBinop_076fK;
  ControlVar cVar_duqnZ;
  ControlBinop cBinop_aGVhB;
  ControlVar cVar_OYyhM;
  ControlBinop cBinop_4DtwM;
  ControlBinop cBinop_sPEHx;
  ControlVar cVar_xQKCi;
  ControlBinop cBinop_olcBb;
  ControlBinop cBinop_HB1vb;
  ControlBinop cBinop_VV8Oe;
  ControlBinop cBinop_t5TvE;
  ControlVar cVar_KnJRv;
  ControlBinop cBinop_ZcrJ8;
  ControlDelay cDelay_dR38e;
  ControlBinop cBinop_66xqV;
  ControlVar cVar_RckXD;
  ControlBinop cBinop_0Yvz6;
  ControlSlice cSlice_AFaN3;
  ControlBinop cBinop_MgxqV;
  ControlVar cVar_sWdyK;
  ControlBinop cBinop_PMLPn;
  ControlVar cVar_z9UOu;
  ControlBinop cBinop_iM3sK;
  ControlBinop cBinop_BL8pQ;
  ControlVar cVar_8M7HX;
  ControlVar cVar_6Gk3T;
  ControlSlice cSlice_Ru1HX;
  ControlSlice cSlice_6BEAh;
  ControlSlice cSlice_2O6my;
  ControlBinop cBinop_vHAjS;
  ControlBinop cBinop_hjind;
  ControlSlice cSlice_PQiy9;
  ControlVar cVar_uRWpk;
  ControlVar cVar_BXCVL;
  ControlBinop cBinop_VWt1j;
  ControlBinop cBinop_kV3FB;
  ControlBinop cBinop_4xxSL;
  ControlBinop cBinop_0nD5u;
  ControlBinop cBinop_ifWhX;
  ControlSlice cSlice_HrWNk;
  ControlSlice cSlice_B597P;
  ControlSlice cSlice_7eA3s;
  ControlSlice cSlice_4fO7c;
  ControlSlice cSlice_QsM4t;
  ControlSlice cSlice_IfwGQ;
  ControlSlice cSlice_PiWma;
  ControlSlice cSlice_DWNyu;
  ControlSlice cSlice_kWGKg;
  ControlSlice cSlice_gtdGp;
  ControlSlice cSlice_y0YTL;
  ControlSlice cSlice_HGX0I;
  ControlDelay cDelay_taS1j;
  ControlVar cVar_AYgg4;
  ControlBinop cBinop_732Un;
  ControlBinop cBinop_9DgN3;
  ControlBinop cBinop_RKXuA;
  ControlBinop cBinop_ORKqM;
  ControlBinop cBinop_bR4Mh;
  ControlBinop cBinop_B6OSm;
  ControlBinop cBinop_H1QOU;
  ControlDelay cDelay_rrS7v;
  ControlBinop cBinop_5xV2q;
  ControlVar cVar_bJrFW;
  ControlVar cVar_4tbuE;
  ControlBinop cBinop_RVbn1;
  ControlVar cVar_faBB3;
  ControlSlice cSlice_CcMJB;
  ControlBinop cBinop_wDLQw;
  ControlBinop cBinop_SUDIo;
  ControlBinop cBinop_jtP4w;
  ControlBinop cBinop_nrsY7;
  ControlBinop cBinop_8Ekxj;
  ControlVar cVar_ebB29;
  ControlDelay cDelay_9A6pw;
  ControlBinop cBinop_QYI2F;
  ControlVar cVar_QjJnG;
  ControlBinop cBinop_opdpg;
  ControlBinop cBinop_1euCm;
  ControlBinop cBinop_gDr69;
  ControlVar cVar_MAjMM;
  ControlVar cVar_rrMTi;
  ControlBinop cBinop_Be6nP;
  ControlBinop cBinop_ZvM7s;
  ControlVar cVar_OKv9T;
  ControlBinop cBinop_jjoCt;
  ControlVar cVar_NO5ZF;
  ControlSlice cSlice_iUFkR;
  ControlSlice cSlice_Hk9KE;
  ControlSlice cSlice_l5R09;
  ControlBinop cBinop_4JN1I;
  ControlBinop cBinop_qAe7E;
  ControlBinop cBinop_ujEEC;
  ControlVar cVar_msNQv;
  ControlSlice cSlice_RUjS0;
  ControlVar cVar_0Z6Pg;
  ControlDelay cDelay_3PYLf;
  ControlBinop cBinop_WtJtn;
  ControlBinop cBinop_CNWM3;
  ControlBinop cBinop_lM23f;
  ControlBinop cBinop_W8mwD;
  ControlVar cVar_vcWsr;
  ControlVar cVar_8hLCA;
  ControlSlice cSlice_RHhsD;
  ControlSlice cSlice_r7xPF;
  ControlSlice cSlice_GQmAl;
  ControlSlice cSlice_vonoQ;
  ControlSlice cSlice_IOPRC;
  ControlSlice cSlice_vtRQ5;
  ControlSlice cSlice_gZkzn;
  ControlSlice cSlice_kSsa6;
  ControlSlice cSlice_SSpi9;
  ControlSlice cSlice_MKymo;
  ControlSlice cSlice_FlryU;
  ControlSlice cSlice_o05uN;
  ControlVar cVar_Lp4G7;
  ControlBinop cBinop_w2U3z;
  ControlSlice cSlice_gVlyE;
  ControlVar cVar_ZAcjO;
  ControlVar cVar_R7GV8;
  ControlSlice cSlice_SGnD9;
  ControlSlice cSlice_zBCMc;
  ControlSlice cSlice_6P5oK;
  ControlSlice cSlice_GLZZX;
  ControlSlice cSlice_W7BAx;
  ControlSlice cSlice_OclBP;
  ControlSlice cSlice_hkVvc;
  ControlSlice cSlice_ocqfK;
  ControlSlice cSlice_hQpqH;
  ControlSlice cSlice_pUXxC;
  ControlSlice cSlice_H9vMj;
  ControlSlice cSlice_8jMMm;
  ControlBinop cBinop_37UMW;
  ControlBinop cBinop_leeZQ;
  ControlBinop cBinop_YrH4C;
  ControlBinop cBinop_y3nXm;
  ControlVar cVar_j3NDe;
  ControlVar cVar_Wg9LB;
  ControlSlice cSlice_hBD15;
  ControlBinop cBinop_gKisa;
  ControlBinop cBinop_iNREp;
  ControlBinop cBinop_bZVmq;
  ControlSlice cSlice_lOAEQ;
  ControlVar cVar_5yert;
  ControlBinop cBinop_v76nD;
  ControlBinop cBinop_AX9cA;
  ControlBinop cBinop_5NlgC;
  ControlBinop cBinop_1fcHX;
  ControlVar cVar_wNNCt;
  ControlBinop cBinop_0YuMd;
  ControlBinop cBinop_7oeTe;
  ControlDelay cDelay_b951T;
  ControlBinop cBinop_SJXEo;
  ControlBinop cBinop_X3oon;
  ControlVar cVar_uNzPZ;
  ControlVar cVar_THQgk;
  ControlBinop cBinop_dKEJB;
  ControlVar cVar_KoMPh;
  ControlBinop cBinop_u029G;
  ControlSlice cSlice_OA9Xq;
  ControlVar cVar_HAFgj;
  ControlBinop cBinop_tJdJr;
  ControlVar cVar_g8aev;
  ControlSlice cSlice_vHUKd;
  ControlSlice cSlice_4kHpM;
  ControlBinop cBinop_hILcO;
  ControlBinop cBinop_T3X28;
  ControlBinop cBinop_Bv4Nf;
  ControlBinop cBinop_7Gr06;
  ControlVar cVar_8xzbr;
  ControlBinop cBinop_L5c2i;
  ControlBinop cBinop_2bKbL;
  ControlVar cVar_ooD4i;
  ControlDelay cDelay_uRTio;
  ControlVar cVar_3u7ev;
  ControlVar cVar_10KT1;
  ControlVar cVar_34qne;
  ControlBinop cBinop_bWnG0;
  ControlBinop cBinop_efv8v;
  ControlBinop cBinop_eYfxK;
  ControlBinop cBinop_bdJqi;
  ControlBinop cBinop_Gu3X2;
  ControlBinop cBinop_sYwZx;
  ControlBinop cBinop_3Gcfa;
  ControlBinop cBinop_daRHK;
  ControlVar cVar_Jm6wI;
  ControlBinop cBinop_N6QMY;
  ControlBinop cBinop_BNCDd;
  ControlBinop cBinop_sNcW5;
  ControlBinop cBinop_Sh17q;
  ControlBinop cBinop_A7Y6F;
  ControlVar cVar_OH0yW;
  ControlBinop cBinop_JeEPN;
  ControlDelay cDelay_8IsTO;
  ControlBinop cBinop_s6asQ;
  ControlBinop cBinop_V6Vr2;
  ControlVar cVar_4TGwP;
  ControlBinop cBinop_RUQGr;
  ControlBinop cBinop_T2Qrz;
  ControlBinop cBinop_JC3EK;
  ControlBinop cBinop_OqShv;
  ControlVar cVar_Tf8ru;
  ControlVar cVar_F21OA;
  ControlVar cVar_6PPGX;
  ControlSlice cSlice_aYHD8;
  ControlVar cVar_lKXKq;
  ControlSlice cSlice_L7uGl;
  ControlSlice cSlice_kTBM8;
  ControlSlice cSlice_8ihNZ;
  ControlBinop cBinop_Br7rZ;
  ControlVar cVar_GazKu;
  ControlBinop cBinop_YKIl7;
  ControlVar cVar_i87kk;
  ControlDelay cDelay_3jV8r;
} Hv_beagleSequencer;

#endif // _HEAVYCONTEXT_BEAGLESEQUENCER_H_
