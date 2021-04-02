//Link to the puzzle: https://www.codingame.com/ide/puzzle/asteroids
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

//Template to simplify substraction between pairs;
template <typename T,typename U>                                                   
pair<T, U> operator-(const pair <T, U> &l, const pair<T, U> &r) {   
    return { l.first - r.first, l.second - r.second };  
} 

int main()
{
    //Declare width, height, Time1, Time2 and Time3;
    int W, H, T1, T2, T3;

    //Declare differences: dT1 = T2 - T1, dT2 = T3 - T2;
    double dT1, dT2;

    //Declare strings to be used in input;
    string firstRow, secondRow;

    //Maps to store leters (asteroids) and their coordinates;
    //m1 - for first picture, m2 - for second picture; coordinates in pairs: y <-> x;
    map<char, pair<int, int>> m1, m2;

    cin >> W >> H >> T1 >> T2 >> T3; cin.ignore();

    //For each string from the input:
    for (int i = 0; i < H; ++i) {
        cin >> firstRow >> secondRow; cin.ignore();

        //Add ONLY letters and their coordinates to maps;
        for (int j = 0; j < W; ++j) {
            if (firstRow.at(j) != '.') m1[firstRow.at(j)] = {i, j};
            if (secondRow.at(j) != '.') m2[secondRow.at(j)] = {i, j};
        }
    }

    //2D array - output of the program (currently consists of dots, i.e. has no asteroids in there);
    vector<string> ans(H, string(W, '.') );

    //Calculate differences between times;
    dT1 = T2 - T1, dT2 = T3 - T2;
    
    //For each letter in first map:
    for (auto [curLetter, curPair1] : m1) {
        //curPair2 - coordinates of current letter in second map 'm2';
        //newPair - NEW coordinates to be calculated;
        //difPos - difference of positions (y2 - y1, x2 - x1);
        pair<int, int> curPair2, newPair {0, 0}, difPos;

        //Assign current letter's coordinates from second map 'm2' to its pair (y <-> x);
        curPair2 = m2[curLetter];

        //Calculate difference between coordinates of current letter;
        difPos = (curPair2 - curPair1);

        //Calculate NEW coordinates of current letter;
        newPair.first  = curPair2.first  + floor(difPos.first  * (dT2/dT1));
        newPair.second = curPair2.second + floor(difPos.second * (dT2/dT1));

        //If new coordinates are out of bound, don't assign its coordinates to answer (skip them) and continue calculations for other asteroids;
        if (newPair.first < 0 || newPair.first >= H || newPair.second < 0 || newPair.second >= W)
            continue;

        //If current char in answer is dot OR current asteroid is closer to us (by alphabet), assign its letter to NEW position;
        if (ans[newPair.first][newPair.second] == '.' || ans[newPair.first][newPair.second] > curLetter)
            ans[newPair.first][newPair.second] = curLetter;
    }

    //Print output;
    for (auto it : ans)
        cout << it << "\n";

    return 0;
}
