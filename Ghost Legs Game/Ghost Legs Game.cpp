//Link to the puzzle: https://www.codingame.com/training/easy/ghost-legs
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int GO(vector<string> v, int curRow, int curPos, string way); //Function prototype to GO right to next column

//Function to get pair of top char <-> down char
char getPair(char c, vector<string> v, int w, int h) {
    int i = 1, curPos = v.front().find(c);

    while (i < h) {
        //If it's a very down char, return this character
        if (i == h-1) 
            return v[i][curPos];

        //Else
        else {
            //If current char is a pipe ('|')
            if (v[i][curPos] == '|') {

                //If there is a '-' to the right of current position, GO right
                if (curPos >= 0 && v[i][curPos+1] == '-') 
                    curPos = GO(v, i, curPos, "RIGHT");
                

                //Else if there is a '-' to the left of current position, GO left
                else if (curPos > 0 && curPos <= w && v[i][curPos-1] == '-') 
                    curPos = GO(v, i, curPos, "LEFT");
                
            }

            //Move down
            ++i;
        }
    }

    return '0';
}

//Function to get pairs (top char <-> down char)
void playGame(vector<string> v, int w, int h) {
    //Declare an unordered map, which will store the pairs of top char <-> down char
    unordered_map<char, char> m;

    //Declare vectors, which will store top chars chars to start the game
    vector<char> top;

    //Get top chars, which are not a ' ' char
    for (auto it : v.front()) 
        if (!isspace(it)) 
            top.push_back(it);

    //For each char in top chars, get its pair from down chars
    for (int i = 0; i < top.size(); ++i) 
        m[top[i]] = getPair(top[i], v, w, h);
    

    //Print the answer
    for (auto it : top)
        cout << it << m[it] << endl;
}

int main()
{
    //Declare width and height; input width and height; clean the input buffer (stream)
    int w, h; cin >> w >> h; cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    //Create a vector of strings of size 'h', which will store the Ghost Legs strings
    vector<string> v(h);

    //Input Ghost Legs strings
    for (int i = 0; i < h; ++i)
        getline(cin, v[i]);

    //Call a function to get pairs to each top character
    playGame(v, w, h);

    return 0;
}

//Function to GO right to next column
int GO(vector<string> v, int curRow, int curPos, string way) {
    for (curPos = (way == "RIGHT") ? curPos+1 : curPos-1; v[curRow][curPos] != '|'; curPos += (way == "RIGHT") ? 1 : -1) 
        if (v[curRow][curPos] == '|') 
            return curPos;
    
    return curPos;
}
