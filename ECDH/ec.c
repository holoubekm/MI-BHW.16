#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "poly.h"
#include "ec.h"


byte* prime;
byte* nprime;
byte* r;
byte* rInv;
byte* rSquare;
byte* num_three;
byte* num_three_monty;
byte* num_two;
byte* num_one;
byte* num_zero;

byte* ECa;
byte* ECb;

byte* out;
byte* tmp1;
byte* tmp2;
byte* tmp3;
byte* tmp4;
byte* tmp5;
byte* tmp6;
byte* tmp7;
byte* tmp8;

void ECalloc() {
  prime = (byte*)malloc(BYTES_CNT);
  nprime = (byte*)malloc(BYTES_CNT);
  r = (byte*)malloc(BYTES_CNT);
  rInv = (byte*)malloc(BYTES_CNT);
  rSquare = (byte*)malloc(BYTES_CNT);
  num_three = (byte*)malloc(BYTES_CNT);
  num_three_monty = (byte*)malloc(BYTES_CNT);
  num_two = (byte*)malloc(BYTES_CNT);
  num_one = (byte*)malloc(BYTES_CNT);
  num_zero = (byte*)malloc(BYTES_CNT);

  ECa = (byte*)malloc(BYTES_CNT);
  ECb = (byte*)malloc(BYTES_CNT);
  
  out = (byte*)malloc(BYTES_CNT);
  tmp1 = (byte*)malloc(BYTES_CNT);
  tmp2 = (byte*)malloc(BYTES_CNT);
  tmp3 = (byte*)malloc(BYTES_CNT);
  tmp4 = (byte*)malloc(BYTES_CNT);
  tmp5 = (byte*)malloc(BYTES_CNT);
  tmp6 = (byte*)malloc(BYTES_CNT);
  tmp7 = (byte*)malloc(BYTES_CNT);
  tmp8 = (byte*)malloc(BYTES_CNT);
}

void ECinit() {
  zero(num_zero);
  zero(num_one);
  *num_one = 1;
  zero(num_two);
  *num_two = 2;
  zero(num_three);
  *num_three = 3;
  zero(num_three_monty);
  zero(out);
  zero(tmp1);
  zero(tmp2);
  zero(tmp3);
  zero(out);

  zero(prime);
  // *prime = 13;
  prime[9] = 0x62;
  prime[8] = 0xCE;
  prime[7] = 0x51;
  prime[6] = 0x77;
  prime[5] = 0x41;
  prime[4] = 0x2A;
  prime[3] = 0xCA;
  prime[2] = 0x89;
  prime[1] = 0x9C;
  prime[0] = 0xF5;

  copy(nprime, prime);
  neg(nprime);

  zero(r);
  zero(rInv);
  zero(rSquare);

  zero(ECa);
  // *ECa = 5;
  ECa[9] = 0x39;
  ECa[8] = 0xC9;
  ECa[7] = 0x5E;
  ECa[6] = 0x6D;
  ECa[5] = 0xDD;
  ECa[4] = 0xB1;
  ECa[3] = 0xBC;
  ECa[2] = 0x45;
  ECa[1] = 0x73;
  ECa[0] = 0x3C;

  zero(ECb);
  // *ECb = 4;
  ECb[9] = 0x1F;
  ECb[8] = 0x16;
  ECb[7] = 0xD8;
  ECb[6] = 0x80;
  ECb[5] = 0xE8;
  ECb[4] = 0x9D;
  ECb[3] = 0x5A;
  ECb[2] = 0x1C;
  ECb[1] = 0x0E;
  ECb[0] = 0xD1;
}

void ECdestroy() {
  free(prime);
  free(nprime);
  free(r);
  free(rInv);
  free(rSquare);
  free(num_three);
  free(num_three_monty);
  free(num_two);
  free(num_one);
  free(num_zero);
  free(ECa);
  free(ECb);
  free(out);
  free(tmp1);
  free(tmp2);
  free(tmp3);
  free(tmp4);
  free(tmp5);
  free(tmp6);
  free(tmp7);
  free(tmp8);
}


void ECSquareAndMultiply(byte* rx, byte* ry, byte* px, byte* py, byte* exp) {
  byte* tmpExp = tmp4;
  byte* baseXa = tmp5;
  byte* baseYa = tmp6;
  byte* baseXb = tmp5;
  byte* baseYb = tmp6;
  copy(tmpExp, exp);
  copy(baseXa, px);
  copy(baseYa, py);
  zero(rx);
  zero(ry);
  while(cmp(tmpExp, num_zero) > 0) {
    if(getbit(tmpExp, 0))
      ECaddPoint(rx, ry, rx, ry, baseXa, baseYa);
    ECaddPoint(baseXb, baseYb, baseXa, baseYa, baseXa, baseYa);
    shiftr(tmpExp);
  }
}

int ECcmp(byte* px, byte* py, byte* qx, byte* qy) {
  if(cmp(px, qx) == 0 && cmp(py, qy) == 0)
    return 0;
  return 1;
}

void ECneg(byte* rx, byte* ry) {
  if(cmp(ry, num_zero) != 0)
    sub(ry, prime, ry);
}

void ECalpha(byte* out, byte* px, byte* py, byte* qx, byte* qy) {
  if(ECcmp(px, py, qx, qy) == 0) {
    mul(tmp1, qx, qx);
    mul(tmp2, tmp1, num_three);
    addMod(tmp1, tmp2, ECa);
    addMod(tmp2, qy, qy);
    inv(tmp3, tmp2);
    mul(out, tmp1, tmp3);
  } else {
    subMod(tmp1, py, qy);
    subMod(tmp2, px, qx);
    inv(tmp3, tmp2);
    mul(out, tmp1, tmp3);
  }
}

void ECalphaMonty(byte* out, byte* px, byte* py, byte* qx, byte* qy) {
  if(ECcmp(px, py, qx, qy) == 0) {
    mulMonty(tmp1, qx, qx);
    mulMonty(tmp2, tmp1, num_three_monty);
    addMod(tmp1, tmp2, ECa);
    addMod(tmp2, qy, qy);
    invMonty(tmp3, tmp2);
    mulMonty(out, tmp1, tmp3);
  } else {
    subMod(tmp1, py, qy);
    subMod(tmp2, px, qx);
    invMonty(tmp3, tmp2);
    mulMonty(out, tmp1, tmp3);
  }
}

void ECaddPoint(byte* rx, byte* ry, byte* px, byte* py, byte* qx, byte* qy) {
  if(cmp(px, qx) == 0 && (cmp(py, qy) != 0 || (cmp(py, num_zero) == 0 && cmp(qy, num_zero) == 0))) {
    copy(rx, num_zero);
    copy(ry, num_zero);
    return;
  }

  if(ECcmp(px, py, num_zero, num_zero) == 0) {
    copy(rx, qx);
    copy(ry, qy);
    return;
  }

  if(ECcmp(qx, qy, num_zero, num_zero) == 0) {
    copy(rx, px);
    copy(ry, py);
    return;
  }

  //Small tuneup to make overlapping pointers great again!
  ECalpha(out, px, py, qx, qy);
  mul(tmp1, out, out);
  subMod(tmp2, tmp1, px);
  subMod(tmp3, tmp2, qx);

  subMod(tmp2, qx, tmp3);
  mul(tmp1, tmp2, out);
  subMod(ry, tmp1, qy);
  copy(rx, tmp3);
}

void ECaddPointMonty(byte* rx, byte* ry, byte* px, byte* py, byte* qx, byte* qy) {
  if(cmp(px, qx) == 0 && (cmp(py, qy) != 0 || (cmp(py, num_zero) == 0 && cmp(qy, num_zero) == 0))) {
    copy(rx, num_zero);
    copy(ry, num_zero);
    return;
  }

  if(ECcmp(px, py, num_zero, num_zero) == 0) {
    copy(rx, qx);
    copy(ry, qy);
    return;
  }

  if(ECcmp(qx, qy, num_zero, num_zero) == 0) {
    copy(rx, px);
    copy(ry, py);
    return;
  }

  ECalphaMonty(tmp2, px, py, qx, qy);
  toMonty(out, tmp2);
  mulMonty(tmp1, out, out);
  subMod(rx, tmp1, px);
  subMod(rx, rx, qx);

  subMod(tmp2, qx, rx);
  mulMonty(ry, tmp2, out);
  subMod(ry, ry, qy);
}

void setup() {
  ECalloc();
  ECinit();
  
  printf("Elliptic curve over GF(p)\n");
}

void printSer(byte* in) {
  for(uint i = 1; i <= BYTES_CNT; i++) {
    printf("%02x", in[BYTES_CNT - i]);
    printf(" ");
   }
}

void readSer(byte* out) {
  byte val, cur, state = 0;
  uint i = 1;
  while(i <= BYTES_CNT) {
    scanf("%c", &val);
    if(isalnum(val)) {
      if(val >= '0' && val <= '9') {
        if(!state) {
          cur = val - '0';
          state = 1;
        } else {
          cur <<= 4;
          out[BYTES_CNT - i++] = cur | (val - '0');
          state = 0;
        }
      } else if((val >= 'A'&& val <= 'Z') || (val >= 'a'&& val <= 'z')) {
        if(!state) {
          cur = val - '7';
          state = 1;
        } else {
          cur <<= 4;
          out[BYTES_CNT - i++] = cur | (val - '7');
          state = 0;
        }
      }
    }
  }
}

int main() {
  setup();
  toMonty(num_three_monty, num_three);

  printf("prime: ");
  printSer(prime);
  printf("\nEC  a: ");
  printSer(ECa);
  printf("\nEC  b: ");
  printSer(ECb);
  printf("\n");
  
  byte* ECpx = (byte*)malloc(BYTES_CNT);
  byte* ECpy = (byte*)malloc(BYTES_CNT);
  byte* ECax = (byte*)malloc(BYTES_CNT);
  byte* ECay = (byte*)malloc(BYTES_CNT);
  byte* ECbx = (byte*)malloc(BYTES_CNT);
  byte* ECby = (byte*)malloc(BYTES_CNT);
  byte* ECqx = (byte*)malloc(BYTES_CNT);
  byte* ECqy = (byte*)malloc(BYTES_CNT);
  byte* ka  = (byte*)malloc(BYTES_CNT);

  ECpx[9] = 0x31;
  ECpx[8] = 0x5D;
  ECpx[7] = 0x4B;
  ECpx[6] = 0x20;
  ECpx[5] = 0x1C;
  ECpx[4] = 0x20;
  ECpx[3] = 0x84;
  ECpx[2] = 0x75;
  ECpx[1] = 0x05;
  ECpx[0] = 0x7D;

  ECpy[9] = 0x03;
  ECpy[8] = 0x5F;
  ECpy[7] = 0x3D;
  ECpy[6] = 0xF5;
  ECpy[5] = 0xAB;
  ECpy[4] = 0x37;
  ECpy[3] = 0x02;
  ECpy[2] = 0x52;
  ECpy[1] = 0x45;
  ECpy[0] = 0x0A;

  zero(ka);
  for(uint i = 0; i < BYTES_CNT; i++)
    ka[i] = (byte)(random());

  //zero(ka);
  //ka[0] = 0x02;
  
  printf("\n\nGoing to make the EC great again!\nPx: ");
  printSer(ECpx);
  printf("\nPy: ");
  printSer(ECpy);
  printf("\nka: ");
  printSer(ka);

  zero(ECax);
  zero(ECay);
  ECSquareAndMultiply(ECax, ECay, ECpx, ECpy, ka);
  printf("\n(ka*P).x = Ax: ");
  printSer(ECax);
  printf("\n(ka*P).y = Ay: ");
  printSer(ECay);

  zero(ECbx);
  zero(ECby);
  printf("\nPlease send values of (kb * P) == B\n");
  printf("\nFormat: 10 bytes from higher to lower\n");
  readSer(ECbx);
  printSer(ECbx);
  printf("Bx OK\n");
  readSer(ECby);
  printSer(ECby);
  printf("By OK\n");\
  zero(ECqx);
  zero(ECqy);
  ECSquareAndMultiply(ECqx, ECqy, ECbx, ECby, ka);
  printf("Q = ka * B\n");
  printf("\nDone:\nQx: ");
  printSer(ECqx);
  printf("\nQy: ");
  printSer(ECqy);
  printf("\n\nDeallocating...\n");  

  ECdestroy();

  free(ECax);
  free(ECay);
  free(ECbx);
  free(ECby);
  free(ECpx);
  free(ECpy);
  free(ECqx);
  free(ECqy);
  free(ka);

  return 0;
}
