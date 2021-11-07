#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
int getpath(maze_t * maze, int col, int row); // helper function to find path from start to end

/*
    Intro: For this mp, we went through all the functions in order and added a helper function to help perform a recursive function
    with backtracking for solve maze. We realized that unlike the last mp, the pointer array cells for this one was a double
    pointer and pointed to a row and then a column. So we used cells while keeping this notation in mind to create, print, and destroy the maze.
    For create maze we allocated space for the pointer array cells and the maze, making maze the type of struct maze_t. We reade from
    the file pointed to by fileName and read from it, getting the dimensions from the first line as well as the rest of the data which filled the
    maze we created with cells. We also needed to read the newlines in order to print the maze properly later. For the solve maze function we used
    recursion and backtracking to check all the paths until end was found, while backtracking if a place was already visited or didn't work. For the 
    body of it (not the base case or backtracking) we checked bounds, checked if the next spot was valid (ie. not an obstacle or visited), and for
    all directions.

    Partner: macraew2
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int rows, cols = 0;

    FILE *fp;
    // int file = *fileName;
    fp = fopen(fileName, "r");                                 // open and read file attached to fileName pointer
    // if(fp == NULL){
    //     return -1;
    // }

    
    fscanf(fp, "%d %d", &rows, &cols);                         // get dimensions by reading first two integers


    maze_t * maze = malloc(sizeof(maze_t));                    // allocate space in mem for maze that's the size of maze_t struct
    // if(maze->cells == NULL){                                   // if no memory left
    //     printf("memory full");
    //     exit(0);
    //     }

    //maze->cells[0][2]


    int i, j;
    maze->cells = (char **)malloc(rows*sizeof(char *));        // allocate memory for cells pointer array

    maze->height = rows;                                       // get rows and columns
    maze->width = cols;
    
    for(i=0; i<rows; i++){                                     // iterate through rows to make cells pointer array
        maze->cells[i] = (char *)malloc(sizeof(char)*cols);
        // if((maze->cells[i]) == NULL){                           // if no memory left
        //     printf("memory full");
        //     exit(0);
        // }
    }

    for(i=0; i<rows; i++){                                     // iterate through rows
        char newline = fgetc(fp);                              // create temporary variable to hold newlines found b/c fgetc gets next char
        for(j=0; j<cols; j++){                                 // iterate through columns
            maze->cells[i][j] = fgetc(fp);                     // assign values found in file to maze
            //fscanf(fp, "%c", &(maze->cells[i][j]));
        }
        newline++;
    }
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            if(maze->cells[i][j] == 'S'){
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == 'E'){
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
    }

    fclose(fp);
    return maze;                                               // return pointer to maze
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    int rows = maze->height;
    for(i=0; i<rows; i++){       // iterate through rows
        free(maze->cells[i]);    // free each row value
    }
    free(maze->cells);           // free cells pointer array
    free(maze);                  // free new maze struct


}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i;
    int j;
    int rows = maze->height;
    int cols = maze->width;

    for(i=0; i< rows; i++){                         // iterate through rows and columns
        for(j=0; j<cols; j++){
            printf("%c", maze->cells[i][j]);        // print maze array for each row and column value from by cells pointer
        }
        printf("\n");                               // print newline after each new row
    }
    
}

int getpath(maze_t * maze, int col, int row){

   // col = maze->startColumn;                      // set starting point
   // row = maze->startRow;
    
    if(col+1<(maze->width)) {                     //make sure its in bounds
        if(maze->cells[row][col+1]==' '){         //see if its empty
            maze->cells[row][col+1]='*';          //if it is fill it with a * to mark we've moved
        if(getpath(maze, col+1, row)==0) {        // recursion! go the spot we found and go through everything again, it should go until the end of the maze or a dead end
           maze->cells[row][col+1]='x';
        }
        else{
            return 1;
        }
    }
    }
    if(col-1>0) {
        if(maze->cells[row][col-1]==' '){
            maze->cells[row][col-1]='*';
        if(getpath(maze, col-1, row)==0){
           maze->cells[row][col-1]='x';
        }
        else{
            return 1;
        }
        }
    }
if(row+1<(maze->height)) {
    if(maze->cells[row+1][col]==' '){
        maze->cells[row+1][col]='*';
        if(getpath(maze, col, row+1)==0){
            maze->cells[row+1][col]='x';
        }
        else{
            return 1;
        }

    }
    }
    if(row-1>0) {
    if(maze->cells[row-1][col]==' '){
        maze->cells[row-1][col]='*';
         if(getpath(maze, col, row-1)==0){
            maze->cells[row-1][col]='x';
         }
         else{
            return 1;
         }
    }
  }
if(maze->cells[row][col+1] =='E'){
    return 1;
}
if(maze->cells[row][col-1] =='E'){
    return 1;
}
if(maze->cells[row+1][col] =='E'){
    return 1;
}
if(maze->cells[row-1][col] =='E'){
    return 1;
}
  return 0;
}




/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    return getpath(maze, col, row); // calling helper function
}
