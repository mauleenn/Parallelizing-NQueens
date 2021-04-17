// Parallel version of the N-Queens problem.


#include <iostream>  
#include <omp.h>
#include <time.h>
#include <sys/time.h>

// Timing execution
double startTime, endTime;

// Number of solutions found
int numofSol = 0;

// Board size and number of queens
#define N 11

void placeQ(int queens[], int row, int column) {
    
    for(int i = 0; i < row; i++) {
        // Vertical
        if (queens[i] == column) {
            return;
        }
        
        // Two queens in the same diagonal
        if (abs(queens[i] - column) == (row-  i))  {
            return;
        }
    }
    
    // Set the queen
    queens[row] = column;
    
    if(row == N-1) {
        
        #pragma omp atomic 
            numofSol++;  //Placed the final queen, found a solution
        
        #pragma omp critical
        {
            std::cout << "The number of solutions found is: " << numofSol << std::endl; 
            for (int row = 0; row < N; row++) {
                for (int column = 0; column < N; column++) {
                    if (queens[row] == column) {
                        std::cout << "X";
                    }
                    else {
                        std::cout << "|";
                    }
                }
                std::cout  << "\n"  << std::endl; 
            }
        }
    }
    
    else {
        
        // Increment row
        for(int i = 0; i < N; i++) {
            placeQ(queens, row + 1, i);
        }
    }
} // End of placeQ()

void solve() {
    #pragma omp parallel num_threads(30)
    #pragma omp single
    {
        for(int i = 0; i < N; i++) {
            // New task added for first row and each column recursion.
            #pragma omp task
            { 
                placeQ(new int[N], 0, i);
            }
        }
    }
} // end of solve()

int main(int argc, char*argv[]) {

    startTime = omp_get_wtime();   
    solve();
    endTime = omp_get_wtime();
  
    // Print board size, number of solutions, and execution time. 
    std::cout << "Board Size: " << N << std::endl; 
    std::cout << "Number of solutions: " << numofSol << std::endl; 
    std::cout << "Execution time: " << endTime - startTime << " seconds." << std::endl; 
    
    return 0;
}

