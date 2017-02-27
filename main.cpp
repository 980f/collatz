#include "stdlib.h"
#include "stdio.h"
#include "memory.h"

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
void printbits(unsigned C){
  char zchar=' ';

  for(unsigned picker=32;picker-->0;){
    if(C&(1<<picker)){
      putchar('1');
      zchar='0';
    } else {
      putchar(zchar);
    }
    if((picker&3)==0){
      putchar(':');
    }
  }
}

void analyze(unsigned C){
  printbits(C);
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
  printf("\n");
}

int main(int argc, char *argv[]){
  printf("Number of bits in math: %d\n", 8*sizeof(unsigned));
  int n=0;
  unsigned C=40;
  if(argc>1){
    C=atoi(argv[1]);
    C|=1; //we're supposed to be given an odd value.
  }

  do {
    ++n;
    analyze(C);
    C+=1+(C<<1);
    while(!(C&1)){
      C>>=1;
    }
  } while(C>1);
  analyze(C);//final report
  printf("%d iterations\n",n);
  return n;
}
