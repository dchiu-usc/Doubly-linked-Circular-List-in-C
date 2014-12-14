#include "warmup1.h"

/***************** Sort the list based on TIMESTAMP ***************/

void InserstionSort(My402List *list,void *obj_new){
    My402ListElem *elem = My402ListFirst(list), *next_elem = NULL;
    MyDS *key = NULL, *new_key = NULL, *next_key = NULL;
    long cur_value = 0, new_value = 0, next_value=0;
    int flag = 0;
    
    new_key = obj_new;
    
    // when no element in the list
    if (My402ListEmpty(list)) {
        My402ListAppend(list,obj_new);
    }
    
    else{
        for (elem = My402ListFirst(list);
             elem != NULL;
             elem = My402ListNext(list, elem) ) {
            
            next_elem = My402ListNext(list, elem);
            
            if( next_elem != NULL){
                
                
                key = elem->obj;
                next_key = next_elem->obj;
                next_value = atol(next_key->t_date);
                
                
                cur_value = atol(key->t_date);
                new_value = atol(new_key->t_date);
                
                
                if(new_value == cur_value){
                    fprintf(stderr,"Same TimeStamps!!!\n");
                    exit(1);
                }
                
                if(new_value > cur_value && new_value < next_value ){
                    flag = My402ListInsertAfter(list, obj_new, elem);
                    if(!flag){
                        fprintf(stderr,"Error while inserting obj after elem\n");
                        exit(1);
                    }
                    break;
                    
                    
                }
                else if(new_value< cur_value){
                    flag = My402ListInsertBefore(list, obj_new, elem);
                    if(!flag){
                        fprintf(stderr,"Error while sorting\n");
                        exit(1);
                    }
                    break;
                    
                }
            }
            else if(next_elem == NULL){
                
                new_value = atol(new_key->t_date);
                key = elem->obj;
                cur_value = atol(key->t_date);
                
                
                if(new_value == cur_value){
                    fprintf(stderr,"Same TimeStamps!!!\n");
                    exit(1);
                }
                
                if(new_value < cur_value){
                    flag = My402ListInsertBefore(list, obj_new, elem);
                    if(!flag)
                        fprintf(stderr,"Error while inserting obj before elem\n");
                }
                else{
                    flag = My402ListInsertAfter(list, obj_new, elem);
                    if(!flag){
                        fprintf(stderr,"Error while inserting obj after elem when one element is there!!\n");
                    }
                }
                break;
            }
        }
        
    }
    
}
