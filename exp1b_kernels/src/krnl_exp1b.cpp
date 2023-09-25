//------------------------------------------------------------------------------
//
// kernel:  exp1b
//
// Purpose: Determine memory bandwidth by reading column-by-column
//

// Update values when needed!!
#define DATA_DIM 4096
//#define DATA_DIM 128

extern "C" {
void krnl_exp1b(const int *in,        // Read-Only Matrix
                int *out) {
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
    for (int i = 0; i < DATA_DIM; i+=16) {
      num00 ^= in[i_outer_index+i_index00+j];
      num01 ^= in[i_outer_index+i_index01+j];
      num02 ^= in[i_outer_index+i_index02+j];
      num03 ^= in[i_outer_index+i_index03+j];
      num04 ^= in[i_outer_index+i_index04+j];
      num05 ^= in[i_outer_index+i_index05+j];
      num06 ^= in[i_outer_index+i_index06+j];
      num07 ^= in[i_outer_index+i_index07+j];
      num08 ^= in[i_outer_index+i_index08+j];
      num09 ^= in[i_outer_index+i_index09+j];
      num10 ^= in[i_outer_index+i_index10+j];
      num11 ^= in[i_outer_index+i_index11+j];
      num12 ^= in[i_outer_index+i_index12+j];
      num13 ^= in[i_outer_index+i_index13+j];
      num14 ^= in[i_outer_index+i_index14+j];
      num15 ^= in[i_outer_index+i_index15+j];

      i_outer_index += i_outer_iter;
    }
    i_outer_index = 0;
  }

  out[0] = num00^num01^num02^num03^num04^num05^num06^num07^num08^num09^num10^num11^num12^num13^num14^num15;
}
}
