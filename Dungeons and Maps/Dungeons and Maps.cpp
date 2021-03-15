#include <iostream>
#include <vector>
using namespace std;

//Function to calculate shortest path on current map
int calculatePath (vector<string> v, vector<vector<bool>> visited, int curX, int curY) {
    int curLen = 0; //Declare current length of path on THIS map
    char c = v[curY][curX]; //Declare current char on the map

    while (c != 'T' || c != '.') {
        //If the current cell has been visited, it means the way is looped, so return 'numeric_limits<int>::max()'
        if (visited[curY][curX]) 
            return numeric_limits<int>::max();
        
        //Else if the cell hasn't been visited:
        else {
            char c = v[curY][curX]; //Update value of 'c'
            visited[curY][curX] = true; //Mark current cell as visited
        
            switch (c) {
                case 'T': { return curLen; } //If found 'T', return length to it
                case '.': { return numeric_limits<int>::max(); } //If the current cell is '.', it means there is no way to treasure, so return 'numeric_limits<int>::max()'
                case '^': { curY -= 1; break; } //Way Up
                case 'v': { curY += 1; break; } //Way Down
                case '<': { curX -= 1; break; } //Way Left
                case '>': { curX += 1; break; } //Way Right
            }

            //Increase current length to 'T' by 1
            curLen += 1;
        }
        
    }
    //"Control reaches end of non-void function" warning without 'return' statement
    return curLen;    
}

int main()
{
    /* Optional for input and output fron files
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    int w, h; //Declare width and height
    cin >> w >> h; cin.ignore();

    int startY, startX; //Declare starting X and Y
    cin >> startY >> startX; cin.ignore();

    int n; cin >> n; cin.ignore(); //Declare amount of maps
    int minLength = numeric_limits<int>::max(); //Declare minimum length to the treasure ('T')
    int ansIndex = numeric_limits<int>::max(); //Declare the index of map with the shortest path to the treasure ('T')

    //For 'n' times
    for (int i = 0; i < n; i++) {
        //Declare and input map with the treasures
        vector<string> map(h);
        for (int j = 0; j < h; ++j)
            cin >> map[j];
        
        //Create vector of visited cells in 2D map (to keep track of which cells have been visited in order to avoid LOOPING)
        vector<vector<bool>> visited(h, vector<bool> (w, 0));

        //Find current shortest path in i-th (current) map
        int curLength = calculatePath(map, visited, startX, startY);

        //Update the 'minLength' and 'ansIndex' if necessary
        if (curLength < minLength) {
            minLength = curLength;
            ansIndex = i;
        }
    }
    
    //If there is no 'ansIndex' (haven't reached 'T' at any maps, print "TRAP").
    //Else print the index of the map with the shortest path
    cout << ((ansIndex != numeric_limits<int>::max()) ? to_string(ansIndex) : "TRAP" );

    return 0;
}
