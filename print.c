

#include "warmup1.h"

/*********** PRINT UTILITY fuctions *****************/

/** Used to print 1 , 3 and last line  ******************
 
+-----------------+--------------------------+----------------+----------------+ 
 */
 

void PrintLines(){
    int j =0;
    
    for (j=1; j<=80; j++) {
        if(j == 1 || j == 19 || j == 46 || j == 63){
            fprintf(stdout,"+");
        }
        else if(j == 80){
            fprintf(stdout,"+\n");
        }
        else{
            fprintf(stdout,"-");
        }
        
    }
    
}


/** Prints 
 
 |       Date      | Description              |         Amount |        Balance |
 
 */

void PrintStatusLine() {
    
    fprintf(stdout,"|");
    fprintf(stdout,"       Date      |");
    fprintf(stdout," Description              |");
    fprintf(stdout,"         Amount |");
    fprintf(stdout,"        Balance |\n");
    
}


/***** This function is used to add commas whose values > 999 eg. 42,142 */

void AddComma(char amt[],char amt_comma[]){
    int i =0,len=0,count =0;
    
    len = strlen(amt)-1;
    for (i = 11; i>=0; i--) {
        if (len >= 0) {
            amt_comma[i] = amt[len--];
            count++;
        }else{
            amt_comma[i] = ' ';
            
        }
        if(((count-3) % 3)==0 && count-3 > 0 && len+1 >0)
            amt_comma[--i] = ',';
        
        
    }
    amt_comma[12]= '\0';
    
}

/********* This function is used to convert integer number to string buffer ****/

void ftoa(char* buffer , int number){
    int i = number,j=0,count=0,temp_int=0,len=0;
    char temp[AMOUNTMAX] = {};
    while(i>0){
        if(count == 2){
            temp[j] = '.';
            j++;
        }
        temp_int = i%10;
        temp[j++] =temp_int +'0';
        i = i/10;
        
        count++;
        
    }
    temp_int =0;i=0;
    temp_int = len = strlen(temp)-1;
    for (i= 0; i<=temp_int; i++) {
        buffer[i] = temp[len--];
        
    }
    buffer[temp_int+1]='\0';
    
    
}

/************ This function is used to convert string to integer **********/

int myatoi(char str[]){
    int i=0,len = 0;
    len = strlen(str)-2;
    while (*str != '\0') {
        
        if(*str != '.')
            i = i*10 + (*str++ - '0') ;
        else
            str++;
        
    }
    
    return i;
}

/****** Print the details of Date , Description , Amount  and Balance *****/

void PrintDetails(My402List *list){
    My402ListElem *elem = NULL;
    MyDS *print = NULL;
    int j=0;
    char date_format[16] = {};
    int balance = 0,amount =0, pos_balance = 0;
    char amt_comma[20] ={};
    char bal_comma[20] = {};
    char desc_print[DESCWIDTH] = {};
    char buffer[AMOUNTMAX] = {};
    int desc_len =0;
    
    
    
    for (elem = My402ListFirst(list);
         elem!=NULL;
         elem = My402ListNext(list, elem)) {
        
        print = elem->obj;
        
        
        fprintf(stdout,"| ");
        
        FormatDate(elem->obj,date_format);
        
        fprintf(stdout,"%s",date_format);
        fprintf(stdout," | ");
        strncpy(desc_print, print->t_desc, sizeof(desc_print));
        desc_len = strlen(desc_print);
        
        for (j =desc_len; j<=DESCWIDTH-1; j++) {
            desc_print[j] = ' ';
        }
        desc_print[DESCWIDTH] ='\0';
        fprintf(stdout,"%s",desc_print);
        fprintf(stdout," | ");
        
        amount = myatoi(print->t_amount);
        if(amount > 9999999) {
            strncpy(amt_comma,"?,???,???.??",sizeof(amt_comma));
            amt_comma[12]= '\0';
        }
        
        AddComma(print->t_amount,amt_comma);
        
        if(strcmp(print->t_type,"-") == 0)
            fprintf(stdout,"(");
        else
            fprintf(stdout," ");
        
        fprintf(stdout,"%s",amt_comma);
        
        if(strcmp(print->t_type,"-") == 0)
            fprintf(stdout,")");
        else
            fprintf(stdout," ");
        fprintf(stdout," | ");
        
        if(strcmp(print->t_type,"+") == 0){
            balance += myatoi(print->t_amount);
        }
        else{
            balance -= myatoi(print->t_amount);
        }
        
        if(balance<0)
            fprintf(stdout,"(");
        else
            fprintf(stdout," ");
        
        if(balance > 9999999)
        {
            strncpy(bal_comma,"?,???,???.??",sizeof(bal_comma));
            bal_comma[12]= '\0';
        }
        
        
        if(balance < 0)
            pos_balance = abs(balance);
        else
            pos_balance = balance ;
        
        ftoa(buffer,pos_balance);
        
        AddComma(buffer,bal_comma);
        fprintf(stdout,"%s",bal_comma);
        if(balance < 0)
            fprintf(stdout,")");
        else
            fprintf(stdout," ");
        
        fprintf(stdout," |\n");
        
        
    }
    
    
}

/*** Prints ***/

void PrintStatement(My402List *list){
    
    PrintLines();
    PrintStatusLine();
    PrintLines();
    PrintDetails(list);
    PrintLines();
}




