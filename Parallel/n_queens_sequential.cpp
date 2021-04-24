// Sequential version of the N-Queens problem.

#include <iostream>  
#include <chrono>
#include <sys/time.h>
#include <sstream>
#include <iomanip>

// Number of solutions found
int numofSol = 0;

// Prevents overhead caused by parallel IOs
std::ostringstream globalOss;

// Board size
const int N = 13;

void placeQ(int queens[], int row, int column) {
    
    for(int i = 0; i < row; i++) {

        // Two queens in the same row
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
        numofSol++;  //Placed final queen, found a solution.
        
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
        // Prints the chessboard but doesn't include the 
        // printing in the overall timing of the program.
        globalOss << oss.str();
    }
    else {
        // Increment row
        for(int i = 0; i < N; i++) {
            placeQ(queens, row + 1, i);
        }
    }
} 

void solve() {

    for(int i = 0; i < N; i++) {
        placeQ(new int[N], 0, i);
    }
} 

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
