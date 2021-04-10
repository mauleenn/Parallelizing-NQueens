#include <iostream>  
#include <omp.h>
#include <time.h>
#include <sys/time.h>

// Timing execution
double startTime, endTime;

// Number of solutions found
int numofSol = 0;

// Board size
#define N 4

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

    #pragma omp critical 
    {
        numofSol++;  //Placed final queen, found a solution
    }

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
    #pragma omp parallel
    #pragma omp single
  {
      for(int i = 0; i < N; i++) {
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
  
 std::cout << "Number of solutions: " << numofSol << std::endl; 
 std::cout << "Execution time:" << endTime - startTime << std::endl; 

return 0;
}
