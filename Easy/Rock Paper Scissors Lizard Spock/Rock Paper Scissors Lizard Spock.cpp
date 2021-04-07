#include <iostream>
#include <vector>
#include <map>
#include <deque>
using namespace std;

//Map to store which letters wins which: 'sCissors': "Paper" and "Rock"; 'Paper': "Rock" and "Spock" etc.
map<char, string> m { {'C', "PL"}, {'P', "RS"}, {'R', "LC"}, {'L', "SP"}, {'S', "CR"} };

//Function to determine which letters wins:
bool hits (char comp1, char comp2) {
    //If there is 'comp2' in 'comp1', it means 'comp1' wins 'comp2';
    return (m[comp1].find(comp2) != string::npos);
}

int main()
{
    //Declare empty deque to store pairs: NUMPLAYER <--> SIGNPLAYER;
    deque<pair<int, char>> players;

    //Create array of vectors to store opponents of n-th NUMPLAYER in his n-th vector (with buffer for 6 players);
    vector<int> opponents[1030];
    
    //'n' times:
    int n; cin >> n; cin.ignore();
    for (int i = 0; i < n; ++i) {
        //Declare and input 'NUMPLAYER' and 'SIGNPLAYER';
        int num; char c; cin >> num >> c; cin.ignore();

        //Create a pair: 'NUMPLAYER' <--> 'SIGNPLAYER';
        players.push_back({num, c});
    }
    
    //While there is no one player in deque (winner):
    while (players.size() != 1) {
        //'comp1' - letter of current player; 'comp2' - letter of next player (first player's opponent);
        char comp1 = players[0].second, comp2 = players[1].second;

        //'num1' - number of current player; 'num2' - number of next player (first player's opponent);
        int num1 = players[0].first, num2 = players[1].first;

        //If first player wins second player, add winner to the end of deque in order to compare him with another player again;
        //Add second player's num to first player's opponents list;
        if (hits(comp1, comp2)) {
            players.push_back({num1, comp1});
            opponents[num1].push_back(num2);
        }

        //If second player wins first player, add winner to the end of deque in order to compare him with another player again;
        else if (hits(comp2, comp1)) {
            players.push_back({num2, comp2});
            opponents[num2].push_back(num1);
        }

        //Else if both players have same letters (e.g. 'L' and 'L'), add player with LEAST num to deque and 'opponents' vector;
        else {
            players.push_back({((num1<num2) ? num1 : num2), ((num1<num2) ? comp1 : comp2)});
            opponents[(num1<num2) ? num1 : num2].push_back(num1<num2 ? num2 : num1);
        }

        //Erase current two players from deque;
        players.erase(players.begin(), players.begin() + 2);
    }

    //Print winner's num;
    cout << players[0].first << "\n";

    //Print winner's opponents' nums;
    for (int i = 0; i < opponents[players[0].first].size(); ++i) {
        cout << opponents[players[0].first][i] << ( (i < opponents[players[0].first].size()-1) ? " " : "" );
    }

    return 0;
}
