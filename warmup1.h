

#ifndef _WARMUP1_H_
#define _WARMUP1_H_

#include "cs402.h"
#include "my402list.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"


#define TYPEMAX 2
#define DATEMAX 16
#define AMOUNTMAX 15
#define DESCMAX 24
#define MAXBUFSIZE 1026

#define DATEWIDTH 15
#define DESCWIDTH 24
#define AMTWIDTH 14
#define BALWIDTH 16


enum Transaction {
    T_TYPE,
    T_TIME,
    T_AMOUNT,
    T_DESC
};

enum Width {
    W_DATE = 15,
    W_DESC = 24,
    W_AMOUNT = 14,
    W_BALANCE = 14
};

/**** Structure for storing the transaction information ******/

typedef struct StoreTransactionData{
    char t_type[TYPEMAX];
    char t_date[DATEMAX];
    char t_amount[AMOUNTMAX];
    char t_desc[DESCMAX];
} MyDS;

/***** Function definations ******/

int Validate(char*,int);
void InserstionSort(My402List*,void *obj);
void StoreNewData(char **, My402List *);
int ReadInput(FILE*,My402List*);
void FormatDate(void*,char*);
void PrintLines();
void PrintStatusLine();
void PrintDetails(My402List*);
void PrintStatement(My402List*);
int myatoi(char str[]);
void AddComma(char amt[],char amt_comma[]);
void ftoa(char*  , int );

#endif /*_WARMUP1_H_*/
