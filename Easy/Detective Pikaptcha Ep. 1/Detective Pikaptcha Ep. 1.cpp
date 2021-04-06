//Link to the puzzle: https://www.codingame.com/training/easy/detective-pikaptcha-ep1
#include <iostream>
#include <vector>
using namespace std;

//Function to replace current DIGIT char with NUMBER of adjacent passages;
char countPassages (vector<string> grid, int y, int x, int w, int h) {
    //Vectors to store coordinates of 4-adjacency neighbors (to check all neighbors of current cell);
    vector<int> dx {-1, 1}, dy {-1, 1};

    //Check all neighbors on X axis; 
    for (int i = 0; i < 2; ++i) {
        int newX = x + dx[i];
        if (newX < w && newX >= 0 && isdigit(grid[y][newX]))
            grid[y][x] = grid[y][x] + 1;
    }

    //Check all neighbors on Y axis;
    for (int i = 0; i < 2; ++i) {
        int newY = y + dy[i];
        if (newY < h && newY >= 0 && isdigit(grid[newY][x]))
            grid[y][x] = grid[y][x] + 1;
    }
    
    return grid[y][x];
}

int main()
{
    //Declare and input width and height of a maze;
    int w, h; cin >> w >> h; cin.ignore();

    //Declare vector to store the whole grid;
    vector<string> grid;

    //Input the whole maze and store it in 'grid';
    for (int i = 0; i < h; i++) {
        string s; cin >> s; cin.ignore(); 
        grid.push_back(s);
    }

    //For each character in maze:
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; ++j) {
            if (isdigit(grid[i][j])) //If current char is a DIGIT:
                grid[i][j] = countPassages(grid, i, j, w, h); //Replace this char with number of adjacent passages;
        }
    }

    //Print answer;
    for (auto it : grid) cout << it << endl;

    return 0;
}
