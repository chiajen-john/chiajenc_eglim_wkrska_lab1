//------------------------------------------------------------------------------
//
// kernel:  exp2b
//
// Purpose: Determine memory bandwidth by writing column-by-column
//

//#define DATA_DIM 4096
#define DATA_DIM 128

extern "C" {

int xorshift(int num) {
  num ^= num << 13;
  num ^= num >> 17;
  num ^= num << 5;
  return num;
}

void krnl_exp2b(float *out) {

  int num00 = 852129405;
  int num01 = 1297230771;
  int num02 = 721781807;
  int num03 = 701130504;
  int num04 = -1877593432;
  int num05 = -686465853;
  int num06 = 1758295511;
  int num07 = -1973247524;
  int num08 = 933706032;
  int num09 = 2056139590;
  int num10 = -1538942814;
  int num11 = 773576297;
  int num12 = 1336751546;
  int num13 = -327623126;
  int num14 = 192869803;
  int num15 = -2046359899;

  int i_outer_iter = 65536;
  int i_outer_index = 0;
  int i_index00 = 0;
  int i_index01 = 4096;
  int i_index02 = 8192;
  int i_index03 = 12288;
  int i_index04 = 16384;
  int i_index05 = 20480;
  int i_index06 = 24576;
  int i_index07 = 28672;
  int i_index08 = 32768;
  int i_index09 = 36864;
  int i_index10 = 40960;
  int i_index11 = 45056;
  int i_index12 = 49152;
  int i_index13 = 53248;
  int i_index14 = 57344;
  int i_index15 = 61440;

  for (int j = 0; j < DATA_DIM; j++) {
    for (int i = 0; i < DATA_DIM; i += 16) {
      out[i_outer_index+i_index00+j] = num00;
      out[i_outer_index+i_index01+j] = num01;
      out[i_outer_index+i_index02+j] = num02;
      out[i_outer_index+i_index03+j] = num03;
      out[i_outer_index+i_index04+j] = num04;
      out[i_outer_index+i_index05+j] = num05;
      out[i_outer_index+i_index06+j] = num06;
      out[i_outer_index+i_index07+j] = num07;
      out[i_outer_index+i_index08+j] = num08;
      out[i_outer_index+i_index09+j] = num09;
      out[i_outer_index+i_index10+j] = num10;
      out[i_outer_index+i_index11+j] = num11;
      out[i_outer_index+i_index12+j] = num12;
      out[i_outer_index+i_index13+j] = num13;
      out[i_outer_index+i_index14+j] = num14;
      out[i_outer_index+i_index15+j] = num15;

      i_outer_index += i_outer_iter;

      num00 = xorshift(num00);
      num01 = xorshift(num01);
      num02 = xorshift(num02);
      num03 = xorshift(num03);
      num04 = xorshift(num04);
      num05 = xorshift(num05);
      num06 = xorshift(num06);
      num07 = xorshift(num07);
      num08 = xorshift(num08);
      num09 = xorshift(num09);
      num10 = xorshift(num10);
      num11 = xorshift(num11);
      num12 = xorshift(num12);
      num13 = xorshift(num13);
      num14 = xorshift(num14);
      num15 = xorshift(num15);
    }
    i_outer_index = 0;
  }
}
}
