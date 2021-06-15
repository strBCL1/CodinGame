#include <iostream>
#include <map> 
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>
using namespace std;
#define defaultValue numeric_limits<int>::max()
map<string, pair<int, int>> mapBoundaries; //Map to store names of arrays <-> left, right boundaries: 'AA' <-> -1..2;
map<string, vector<int>> mapArrays; //Map to store names of arrays <-> its numbers: 'AA' <-> 1 2 3 4...;

//Function to get element in 'arraysName' on 'index' position;
int getElement(int index, string arraysName) {
    //Get right and left boundaries of current array;
    int leftBoundary = mapBoundaries[arraysName].first, rightBoundary = mapBoundaries[arraysName].second; 

    int sumOFArraysBoundaries = rightBoundary - leftBoundary + 1; //Get sum of current array's boundaries;
    int curIndex = sumOFArraysBoundaries - (rightBoundary - index + 1); //Get index of current element;

    return mapArrays[arraysName][curIndex]; //Return the element;
}

//Function to print the element to be processed;
void printElement (string x) {
    stack<string> s; //Create stack to perform parsing;

    for (int i = 0; i < x.size(); ++i) { //Insert spaces after brackets and digits to perform parsing using stringstream;
        if (x[i+1] == '[' || x[i] == '[' || x[i] == ']' || (i < x.size()-1 && isdigit(x[i]) && x[i+1] == ']'))
            x.insert(begin(x) + 1 + i++, 1, ' ');
    }

    //'stringstream' - var to process each element in array's string ('[', ']', numbers...);
    //'word' - auxiliary string to store each extracted element from stringstream;
    //'num' - auxiliary integer to store numbers from string (boundaries, numbers in array);
    stringstream ss(x); string word; int num;

    while (ss >> word) { //While extracting elements in string:
        if (word == "]") { //If current element is "]":
            int index = stoi(s.top()); s.pop(); s.pop(); //Get index of current array and erase it and '[' from stack;

            string arraysName = s.top(); s.pop(); //Get name of the array; erase name of the array from stack;
            index = getElement(index, arraysName); //Get element in 'arraysName' on 'index' position;

            if (s.empty()) cout << index; //If stack is empty, it means no elements left and print the sought element;
            else s.push(to_string(index)); //Else it means that there are some elements in stack, and push the element to the stack;
        }
        else s.push(word); //Else push to stack everything which is not "]";
    }
}

//Function to get left and right boundaries of the array;
void getPairs(string s) {
    //Replace '[' and ']' with ' ';
    s[s.find("]")] = ' '; 
    s[s.find("[")] = ' ';

    replace(begin(s), end(s), '.', ' '); //Replace all '.' with ' ';

    
    int leftBoundary = defaultValue, rightBoundary = defaultValue; //Initialize left and right boundaries with default values;
    string name; //Declare the name of an array;

    //Stringstream to extract single elements in array's string; 
    //'word' - auxiliary string, in which extracted elements will be stored; 
    //'num' - auxiliary integer to store numbers (indexes and elements) in array's string;
    stringstream ss(s); string word; int num;  

    while (ss >> word) { //While extracting elements from string:
        if (isalpha(word[0])) name = word; //Initialize array's name;
        else if (stringstream(word) >> num) { //If current element is a number:
            if (leftBoundary == numeric_limits<int>::max()) leftBoundary = num; //Initialize array's left boundary;
            else if (rightBoundary == numeric_limits<int>::max()) rightBoundary = num; //Initialize array's right boundary;
            else mapArrays[name].push_back(num); //Add array's numbers to its vector in map;
        }
    }
    mapBoundaries[name] = {leftBoundary, rightBoundary}; //Add array's boundaries to its name in map;
}

int main()
{
    int n; cin >> n; cin.ignore(); //Input amount of arrays to be inputted;

    for (int i = 0; i < n; ++i) { //'n' times:
        string s; getline(cin, s); //Get line of the array;        
        getPairs(s); //Create pairs: (Array's name <-> left, right boundaries) && (Array's name <-> numbers in this array);
    }
    
    string x; getline(cin, x); //Initialize and input element to be printed;
    printElement(x); //Find the element to be printed and print it;
    return 0;
}
