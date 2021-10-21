#include "sudoku.h"

/*-------------------------------------------------------------------------------------------------
Start here to work on your MP7

Intro: For this MP, we worked on each function sequentially and used the site as a guide. For the
first function we iterated through the rows with a for loop and checked to see if the value was there.
For the second, we did the same except iterating through the columns. The third function was more
complicated and confusing. We realized we needed to only check withing the designated 9 3x3 grids,
so we created separate values to use to iterate through just the section the cell was in. For the
fourth, we just called all the previous helper functions. Then for the last, we essetnially just 
followed the site's guide.

Partner: macraew2

-------------------------------------------------------------------------------------------------*/
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int x;                        // init variable to iterate through row
  // BEG TODO
  for(x=0; x<9; x++){           // iterate through rows
    if(sudoku[i][x] == val){    // see if value is in that location
      return 1;
    }
  }

  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int y;                        // init variable to iterate through columns
  for(y=0; y<9; y++){           // iterate through columns
    if(sudoku[y][j] == val){    // is value in that location
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  int a = 0;                      // init temp variables to only go through 3x3 grid
  int b = 0;

  /* finding & setting starting point of 3x3 based on current array cell*/

  if(i>= 3){                     // if row is greater than or equal to three set temp row to three           
    a = a+3;
  }
  if(i>=6){                     // if row is greater than or equal to six set temp row to six 
    a = a+3;
  }
  if(j>=3){                      // if column is greater than or equal to three set temp col to three 
    b = b+3;
  }
  if(j>=6){                     // if column is greater than or equal to six set temp column to six 
    b = b+3;
  }

  for(int r=0; r<3; r++){       // iterate through rows and columns and see if in temp [a,b] cell
    for(int c=0; c<3; c++){
      if(sudoku[a][b] == val){
        return 1;
      
      }
      b++;                      // increment temp column
    }
    a++;                        // increment temp row
    b=b-3;                      // subtract row by three so it stays within 3x3
  }


  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  /* call all previous helper functions to optimize later*/
  if(is_val_in_row(val, i, sudoku) == 0){
    if(is_val_in_col(val, j, sudoku) == 0){
      if(is_val_in_3x3_zone(val, i, j, sudoku) == 0){
        return 1;                                             // return true
      }
    }
  }

  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j = 0;                                           // init temp variables
  int unfilled = 0;

  /* see if all cells are assigned numbers*/
  for(i=0; i<9; i++){                                     // iterate through entire array's rows and columns
    for(j=0; j<9; j++){
      if(sudoku[i][j] == 0){
        unfilled++;                                       // increment variable to count if cell is unfilled
        
        break;
      }
    }
    if(unfilled!=0){                                      // if not unfilled break out of column loop
        break;
      }
  }
  //printf("%d %d",i ,j);
  if(unfilled == 0){
    return 1;
  }
  for(int num=1; num<=9; num++){
    if(is_val_valid(num, i, j, sudoku) == 1){             // if cell can be filled with number
      sudoku[i][j] = num;                                 // set cell to number
      if(solve_sudoku(sudoku)){                           // recursive function
        return 1;                                         // return true
      }
      sudoku[i][j] = 0;                                   // make non filled cell
    }
    
  }
  return 0;                                               // return false
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





