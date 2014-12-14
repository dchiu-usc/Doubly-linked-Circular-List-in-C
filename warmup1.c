/******** author: lavish singal , lsingal@usc.edu ***********/

#ifndef _WARMUP1_C_
#define _WARMUP1_C_

#include "warmup1.h"
#include <sys/stat.h>


/* Files depended on 
 1) print.c
 2) sort.c
 3) my402list.c
 4) warmup1.h
 */

/***** Formats the date format in  WWW MMM DD YYYY format *****/

void FormatDate(void *obj,char *date_format){
    
    MyDS *date = NULL;
    char buf[26] = {};
    time_t trans_time;
    int i = 0;
    
    date = (MyDS*)obj;
    trans_time = (time_t)atol((date->t_date));
    
    strncpy(buf,ctime(&(trans_time)) , sizeof(buf));
    
    for(i =0 ; i<15;i++)
        if(i < 11)
            date_format[i] = buf[i];
        else
            date_format[i] = buf[i+9];
    date_format[15] = '\0';
    
    
}

/****** Validate all the values contained in the file and returns exceptions ****/

int Validate(char *data_ptr,int i){
    int set = 0, date_int =0,len=0;
    time_t current_time =0;
    char *temp = NULL,*temp2=NULL;
    
    switch (i) {
        case T_TYPE:
            if (strcmp(data_ptr,"+") == 0 || strcmp(data_ptr,"-") == 0) {
                set = 1;
            }
            else{
                fprintf(stderr,"Invalid Transaction Type\n");
                exit(1);
            }
            break;
        case T_TIME:
            current_time = time(0);
            date_int = atoi(data_ptr);
            
            if (strlen(data_ptr) >= 11) {
                fprintf(stderr,"Invalid TimeStamp..Greater than 10\n");
                exit(1);
            }
            if(date_int >=0 && date_int<=current_time){
                set = 1;
            }
            else{
                fprintf(stderr,"Timestamp exceeds currect time!\n");
                exit(1);
            }
            break;
        case T_AMOUNT:
            temp = data_ptr;
            date_int = atoi(data_ptr);
            temp2 = strchr(data_ptr, '.');
            
            if(temp2 == NULL){
                fprintf(stderr,"No decimal digit found\n");
                exit(1);
            }
            
            while(*temp++ != '.')
                len++;
    
            if(len > 7){
                fprintf(stderr,"Reached maximum Transaction Amount >10 Million\n");
                exit(1);
            }
            else if(strlen(temp) != 2){
                fprintf(stderr,"Must contain 2 digits after period\n");
                exit(1);
            }
            else if(date_int < 0){
                fprintf(stderr,"transaction amount should be positive\n");
                exit(1);
            }
            else{
                set = 1;
            }
            
            break;
        case T_DESC:
            if(strlen(data_ptr) <= 0){
                fprintf(stderr,"Desc should not be empty\n");
                exit(1);
            }
            else{
                set = 1;
            }
            break;
            
        default:
            fprintf(stderr,"Too many fields!!\n");
            exit(1);
            break;
    }
    
    return set;
    
}

/****** Store the Date after validation is complete ********/

void StoreNewData(char *s_data[], My402List *list){
    MyDS *store = NULL;
    
    //memory allocated .. where to free this?????????? when free the obj
    store = (MyDS*)malloc(sizeof(MyDS));
    memset(store, 0, sizeof(MyDS));
    
    strncpy(store->t_type, s_data[T_TYPE],sizeof(store->t_type));
    strncpy(store->t_date,s_data[T_TIME],sizeof(store->t_date));
    strncpy(store->t_amount,s_data[T_AMOUNT],sizeof(store->t_amount));
    strncpy(store->t_desc,s_data[T_DESC],sizeof(store->t_desc));
    
    InserstionSort(list,store);
}

/****** Reads input from the file line by line *********/

int ReadInput(FILE *fp , My402List *list){
    
    //parse the data from file
    char data[MAXBUFSIZE];
    int trans=0,tab_count=0;
    char *data_ptr = NULL, *nl_ptr = NULL;
    char *s_data[4];  // array of pointer for storing the data inputs
    
    memset(&data, 0, sizeof(data));
    
    while (fgets(data, MAXBUFSIZE, fp) != NULL) {
        if(strlen(data) > 1024){
            fprintf(stderr,"Line exceeds 1024 characters\n");
            exit(1);
        }
        trans=0;tab_count=0;
        memset(s_data, 0, sizeof(s_data));
        data_ptr = data;
        nl_ptr = strchr(data_ptr, '\n');

        *nl_ptr = '\0';
        char *tab_ptr = strchr(data_ptr,'\t');
        while (tab_ptr != NULL) {
            *tab_ptr++ = '\0';
            tab_count++;
            Validate(data_ptr,trans);
            s_data[trans++] = data_ptr;
            data_ptr = tab_ptr;
            tab_ptr = strchr(data_ptr,'\t');
        }
        if(tab_count != 3){
            fprintf(stderr,"Invalid data!\n");
            exit(1);
        }
        if(Validate(data_ptr,trans)){
            s_data[trans] = data_ptr;
            StoreNewData(s_data,list);
        }
    }
    return 1;
    
}

/*************************** MAIN **************************/

int main(int argc , char*argv[]){
    My402List node ;
    FILE *fp = NULL;
    struct stat statbuf;
    
    
    
    if(argc != 2 && argc != 3 ){
        fprintf(stderr, "Please enter correct command- warmup1 sort [tfile]\n");
        exit(1);
    }
    
    if(strcmp(argv[1],"sort") != 0){
        fprintf(stderr, "Please enter correct command- warmup1 sort [tfile]\n");
        exit(1);
    }

    
    if(argc == 2){
        fp = stdin;
                    
    }
    
    
    else if(argc == 3){
        fp = fopen(argv[2], "r");
        if(fp == NULL){
            fprintf(stderr, "File \"%s\" not found\n",argv[2]);
            exit(1);
        }
        
        stat(argv[2], &statbuf);
        
        if(S_ISDIR(statbuf.st_mode)){
           fprintf(stderr, "\"%s\" is a directory\n",argv[2]);
            exit(1);
        }
        
        
    }
    
    
    memset(&node,0,sizeof(My402List));
    
    if(!My402ListInit(&node)){
        fprintf(stderr,"Error while init!!\n");
    }
    if(!ReadInput(fp,&node)){
        fprintf(stderr,"Error while reading input!\n");
    }
    
    PrintStatement(&node);
    
    return 0;
    
}



#endif /*_MY402LIST_C_*/
