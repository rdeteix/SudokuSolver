//
//  main.cpp
//  Sudoku Solver
//
//  Created by Rémi Deteix on 22/08/2017.
//  Singapore's prime minister Lee Hsien Loong Sudoku Solver
//  With slight modifications
//
//  Backtrack search
//

#include <iostream>
#include <array>
#include "SudokuSolver.hpp"
#include <ctime>




int main(int argc, const char * argv[]) {
    grid_init_type grid1 =
    {{
        {'9','0','0','1','0','0','0','0','5'},
        {'0','0','5','0','9','0','2','0','1'},
        {'8','0','0','0','4','0','0','0','0'},
        {'0','0','0','0','8','0','0','0','0'},
        {'0','0','0','7','0','0','0','0','0'},
        {'0','0','0','0','2','6','0','0','9'},
        {'2','0','0','3','0','0','0','0','6'},
        {'0','0','0','2','0','0','9','0','0'},
        {'0','0','1','9','0','4','5','7','0'}
    }};
    grid_init_type grid2 =
    {{
        {'4','0','0','3','0','9','0','7','0'},
        {'0','0','0','0','6','0','1','0','0'},
        {'8','0','0','1','0','5','0','9','0'},
        {'0','5','0','7','0','0','0','0','0'},
        {'1','0','0','2','0','8','0','0','7'},
        {'0','0','0','0','0','6','0','5','0'},
        {'0','8','0','6','0','1','0','0','5'},
        {'0','0','9','0','3','0','0','0','0'},
        {'0','7','0','5','0','2','0','0','3'}
    }};
    
    std::clock_t begin = std::clock();

    SudokuSolver solver(grid1);
    //solver.print();
    solver.run();
    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC *1000;

    std::cout <<"Time (ms) : "<< elapsed_secs << std:: endl;
    return 0;
}
