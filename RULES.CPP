

/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <string.H>
#include <assert.h>
#include <conio.h>
#include <math.h>

#define EQ ==
#define NE !=
#define GE >=
#define LE <=
#define GT >
#define LT <

#define FALSE 0
#define TRUE 1
#define AND &&
#define OR ||
#define NOT !

#define bitand &
#define bitor |
#define bitxor ^
#define bitnot ~

typedef int_fast8_t I8;
typedef uint_fast8_t U8;
typedef int_fast16_t  I16;
typedef uint_fast16_t U16;
typedef int_fast32_t  I32;
typedef uint_fast32_t U32;
typedef int_fast64_t I64;
typedef uint_fast64_t U64;

typedef uint_fast64_t VAL64;
typedef uint_fast64_t WCX;

typedef struct
  {U32 W[2];
  } LEQUW;
typedef union
  {U64 L;LEQUW V;  
  } LEQLL;

#define SLENX 72
#define XPWX 72
static VAL64 PW2[XPWX];
static I32 iC;
static U8 wC;

#define DCX   8000000
static WCX C[DCX];
#define DRX 72
static char m[DRX][DRX];
static WCX RN[DRX];
static U8   RUD[DRX];
static bool RTU[DRX];
static U8   RTX[DRX];

void newl(void)
{printf("\n");
}

void Dp(char *p)
{printf("%s. \n",p);
}

void inits(void)
{
int v;

/* dont touch PW2 dim */
for(int e=0;e LE 63;e++)
  {
  PW2[e]=1;for(int i=0;i LT e;i++)PW2[e]*=2;;
  }
}

void genrules(int pn)
{
char l[DRX];int dkn,a,b,k;

dkn=pn;assert(pn LE DRX);
printf("Creating the first %d rules. \n",pn);
a=3;b=3;
for(int r=0;r< dkn;r++)
  {
  if(r EQ 0){a=3;b=3;}
  for(int i=0;i<dkn;i++)l[i]='n';
  l[dkn]='f';l[dkn+1]=0;k=dkn-1-r;
  for(int i=a;i<=b;i++)
    {
    if(a EQ (a&i))l[k]='1';else l[k]='x';
    k++;
    }
    l[dkn-1-r]='e';l[dkn+1]=0;strcpy(m[r],l);
    m[0][dkn-1]='e';

    {
    WCX rvn;char ch;
    int cox,uder;

    strcpy(l,m[r]);uder=0;
    for(int b=dkn-1;
      (l[b] EQ '1') AND (b>=0);b--)uder++;
    RUD[r]=uder;rvn=0;cox=0;
    for(int b=dkn;b>=0;b--)
      {
      assert(b LE DRX);ch=l[b];
      if(ch EQ '1')rvn++;
      else if(ch EQ 'x')cox++;
      else if(ch EQ 'e'){rvn++;break;}
      rvn<<=1;
      }
    RN[r]=rvn;RTX[r]=cox;
    printf("%02d [%2d-%2d] %s %04I64X \n"
      ,r,a,b,m[r],rvn);
    }
  a--;if(a<0){a=b;b=2*b+1;}
  }
  {
  for(int r=0;r<DRX;r++)RTU[r]=0;
  for(int r=0;r<DRX;r=2*r+1)RTU[r]=1;
  }
}

void createset(int pn)
{
WCX tmp,rnm,pwm,mit;
I32 lowC,kC;int n;

n=pn;assert(n GE 1);

C[0]=0;C[1]=1;
lowC=2;kC=lowC;wC=1;
printf("Start set:");
printf("C%02d =[%02d*%d] =",1,wC,kC);
for(int i=0;i<kC;i++)
  printf(" %04I64X,",C[i]);
newl();
printf("Apply rules %d to %d \n",wC,n);
for(int k=wC;k<n;k++)
  {
  wC++;pwm=PW2[k];rnm=RN[k];
  printf("Rule %02d: %s %04I64X."
,k,m[k],RN[k]);
  printf("Match: ");
  for(int i=1;i<lowC;i++)
    {
    tmp=C[i];tmp=tmp|pwm;mit=tmp&rnm;
    if(mit NE rnm)continue;
    assert(kC LT DCX);C[kC++]=tmp;
    printf(" %04I64X",tmp);
    }
  newl();lowC=kC;
  }
iC=lowC;
printf("C%02d =[%02d*%d] {",n,wC,iC);
for(int i=0;i<iC;i++)printf("%02I64X,",C[i]);
printf("}\n");

}


void titles(void)
{
Dp("Computes Dedekind sets");
Dp("using binary rules");
Dp("Author: JM Montolio A. 2020");
Dp("  gcc7+MINGW. x64");
Dp("  MIT Licensed ");
Dp("The cardinality of set are OEIS A132581");
Dp("Each rule expand is OEIS A132582");
Dp("See Author works on openthesis.org");
}

void endes(void)
{
Dp("Derived from Author works");
Dp("Contact: JOSMANCOLT@protonmail.com");
Dp("Ref: OEIS Dr.Sloane. 2020");
Dp("Sequences A132581, A132582");
}

void presskey(void)
{
char c;
printf("\r  -- space or leave -- ");
c=getch();
printf("\r                       ");
printf("\r");
if(c NE 32)exit(0);
}

int main(void)
{
int n;

titles();
presskey();
inits();
n=8;
printf("Create one demo set.\n");
genrules(n);
presskey();
createset(n);  
presskey();

endes();
return 1;
}

/************* MINGW BAT *****************
gcc -Wall -march=x86-64 -O2 -o %1.exe %1.c 
*****************************************/


