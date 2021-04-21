// Parallel version of the N-Queens problem.

#include <iostream>  
#include <omp.h>
#include <chrono>
#include <sys/time.h>
#include <sstream>
#include <iomanip>

// Number of solutions found
int numofSol = 0;

// Prevents overhead caused by parallel IOs
std::ostringstream globalOss;

// Board size and number of queens
const int N = 4;

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
        
        std::ostringstream oss;
        oss << "The number of solutions found is: " << numofSol << std::endl; 
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                if (queens[row] == column) {
                    oss << "X";
                }
                else {
                    oss << "|";
                }
            }
            oss  << std::endl << std::endl; 
        }

        #pragma omp critical
        globalOss << oss.str();
    }
    else {

        for(int i = 0; i < N; i++) {
            placeQ(queens, row + 1, i);
        }
    }
} // End of placeQ()

void solve() {
    
    #pragma omp parallel
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

    auto begin = std::chrono::high_resolution_clock::now(); 
    solve();
    std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - begin;
    double execution_time = elapsed.count();

    std::cout << globalOss.str();
  
    // Print board size, number of solutions, and execution time. 
    std::cout << "Board Size: " << N << std::endl; 
    std::cout << "Number of solutions: " << numofSol << std::endl; 
    std::cout << "Execution time: "  << std::fixed << std::setprecision(9) << execution_time << " seconds." <<std::endl;
    
    return 0;
}