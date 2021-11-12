#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* 
    Intro: For this mp, we started with load tuples, where we opened the file and read the dimensions and then also the data.
    We then created a new matrix with the sp tuples struct type and loaded the dimensions read into it and set the non zero
    to 0. We then set the head of linked list to NULL. Then we kept reading from the file and loading the rows cols and values
    into set tuples, where we either insert, delete, or replace a node. In set tuples, we realized we had these three cases
    and different cases for each (beginning, middle, or end of the linked list). Overall, the function iterates through the
    list through the while loop and increments by setting curr to it's next node. Next, gv tuples iterates through, similar to
    how set tuples does, and checks the dimensions saved within each node against the dimensions you want to find. Save tuples
    iterates through the same way and just writes to a file that the argument pointer points to in memory. Destory tuples, again,
    iterates the same way but frees the memory at each node and then frees the entire new struct made (mat_t). Add tuples iterates
    with a while loop, like the last functions, but iterates differently, depending on if the dimensions are the same for MatA and
    MatB or if the index is less or more. It then adds the values and passes set tuples with the new sum and the dimensions to create
    the new retmat matrix.

    Partner: macraew2
*/


sp_tuples * load_tuples(char* input_file)
{
int rows, cols;
sp_tuples* mat_t = (sp_tuples*)malloc(sizeof(sp_tuples));               // make mat_t sp tuples type
FILE *fp;
fp = fopen(input_file, "r");                                            // open and write to file

fscanf(fp, "%d %d", &rows, &cols);                                      // scan to get dimensions

sp_tuples_node* tuples_head = malloc(sizeof(sp_tuples_node));
mat_t->m = rows;      //i think sp_tuples is a variable name and type if not make a different variable for it
mat_t->n = cols; 
mat_t->tuples_head=tuples_head;
mat_t->nz=0;
tuples_head->row=0;
tuples_head->col=0;
tuples_head->value=0;

tuples_head->next=NULL;        //have the end point to NULL

 int tempr,tempc;
double tempv;
while(1){
    fscanf(fp, "%d %d %lf", &tempr, &tempc, &tempv);     //check if its the end of file and store contents int temp variables if not
    if(feof(fp) != 0){                                   // loop while until end of file is reached
        break;
    }

    set_tuples(mat_t, tempr, tempc, tempv) ;             // call set tuples to sort, insert, delete, and replace


}

    fclose(fp);                                          // close file
    return mat_t;                                        // return pointer to structure
}



double gv_tuples(sp_tuples * mat_t,int row,int col){
 
 //sp_tuples_node * temp;
   sp_tuples_node *before = mat_t->tuples_head;
   sp_tuples_node *current = before->next;


while(1)  {   //if u just put while with nothing in it will it go until it returns sum?
if(current->row>row){            //if its at a larger row
       if(current->col>col){        //and collumn
           if((before->col==col)&&(before->row==row)){
               return before->value;            //if before has the same rows and cols then it has the value we want
           }
           else{
              return 1; //idk what we return if those coordinates do not exist
           }
       }
}
       before=current;
       current=current->next;
       if(current==NULL){
                           //idk what we return if those coordinates do not exist  
}
}
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node * new;
    sp_tuples_node * temp;                                                          // temp to store curr
    sp_tuples_node *before = mat_t->tuples_head;
    sp_tuples_node *current = before->next;
 

   if(value==0){
       while(1){                                                                     // while true
    if(((current->row)*(mat_t->n)+(current->col))>=(row*(mat_t->n)+col)){            //if its at a larger row
      // if(current->col>col){        //and collumn
           if((before->col==col)&&(before->row==row)){                               // if row and col are same
               temp=before->next;                                                    // move the pointers
               before->next=current->next;   
               free(temp);                                                           // free the memory
               mat_t->nz--;                                                          // decrement number of non zero numbers
               return;
           }

       }
      // }
       

       before=current;
       current=current->next;
       if(current==NULL){
         return;                   //exit or break
       }
   
   }
} 
         
while(1){
     if (current==NULL){
       temp =before->next;                   //temporarilaly hold the value
           before->next = malloc(sizeof( sp_tuples_node));       //the the previous one point to our new creation
           new=before->next;            //assign new one
           new->next=temp;          //new one is pointing towards the current one
            //current->next=temp;                 //have our new one point to the next
            //temp=before->next;      //fill in the values to the new spot:
            new->row=row;
            new->col=col;
            new->value=value;
            mat_t->nz++;
              return;          //EXIT
   }

   if(((current->row)*(mat_t->n)+(current->col))>=(row*(mat_t->n)+col)){            //if its at a larger row
       //if((current->col)>=col){        //and collumn
           if((before->col==col)&&(before->row==row)){
               before->value=value;
               break;//EXIT
           }

           temp =before->next;                   //temporarilaly hold the value
           before->next = malloc(sizeof( sp_tuples_node));       //the the previous one point to our new creation
           new=before->next;            //assign new one
           new->next=temp;          //new one is pointing towards the current one
            //current->next=temp;                 //have our new one point to the next
            //temp=before->next;      //fill in the values to the new spot:
            new->row=row;
            new->col=col;
            new->value=value;
            mat_t->nz++;
              return;          //EXIT
       
  // }
}

       before=current;
       current=current->next;
    //    if(current==NULL){
    //        return; //EXIT?
    //    }
   
} 

}



void save_tuples(char* file_name, sp_tuples * mat_t)
{
    FILE *fp;
    fp = fopen(file_name, "w");                                             // open and prepare to write to file
    if(fp == NULL){                                                         // incase file could not open
        printf("Error: file did not open");
    }

    sp_tuples_node * curr = mat_t->tuples_head;                             // set curr to start at head 
    curr=curr->next;                                                        // current node increments to next

fprintf(fp, "%d %d \n", mat_t->m, mat_t->n);                                // print dimensions to file
    while(1){
       
       
        fprintf(fp, "%d %d %lf \n",  curr->row,  curr->col, curr->value);

        if(curr->next == NULL){                                     // if on last node then it's finished adding to file & break out of while loop
            break;
        }

        curr = curr->next;
    }

    fclose(fp);
    return;
}




sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

sp_tuples_node * curA = matA->tuples_head;
sp_tuples_node *curB =matB->tuples_head;
sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
retmat->m=matB->m;                                                          // place argument matrix values (m,n, nz) into retmat
retmat->n=matB->n;
retmat->nz=0;

sp_tuples_node* head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));    // allocate memory for head of retmat
head->row=0;
head->col=0;
head->value=0;
head->next=NULL;

//int rows =matB->m;
int cols=(matB->n);
retmat->tuples_head= head;

curA=curA->next;                                                            //have it pointing at the first value
curB=curB->next;

while(1){

    if(((curA->row)*cols+(curA->col)) == ((curB->row)*cols+(curB->col))){               // if index are the same
        set_tuples(retmat, (curB->row), (curA->col), ((curA->value)+(curB->value)));
        curA=curA->next;
        curB=curB->next;
        retmat->nz++;
    }
    else if (((curA->row)*cols+(curA->col))<((curB->row)*cols+(curB->col))){            // if A index less than B
        set_tuples(retmat,(curA->row), (curA->col),  (curA->value) );
        curA=curA->next;
        retmat->nz++;
    }
    else{
        set_tuples(retmat,(curB->row), (curB->col),  (curB->value) );
        curB=curB->next;
        retmat->nz++;
    }
    if(curA==NULL){                                                                     // if at end
set_tuples(retmat,(curB->row), (curB->col),  (curB->value) );
        curB=curB->next;
        retmat->nz++;
        break;
    } 
    if(curB==NULL){
        set_tuples(retmat,(curA->row), (curA->col),  (curA->value) );
        curA=curA->next;
        retmat->nz++;
        break;
    }
}

    return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 

sp_tuples_node * curA = matA->tuples_head;
sp_tuples_node *curB =matB->tuples_head;
sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
retmat->m=matB->m;
retmat->n=matB->n;
retmat->nz=0;

sp_tuples_node* head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
head->row=0;
head->col=0;
head->value=0;
head->next=NULL;

//int rows =matB->m;
int cols=(matB->n);
retmat->tuples_head= head;

curA=curA->next;    //have it pointing at the first value
curB=curB->next;

while(1){

    if(curA->row==curB->row && curA->col==curB->col){
        set_tuples(retmat, curB->row, curA->col, (curA->value)*(curB->value));
        curA=curA->next;
        curB=curB->next;
    }
    else if (((curA->row)*cols+(curA->col))<((curB->row)*cols+(curB->col))){
       
        curA=curA->next;
    }
    else{
       
        curB=curB->next;
    }
    if(curA==NULL&&curB==NULL){
        break;
    }
}

    return retmat;
}





   
void destroy_tuples(sp_tuples * mat_t){
     sp_tuples_node * cur = mat_t->tuples_head;
      sp_tuples_node *temp;
    while(1){
        temp = cur->next; 
        if (temp==NULL){
            break;
        }
        free(cur);
     cur=temp;

    }
    free(mat_t);
    //destroy
    return;
} 




