//Link to the puzzle: https://www.codingame.com/training/medium/the-last-crusade-episode-1
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    int w, h; cin >> w >> h; cin.ignore(); //Number of cols and rows in a grid;
    vector<vector<int>> grid (h, vector<int> (w, 0)); //Create empty grid (maze) of size 'H x W', which contains NUMBER TYPES of cells;

    //'H' times:
    for (int i = 0; i < h; i++) {
        string LINE; getline(cin, LINE); //Input ROW of a maze, which contains NUMBER TYPES of cells;

        //Variables to extract NUMBER TYPES from string and place them into grid;
        stringstream ss(LINE); string word; 

        int num, j = 0; //'j' - 'x' coordinate of cells in the grid;

        //Start extracting NUMBERS OF TYPES from string; 
        //Link to learn more about extraction method: https://www.geeksforgeeks.org/extract-integers-string-c/;
        while (!ss.eof()) {
            ss >> word;
            if (stringstream(word) >> num)
                grid[i][j++] = num;
        }
    }
    
    int EX; cin >> EX; cin.ignore(); //The coordinate along the X axis of the exit (not useful for this first mission, but must be read).

    //Infinite game loop:
    while (1) {

        //Input Indy's current 'x', 'y' and entrance point ("TOP", "RIGHT" or "LEFT");
        int x, y; string pos; cin >> x >> y >> pos; cin.ignore();

        //'curCellType' - NUMBER TYPE of current cell in a grid;
        int curCellType = grid[y][x];

        //If 'curCellType' is 1 or 3, or 7, or 8, or 9, or 12, or 13, simply increase his 'y' coordinate;
        if (curCellType == 1 || curCellType == 3 || curCellType == 7 || curCellType == 8 || 
            curCellType == 9 || curCellType == 12 || curCellType == 13 )
            y++;
        
        //Else if 'curCellType' equals to 2:
        else if (curCellType == 2) {
            if (pos == "LEFT") x++;
            else x--;
        }

        //Else if 'curCellType' equals to 4:
        else if (curCellType == 4) {
            if (pos == "TOP") x--;
            else if (pos == "RIGHT") y++;
        }

        //Else if 'curCellType' equals to 5:
        else if (curCellType == 5) {
            if (pos == "TOP") x++;
            else if (pos == "LEFT") y++;
        }

        //Else if 'curCellType' equals to 6:
        else if (curCellType == 6) {
            if (pos == "LEFT") x++;
            else if (pos == "RIGHT") x--;
        }

        //Else if 'curCellType' equals to 10:
        else if (curCellType == 10) x--;

        //Else if 'curCellType' equals to 11:
        else x++;

        //Output updated 'x' and 'y' of Indy;
        cout << x << " " << y << endl;
    }

    return 0;
}
