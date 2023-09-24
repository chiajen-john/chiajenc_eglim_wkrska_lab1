//------------------------------------------------------------------------------
//
// kernel:  exp2a
//
// Purpose: Determine memory bandwidth by writing row-by-row
//

//#define DATA_DIM 4096
#define DATA_DIM 128

extern "C" {

//int xorshift(int num) {
//  num ^= num << 13;
//  num ^= num >> 17;
//  num ^= num << 5;
//  return num;
//}

void krnl_exp2a(float *out) {

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

  int i_index = 0;

  for (int i = 0; i < DATA_DIM; i++) {
    for (int j = 0; j < DATA_DIM; j += 16) {
      out[i_index+j] = num00;
      out[i_index+j+1] = num01;
      out[i_index+j+2] = num02;
      out[i_index+j+3] = num03;
      out[i_index+j+4] = num04;
      out[i_index+j+5] = num05;
      out[i_index+j+6] = num06;
      out[i_index+j+7] = num07;
      out[i_index+j+8] = num08;
      out[i_index+j+9] = num09;
      out[i_index+j+10] = num10;
      out[i_index+j+11] = num11;
      out[i_index+j+12] = num12;
      out[i_index+j+13] = num13;
      out[i_index+j+14] = num14;
      out[i_index+j+15] = num15;

      num00 ^= num00 << 13;
      num00 ^= num00 >> 17;
      num00 ^= num00 << 5;
      num01 ^= num01 << 13;
      num01 ^= num01 >> 17;
      num01 ^= num01 << 5;
      num02 ^= num02 << 13;
      num02 ^= num02 >> 17;
      num02 ^= num02 << 5;
      num03 ^= num03 << 13;
      num03 ^= num03 >> 17;
      num03 ^= num03 << 5;
      num04 ^= num04 << 13;
      num04 ^= num04 >> 17;
      num04 ^= num04 << 5;
      num05 ^= num05 << 13;
      num05 ^= num05 >> 17;
      num05 ^= num05 << 5;
      num06 ^= num06 << 13;
      num06 ^= num06 >> 17;
      num06 ^= num06 << 5;
      num07 ^= num07 << 13;
      num07 ^= num07 >> 17;
      num07 ^= num07 << 5;
      num08 ^= num08 << 13;
      num08 ^= num08 >> 17;
      num08 ^= num08 << 5;
      num09 ^= num09 << 13;
      num09 ^= num09 >> 17;
      num09 ^= num09 << 5;
      num10 ^= num10 << 13;
      num10 ^= num10 >> 17;
      num10 ^= num10 << 5;
      num11 ^= num11 << 13;
      num11 ^= num11 >> 17;
      num11 ^= num11 << 5;
      num12 ^= num12 << 13;
      num12 ^= num12 >> 17;
      num12 ^= num12 << 5;
      num13 ^= num13 << 13;
      num13 ^= num13 >> 17;
      num13 ^= num13 << 5;
      num14 ^= num14 << 13;
      num14 ^= num14 >> 17;
      num14 ^= num14 << 5;
      num15 ^= num15 << 13;
      num15 ^= num15 >> 17;
      num15 ^= num15 << 5;

      //num00 = xorshift(num00);
      //num01 = xorshift(num01);
      //num02 = xorshift(num02);
      //num03 = xorshift(num03);
      //num04 = xorshift(num04);
      //num05 = xorshift(num05);
      //num06 = xorshift(num06);
      //num07 = xorshift(num07);
      //num08 = xorshift(num08);
      //num09 = xorshift(num09);
      //num10 = xorshift(num10);
      //num11 = xorshift(num11);
      //num12 = xorshift(num12);
      //num13 = xorshift(num13);
      //num14 = xorshift(num14);
      //num15 = xorshift(num15);
    }
    i_index += DATA_DIM; // Using this counter to avoid multiplication in index calculatation
  }
}
}
