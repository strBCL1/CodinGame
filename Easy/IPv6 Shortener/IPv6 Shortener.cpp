//Link to the puzzle: https://www.codingame.com/training/easy/ipv6-shortener
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

//Function to get max value from map;
pair<int, int> maxValue (map<int, int> m) {
    pair<int, int> p {0, 0};

    for (pair<int, int> it : m) 
        if (it.second > p.second) 
            p = {it.first, it.second};

    return p;
}

int main()
{
    //Declare and input IPv6 address; 
    string ip; getline(cin, ip);

    //Replace all colons with spaces;
    replace_if(begin(ip), end(ip), [] (auto c) { return c == ':'; }, ' ' );

    //Vector of empty hex blocks of NEW shortened IPv6 address (with a buffer to avoid segmentation fault);
    vector<string> blocks(12, "");

    //Fill NEW IP address with blocks of old IPv6 address;
    stringstream ss(ip); int i = 0;
    while (!ss.eof()) 
        ss >> blocks[i++];
    

    //Erase all leading zeros from hex blocks;
    for (int i = 0; i < blocks.size(); ++i) 
        while (blocks[i].front() == '0' && blocks[i].size() > 1) 
            blocks[i].erase(0, 1);

    //Create a map to store indexes of ALL "0000" blocks and amount of NEXT "0000" blocks AFTER them;
    //Used to identify the longest sequence of "0000" blocks;
    map<int, int> m;

    //Fill map with positions of "0000" and amounts of "0000" blocks after them;
    for (int i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == "0") {
            m[i]++; 
            int curZerPos = i++;

            while (blocks[i++] == "0")
                m[curZerPos]++;             
        }
    }

    //Find longest "0000" sequence starting position;
    //.first = index of start, .second = amount of "0000" blocks after this position;
    pair<int, int> longestSeqStart = maxValue(m);//find_if(begin(m), end(m), [&] (auto i) {return i.second == ((--m.end())->second);});

    //IF it's not a single "0000" block:
    if (longestSeqStart.second > 1) {
        //Erase whole longest "0000" sequence;
        blocks.erase(blocks.begin() + longestSeqStart.first, blocks.begin() + longestSeqStart.first + longestSeqStart.second); 

        //Insert double-colon;
        blocks.insert(blocks.begin() + longestSeqStart.first, "::");
    }

    //Print shortened IPv6 address;
    for (int i = 0; !blocks[i].empty(); ++i) {
        //If current block is only "::", simply print it;
        if (blocks[i] == "::") cout << "::";

        //Else if next block is "::", print current block WITHOUT colon;
        else if (blocks[i+1] == "::") cout << blocks[i];

        //Else print current block with colon (if cur block isn't the last);
        else cout << blocks[i] << (!blocks[i+1].empty() ? ":" : "");
    }
}
