#include <iostream>  
#include <chrono>
#include <sys/time.h>

// Timing execution
double startTime, endTime;

// Number of solutions found
int numofSol = 0;

// Board size and number of queens
#define N 8

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
} // End of placeQ

// Set the queen
queens[row] = column;

if(row == N-1) {
        numofSol++;  //Placed final queen, found a solution

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

else {
     // Increment row
     for(int i = 0; i < N; i++) {
         placeQ(queens, row + 1, i);
     }
}
} // End of placeQ()

void solve() {
      for(int i = 0; i < N; i++) {
              placeQ(new int[N], 0, i);
        }
} // end of solve()

int main(int argc, char*argv[]) {

   auto begin = std::chrono::high_resolution_clock::now(); 
   solve();
   auto end = std::chrono::high_resolution_clock::now();
   auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  
 // Print board size, number of solutions, and execution time 
 std::cout << "Board Size: " << N << std::endl; 
 std::cout << "Number of solutions: " << numofSol << std::endl; 
 std::cout << "Execution time: " << elapsed.count() * 1e-9 << " seconds." << std::endl; 

return 0;
}
