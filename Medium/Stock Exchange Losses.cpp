//Link to the puzzle: https://www.codingame.com/training/medium/stock-exchange-losses
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back 
#define ll long long
//Method 'pb' == 'push_back'; data type 'll' == 'long long';

int main()
{
    ll n, stock; cin >> n; cin.ignore(); //'n' - amount of stocks to be inputted;
    vector<ll> stockArray; //Array (vector) to store stocks;

    //Input stocks and push them to the array;
    while (cin >> stock)
        stockArray.pb(stock);

    //'minVal' - minimal value of stock, 'maxVal' - maximal value of stock;
    //'minVal' and 'maxVal' are set to the value of LAST stock by default;
    //'maxDif' (answer variable) - maximal difference of 'maxVal' and 'minVal' ('maxVal' - 'minVal'); set to 0 by default;
    ll minVal = stockArray.back(), maxVal = stockArray.back(), maxDif = 0;

    //From last stock to the very first:
    for (int i = stockArray.size()-1; i > 0; --i) {
        //If NEXT stock value is less than CURRENT 'minVal', update 'minVal';
        if (stockArray[i-1] < minVal)
            minVal = stockArray[i-1];

        //Else if NEXT stock value is greater than CURRENT STOCK value:
        else if (stockArray[i-1] > stockArray[i]) {
            maxVal = stockArray[i-1]; //Update 'maxVal';

            //Update 'maxDif' if difference ('maxVal' - 'minVal') is greater than CURRENT MAXIMAL DIFFERENCE;
            maxDif = (maxVal - minVal > maxDif) ? maxVal - minVal : maxDif;
        }
    }

    //Print '0' or answer (with minus);
    cout << ((maxDif > 0) ? "-" : "") << maxDif;

    return 0;
}
