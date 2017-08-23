//
//  SudokuSolver.cpp
//  Sudoku Solver
//
//  Created by Rémi Deteix on 22/08/2017.
//  Singapore's prime minister Lee Hsien Loong Sudoku Solver
//  With slight modifications
//
//  Backtrack search
//

#include "SudokuSolver.hpp"

// If solver already created don't set static arrays again
static bool uninitialized = true;
// Array that converts 1d position to row, col and block id
static std::array<int,81> toRow, toCol, toBlock;


SudokuSolver::SudokuSolver(const grid_init_type & _grid)
{
    // Set static arrays again if first creation
    if(uninitialized)
    {
        for(unsigned int i = 0; i < 9; ++i)
        {
            for(unsigned int j = 0; j < 9; ++j)
            {
                int position = 9 * i + j;
                toRow[position] = i;
                toCol[position] = j;
                toBlock[position] = (i / 3) * 3 + ( j / 3);
            }
        }
        uninitialized = false;
    }
    
    // Set row, col, block available value
    // 1111111110 : 9 possibilities
    
    for(unsigned int i = 0; i < 9; ++i)
        block[i] = row[i] = col[i] = ones;
    // Initilize grid and seq
    for(int position = 0; position < 81; ++position){
        grid[position] = 0;
        seq[position] = position;
    }
    
    iter = seq.begin();
    
    // Set the known value in the grid
    for(unsigned int i = 0; i < 9; ++i)
        for(unsigned int j = 0; j < 9; ++j)
            if(_grid[i][j] != '0')
                setVal(i, j, _grid[i][j] - '0');
    
    count =0;
};

inline void SudokuSolver::setVal(int i, int j, int figure)
{
    // Get the 1d array position
    int position = 9 * i + j;
    // Set the figure th bit to 1
    int bit = 1 << figure;
    int nonbit = ~bit;
    // Put it in the grid
    grid[position] = bit;
    // This figure is no longuer available
    // Set revelevant block, row, col bit to 0
    block[toBlock[position]] &= nonbit;
    row[i] &= nonbit;
    col[j] &= nonbit;
    
    std::iter_swap(iter,seq.begin()+position);
    ++iter;
}


inline int SudokuSolver::log2(int figure)
{
    switch (figure)
    {
        case 2:
            return 1;
        case 4:
            return 2;
        case 8:
            return 3;
        case 16:
            return 4;
        case 32:
            return 5;
        case 64:
            return 6;
        case 128:
            return 7;
        case 256:
            return 8;
        case 512:
            return 9;
        default:
            return 0;
    }
}

// Return the cell with the fewest possibilities
iter_type SudokuSolver::nextIter(iter_type prev)
{
    iter_type next = nullptr;
    int bitCount, possibilities, position;
    int minBitCount = 100;

    for (auto iter2 = prev; iter2 < seq.end(); ++iter2) {
        position = *iter2;
        possibilities = block[toBlock[position]] & row[toRow[position]] & col[toCol[position]];
        bitCount = 0;
        while (possibilities)
        {
            possibilities &= ~(possibilities & -possibilities);
            ++bitCount;
        }
        if (bitCount < minBitCount)
        {
            minBitCount = bitCount;
            next = iter2;
        }
    }
    return next;
}

void SudokuSolver::place(iter_type _iter)
{
    if (_iter >= seq.end())
    {
        std::cout <<"Solution number "<< ++count << ": "<< std:: endl;
        puts("\n");
        print();
        return;
    }
    auto next = nextIter(_iter);
    std::iter_swap(_iter,next);
    int position = *_iter;
    
    int BlockIndex = toBlock[position],
    RowIndex = toRow[position],
    ColIndex = toCol[position];
    
    int possibilities = block[BlockIndex] & row[RowIndex] & col[ColIndex];
    
    while (possibilities)
    {
        int valbit = possibilities & (-possibilities); // Lowest 1 bit in possibilities
        int nonvalbit = ~valbit; // Set the lowest 1 bit to 0
        possibilities &= nonvalbit;
        grid[position] = valbit;
        block[BlockIndex] &= nonvalbit;
        row[RowIndex] &= nonvalbit;
        col[ColIndex] &= nonvalbit;
        
        place(_iter + 1);
        
        grid[position] = 0; // Unset the lowest 1 bit
        block[BlockIndex] |= valbit;
        row[RowIndex] |= valbit;
        col[ColIndex] |= valbit;
    }
    std::iter_swap(_iter,next);
}
void SudokuSolver::run()
{
    place(iter);
}


void SudokuSolver::print()
{
    for (int i=0; i<9; ++i)
    {
        for (int j=0; j<9; ++j)
        {
            printf( ((j+1)%3) ? "%d " : "%d|", log2(grid[i*9 +j]));
        }
        putchar('\n');
        if (!((i+1)%3))
            puts("------------------");
    }
    puts("\n");
}
