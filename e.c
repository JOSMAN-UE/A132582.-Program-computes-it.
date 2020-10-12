
/********************************************
OEIS A132582. 
(C) J.M. Montolio Aranda. 2020. Spain-UE.
The Function E(n). Using rules. Without sets.
Related to author works.
********************************************/

#pragma pack(16)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.H>

typedef int_fast64_t  BNUM;
typedef uint_fast64_t  LARGENUM;

#define EQ ==
#define NE !=
#define GE >=
#define LE <=
#define GT >
#define LT <
#define AND &&
#define OR ||
#define NOT !
#define bitor |
#define bitand &
#define bitxor ^
#define bitnot ~

/****** LIMIT WIDE ****************/
#define XWIDE 64  /* 64 128 */
#define WDIM (XWIDE+4)  /* 80 129 */
/**********************************/
#define STRSZ 90   /* string **/
/**********************************/


#define ATALI __attribute__((aligned))
#pragma pack(16)

static LARGENUM TABPOW2[WDIM] ATALI ; /* table */
static LARGENUM RULENUM[WDIM] ATALI ;  /* rule */
static int  QRIGHT1[WDIM] ATALI ;     /* Ones right */
static bool RALL1[WDIM] ATALI ;     /* All ones */

#pragma pack(16)
static void genrules(const int pn)
{
const int PARAMNN=pn;
const int lasr=pn-1;
int AA,BB;
char NRULES[WDIM][WDIM],linrule[WDIM];
LARGENUM BINRULE;

/** AA,BB: Algorithm gen rules ***/
AA=3;BB=3;
/****** r is rule number **/
for(int r=0;r LT PARAMNN;r++)
  {
  int k;
  for(int i=0;i LT PARAMNN;i++)linrule[i]='n';
  linrule[PARAMNN]='f';linrule[PARAMNN+1]=0;
  k=PARAMNN-1-r;
  for(int i=AA;i LE BB;i++)
    {
    if(AA EQ (AA bitand i))linrule[k]='1';
    else linrule[k]='x';
    k++;
    }
  linrule[PARAMNN-1-r]='e';
  linrule[PARAMNN+1]=0;

/** rule text form ***/
  strcpy(NRULES[r],linrule);

/***  next AA,BB ****/
  AA--;if(AA LT 0){AA=BB;BB=2*BB+1;}
  }

/*** last detail ***/
NRULES[0][PARAMNN-1]='e';

/** rule with all ones **/
for(int r=0;r LT XWIDE;r++)RALL1[r]=0;
for(int r=0;r LT XWIDE;r=2*r+1)RALL1[r]=1;

/** fill two arrays ***/
for(int r=0;r LT PARAMNN;r++)
  {
  int rightones;

  strcpy(linrule,NRULES[r]);

/*** right number of consecutive ones ***/ 
  rightones=0;
  for(
    int b=PARAMNN-1;
    (linrule[b] EQ '1') AND (b GE 0);
    b--)rightones++;
  QRIGHT1[r]=rightones;BINRULE=0;

/** rule binary form */
  for(int b=PARAMNN;b GE 0;b--)
    {
    char CHR=linrule[b];
    if(CHR EQ '1')BINRULE++;
    else if(CHR EQ 'e'){BINRULE++;break;}
    BINRULE<<=1;
    }
  RULENUM[r]=BINRULE;
  }

/******* print rules ***********
 ... for(int r=0;r LT pn;r++) 
*******************************/
  printf("newrule %4d: UD%02d TU%1d RN:%I64X \n"
  ,lasr,QRIGHT1[lasr],RALL1[lasr],RULENUM[lasr]);
}


static BNUM E(const int param)
__attribute__((pure))
__attribute__((aligned))
__attribute__((hot));
static BNUM E(const int param)
{
LARGENUM xstart,xend,xstep; /* main for **/
BNUM expan;  /* E value **/
const int mm=param;  
const int minus=param-1;

/*** main for values **********************/
if(RALL1[minus])
  {
  xstart=TABPOW2[mm]-1;
  xend  =xend;
  xstep=2;
  printf("Rule all ones. \n");
  if(mm EQ 1)return 2; /* Some definition */
  else return +1; /** Always **/
  }
else
  {
  xstart=TABPOW2[minus]+1;
  xend  =TABPOW2[mm]-1;
  xstep=TABPOW2[QRIGHT1[minus]];
  while((xstart%xstep) NE (xstep-1))xstart+=2;
  }

/*** E value ****************/
expan=0;

printf("xstart %I64d \n",xstart);
printf("xend   %I64d \n",xend);
printf("xstep  %I64d rules 2..%d \n",xstep,minus);

/***** main for *********************************/
for(LARGENUM can=xstart;can LE xend;can+=xstep)
  {

/*** this for skips many values ********/
  for(int r=minus;r GT 1;r--)
    {
/** power2, rulebinary ************/
    const LARGENUM TPr=TABPOW2[r];
    const LARGENUM RNr=RULENUM[r];
/** main for logic *****************************/
    const LARGENUM ban=(can bitand TPr);
    const bool bb=(ban NE 0);
    if(bb){can |= RNr;}
/**************************************/
    }

/********* values not skipped are counted **/
  expan++;
  }
return expan;
}

int main(void)
{
BNUM EVAL,ESUM;

/** fill table pow 2 **********/
for(int e=0;e LE XWIDE;e++)
  {
  LARGENUM r,p;
  r=1;p=(r<<e);TABPOW2[e]=p;
  }

ESUM=0; /*** The F() value. ****/
for(int n=1;n LE XWIDE;n++)
  {
  printf("==== n %04d ============== \n",n);
  genrules(n);
  EVAL=E(n);ESUM+=EVAL;
  printf("E(%d)= %I64d. F(%d)= %I64d \n"
    ,n,EVAL,n,ESUM);
  }
return +1;
}

