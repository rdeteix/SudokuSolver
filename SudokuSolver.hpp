//
//  SudokuSolver.hpp
//  Sudoku Solver
//
//  Created by Rémi Deteix on 22/08/2017.
//  Singapore's prime minister Lee Hsien Loong Sudoku Solver
//  With slight modifications
//
//  Backtrack search
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>
#include <array>

using grid_init_type = std::array<std::array<char,9>,9>;
using grid_type = std::array<std::array<int,9>,9>;
using iter_type = std::array<int,81>::iterator;


class SudokuSolver
{
private:
    static constexpr int ones = 1022; // 111 111 111 0
    std::array<int,81> grid, seq;
    std::array<int,9> block, row ,col;
    std::array<int,81>::iterator iter;
    size_t count;
    
    void setVal(int i, int j, int val);
    int log2(int figure);
    iter_type nextIter(iter_type prev);
    void place(iter_type iter);

public:
    SudokuSolver(const grid_init_type &grid);
    void run();
    void print();
};

#endif /* SudokuSolver_hpp */
