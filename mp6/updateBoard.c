/*
    Intro: For this MP, we completed each function and debuged them in order. For the first function we
    followed the algorithm written in prose on the page and iterated through the board while checking if
    it was in bounds. For the second function, we made a copy of the board and counted the number
    of live neighbors in that board (same board). We used this copy so that it would update the board
    in one step, not as it went through the code. Then we iterated through the board and checked the
    number of live neighbors, which would then determine if the cell stayed the same, died, or was
    revived. For the third function, we made another copy of the board to iterate through, and then
    we counted how many cells in the board copy were different from the original board after updating
    the copy. If the counter was zero, then it was the same. If it was one, then the board changed.
    Partner: macraew2

*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int live_neighbors = 0;                             // output of number of how many neighbors to the cell are alive
    for(int i=row-1; i<=row+1; i++){                    // iterate through row
        if(i>=0 && i<=boardRowSize-1){                  // if the row is within bounds of the board
            for(int j=col-1; j<=col+1; j++){            // iterate through column
                if(j>=0 && j<=boardColSize-1){          // if the column is within the bounds
                    if(i != row || j != col){           // if the cell isn't at the cell location it's checking
                        if(board[i*boardColSize+j]){    // if the cell is alive
                            live_neighbors++;
                        }
                    }
                }
            }
        }
    }
    return live_neighbors;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int r = 0;                                                                         // temporary row counter
    int c = 0;                                                                         // temporar column counter 
    int deep[boardRowSize*boardColSize];                                               // copy of board
    int i;
    for(i=0; i<boardColSize*boardRowSize; i++){                                        // copy each value at location into deep
        deep[i] = board[i];
    }

    for(r=0; r<boardRowSize; r++){                                                      // iterate through rows and columns
        for(c=0; c<boardColSize; c++){
            if(countLiveNeighbor(deep, boardRowSize, boardColSize, r, c) == 2){         // if number of live neighbors is 2
                board[r*boardColSize+c] = board[r*boardColSize+c];                      // board stays same
            }
            else if(countLiveNeighbor(deep, boardRowSize, boardColSize, r, c) == 3){    // if number of live neighbors is 3
                board[r*boardColSize+c] = 1;                                            // dead cell becomes alive
            }
            else{
                board[r*boardColSize+c] = 0;                                            // cell dies
            }  
        }
    }

    
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int boardcopy[boardRowSize*boardColSize];                       // copy of board
    int i,j;                                                        // init i variable to copy board & init j variable to iterate thru board
    for(i=0; i<boardColSize*boardRowSize; i++){
        boardcopy[i] = board[i];
    }
    int counter = 0;                                                // counter for number of cells not the same
    updateBoard(boardcopy, boardRowSize, boardColSize);
    for(j=0; j<boardRowSize*boardColSize; j++){
        if((board[j]) != (boardcopy[j])){
            counter++;
        }
    }
    if(counter==0){
        return 1;                                                   // if board is same return 0
    }
    else{
        return 0;                                                   // if board isn't same return 1
    }
}
    


/*
   __Y___Y___
  /          \
 /            \
 }    0o0     {	
(              )		
|  U       U   |
\              /
 \___U____U___/			

:3

*/

