#include <iostream>  
#include <omp.h>
#include <time.h>
#include <sys/time.h>

double startTime, endTime;
int numofSol = 0;
#define N 10

void setQueen(int queens[], int row, int column) {
    
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
         setQueen(queens, row + 1, i);
     }
}
} // End of setQueen

void solve() {
    #pragma omp parallel
    #pragma omp single
  {
      for(int i = 0; i < N; i++) {
          #pragma omp task
          {
              setQueen(new int[N], 0, i);
          }
        }
  }
}

int main(int argc, char*argv[]) {

   startTime = omp_get_wtime();   
   solve();
   endTime = omp_get_wtime();
  
 std::cout << "Number of solutions: " << numofSol << std::endl; 
 std::cout << "Execution time:" << endTime - startTime << "ms.\n";

return 0;
}
