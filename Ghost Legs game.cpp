#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
int goRight(vector<string> v, int curRow, int curPos); //Function to go right to next column
int goLeft(vector<string> v, int curRow, int curPos); //Function to go left to next column

//Function to get pair of top char <-> down char
char getPair(char c, vector<string> v, int w, int h) {
    int i = 1, curPos = v.front().find(c);

    //cout << "\n" << c << ":\n";

    while (i < h) {
        //If it's a down char, return this character
        if (i == h-1) { return v[i][curPos]; }

        //Else
        else {
            //cout << i << "\n";

            //if it's a pipe ('|')
            if (v[i][curPos] == '|') {

                //If there is a '-' to its right, go right
                if (curPos >= 0 && v[i][curPos+1] == '-') { 
                    //cout << i << " " << curPos << "\n"; 
                    curPos = goRight(v, i, curPos);
                }

                //Else if there is a '-' to its right, go right
                else if (curPos > 0 && curPos <= w && v[i][curPos-1] == '-') { 
                    //cout << i << " " << curPos << "\n";
                    curPos = goLeft(v, i, curPos);
                }
            }
            //cout << i << " " << curPos << "\n"; 
            ++i;
        }
    }

    return '0';
}

//Function to get pairs (top char <-> down char)
void playGame(vector<string> v, int w, int h) {
    //Declare a map, which will store the pairs of top char <-> down char
    unordered_map<char, char> m;

    //Declare vectors, which will store top chars chars to start the game
    vector<char> top;

    //Get top chars
    for (auto it : v.front()) if (!isspace(it)) top.pb(it);

    //For each char in top chars, get its pair from down chars
    for (int i = 0; i < top.size(); ++i) {
        m[top[i]] = getPair(top[i], v, w, h);
    }

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
    
    //Declare width and height; input width and height
    int w, h; cin >> w >> h; cin.ignore(); 

    //Create a vector of strings which will store the Ghost Legs
    vector<string> v(h);

    //Input Ghost Legs
    for (int i = 0; i < h; ++i)
        getline(cin, v[i]);

    //Call a function to get pairs (top char <-> down char)
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
