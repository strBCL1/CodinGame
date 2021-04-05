#include <iostream>
#include <string>
#include <vector>
using namespace std;


//Class to encrypt/decrypt the messages;
class Solution {
private:
    //Vector to store 3 rotors from input;
    vector<string> rotors;

    //'message' - message to be encrypted/decrypted;
    //'operation' - operation to be performed on 'message' (encryption or decryption);
    //'alphabet' - all letters of english alphabet, which will be used in Caesar shifting and Rotors;
    string message, operation, alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Caesar shift (how many letters the char is moved);
    int shift;
     
public:
    //Input 'operation', 'shift', 'rotors' and 'message';
    void getInput() {
        getline(cin, operation); 
        cin >> shift; cin.ignore();
      
        rotors.resize(3);
        for (int i = 0; i < 3; i++) 
            getline(cin, rotors[i]);

        getline(cin, message);
    }
  
    //Determine what to do: encode or decode the message;
    void operationToPerform () {
        (operation == "ENCODE") ? performEncoding() : performDecoding();
    }

    //Function to perform encoding on message:
    void performEncoding () {
        //Perform shifting on message;
        doCaesarShift();        

        //Pass the message through 3 Rotors (from first to last);
        for (int i = 0; i < 3; ++i) {
            doRotor(rotors[i]); 
        }
    }
  
    //Function to perform decoding on the message:
    void performDecoding () {
        //Pass the message through 3 Rotors (from last to first - backwards);
        for (int i = 2; i >= 0; --i) {
            doRotor(rotors[i]);
        }

        //Perform shifting on message;
        doCaesarShift();
    }
    
    //Function to perform Caesar shift:
    void doCaesarShift () {
        //For each letter in message:
        for (int i = 0; i < message.size(); ++i) {
            //Get new position of current letter in alphabet;
            int newAlphabetPos = (operation == "ENCODE") ? ((alphabet.find(message[i]) + i + shift) % 26) : (alphabet.find(message[i]) - (i % 26) - shift);

            //If we need to decode the message, and 'newAlphabetPos' is < 0, it means we need to get the new letter of alphabet from alphabet's END (LAST POSITION);
            if (operation == "DECODE" && newAlphabetPos < 0) 
                newAlphabetPos = (26 + (newAlphabetPos % 26)) % 26;

            //Replace current char in message by new letter from alphabet;
            message[i] = alphabet[newAlphabetPos];
        }
    }

    //Function to perform encoding/decoding on message, using Current Rotor:
    void doRotor (string curRotor) {
        //For each letter in message:
        for (int i = 0; i < message.size(); ++i) {
            //If we need to encode the message, replace current char by letter on 'message[i]' position from ALPHABET, else: from Rotor;
            message[i] = (operation == "ENCODE") ? curRotor[alphabet.find(message[i])] : alphabet[curRotor.find(message[i])]; 
        }
    }
    
    //Print the answer (encoded/decoded) message;
    void printAnswer() {
        cout << message;
    }
};

int main()
{
    //Object of 'Solution' class to handle encoding/decoding process;
    Solution g;

    //Handling the encryption/decryption:
    g.getInput();
    g.operationToPerform();
    g.printAnswer();
    
    return 0;
}
