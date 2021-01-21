#include <bits/stdc++.h> //Library to store primary needed functions
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
int goRight(vector<string> v, int curRow, int curPos); //Function prototype to go right to next column
int goLeft(vector<string> v, int curRow, int curPos); //Function prototype to go left to next column

//Function to get pair of top char <-> down char
char getPair(char c, vector<string> v, int w, int h) {
    int i = 1, curPos = v.front().find(c);

    while (i < h) {
        //If it's a very down char, return this character
        if (i == h-1) { return v[i][curPos]; }

        //Else
        else {
            //If current char is a pipe ('|')
            if (v[i][curPos] == '|') {

                //If there is a '-' to the right of current position, go right
                if (curPos >= 0 && v[i][curPos+1] == '-') { 
                    curPos = goRight(v, i, curPos);
                }

                //Else if there is a '-' to the left of current position, go left
                else if (curPos > 0 && curPos <= w && v[i][curPos-1] == '-') { 
                    curPos = goLeft(v, i, curPos);
                }
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
    for (auto it : v.front()) if (!isspace(it)) top.pb(it);

    //For each char in top chars, get its pair from down chars
    for (int i = 0; i < top.size(); ++i) 
        m[top[i]] = getPair(top[i], v, w, h);
    

    //Print the answer
    for (auto it : top)
        cout << it << m[it] << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
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

//Function to go right to next column
int goRight(vector<string> v, int curRow, int curPos) {
    for (curPos = curPos+1; v[curRow][curPos] != '|'; ++curPos) 
        if (v[curRow][curPos] == '|') 
            return curPos;
    

    return curPos;
}

//Function to go left to next column
int goLeft(vector<string> v, int curRow, int curPos) {
    for (curPos = curPos-1; v[curRow][curPos] != '|'; --curPos) 
        if (v[curRow][curPos] == '|') 
            return curPos;

    return curPos;
}
