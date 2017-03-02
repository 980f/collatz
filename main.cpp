#include "stdlib.h"
#include "stdio.h"
#include "memory.h"
#include "cheaptricks.h"

#define HISTO 0

#if HISTO
//using 32 bit integers for first pass:
unsigned Ones[32];
unsigned Zeroes[32];


void dumphisto(unsigned (&array)[32]){
  printf(" :");
  unsigned limit=32;
  while(limit-->0){
    if(array[limit]>0){
      break;
    }
  }
  for(unsigned index=1;index<=limit;++index){//zeroth element is irrelevant, it exists for convenience in indexing.
    printf("%2d ",array[index]);
  }

}

#endif
int printbits(unsigned C){
  bool blanking=true;
  int msb=-1;//horribly illegal value

  for(unsigned picker=32;picker-->0;){
    if(C&(1<<picker)){
      putchar('1');
      if(flagged(blanking)){
        msb=1+picker;
      }
    } else {
      putchar(blanking?' ':'0');
    }
    if((picker&3)==0){
      putchar(':');
    }
  }
  return msb;
}

int analyze(unsigned C){
  int bits=printbits(C);
#if HISTO
  memset(Ones,0,sizeof(Ones));
  memset(Zeroes,0,sizeof(Ones));
  unsigned run=0;
  do {
  while(C&1){
    ++run;
    C>>=1;
  }
  ++Ones[run];
  run=0;
  while(C && !(C&1)){
    ++run;
    C>>=1;
  }
  ++Zeroes[run];
  run=0;
  } while(C);
  dumphisto(Ones);
  dumphisto(Zeroes);
#endif
  printf("\t%d bits\n",bits);
  return bits;
}

int collatzIterate(unsigned C){
  unsigned n = 0;//number of iterations.
  printf("%d\t",C);
  do {
    ++n;
    int bits=analyze(C);
    C+=1+(C<<1);
    int trailers=0;
    while(!(C&1)){
      ++trailers;
      C>>=1;
    }
    printf("shift %d\t",trailers);
  } while(C>1);
  analyze(C);//final report
  printf("%d iterations\n",n);
  return n;
}

int main(int argc, char *argv[]){
  printf("Number of bits in math: %lu\n", 8*sizeof(unsigned));

  unsigned C=(argc>1)?atoi(argv[1]):40;
  C|=1; //we're supposed to be given an odd value.

  return collatzIterate(C);
}
