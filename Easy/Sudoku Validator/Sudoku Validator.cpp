//L:ink to the puzzle: https://www.codingame.com/training/easy/sudoku-validator
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Function to stop executing program;
void stop () {
    cout << "false";
    exit(0);
}

int main()
{
    //Create empty 2D Sudoku;
    vector<vector<int>> grid (9, vector<int> (9, 0));

    //Vector to store the correct sequence of values in rows, cols and sub-grids (sub-grid == square);
    vector<int> correctValues {1, 2, 3, 4, 5, 6, 7, 8, 9};

    //Input 2D Sudoku;
    for (int y = 0; y < 9; y++) 
        for (int x = 0; x < 9; x++) 
            cin >> grid[y][x];

    //Check each row and column: 
    for (int cur = 0; cur < 9; ++cur) {
        //Vectors to store current row's values and current column's values;
        vector<int> xs, ys;

        //Update current row's values;
        for (int i = 0; i < 9; ++i) 
            xs.push_back(grid[cur][i]);
        
        //Update current column's values;
        for (int i = 0; i < 9; ++i) 
            ys.push_back(grid[i][cur]);

        //Sort current row's values;
        sort(begin(xs), end(xs));

        //If sorted 'xs' is valid: 
        if (xs == correctValues) {
            //Sort current column's values;
            sort(begin(ys), end(ys));

            //If sorted 'ys' isn't valid, stop executing and print "false", else continue checking;
            if (ys != correctValues)
                stop();
        }
        else stop(); //Else if 'xs' isn't valid, stop executing and print "false";
    }

    //If all cols and rows are sorted and there are no repeating values, check squares then:
    for (int y = 0; y < 9; y += 3) {
        for (int x = 0; x < 9; x += 3) {
            //Vector to store current square's values;
            vector<int> square;

            //Add values to 'square' from grid;
            for (int i = y; i < y+3; ++i) 
                for (int j = x; j < x+3; ++j) 
                    square.push_back(grid[i][j]);

            //Sort square's values;
            sort(square.begin(), square.end());

            if (square != correctValues) //If sorted 'square' isn't valid, stop running program and print "false";
                stop();
        }
    }

    //If all rows and cols are valid, and squares are valid, print "true";
    cout << "true";

    return 0;
}
