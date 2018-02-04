/* A simple program which counts the number of word in a phrase. */

#include <iostream> // For cout, cin, etc.
#include <string> // For storing the phrase, getline, etc.
#include <cctype>
using namespace std;

int main() {
    string phrase; // Declares a string for the phrase
    int i; // Declares a variable for the for-loop
    int numWords = 0; // Declares and initializes a counter for the number of words

    cout << "Word Counter" << endl << "------------" << endl << "Enter any phrase:" << endl; // Prompts the userto enter any phrase

    getline(cin, phrase); // Reads in the line of input
    phrase.push_back(' '); // Pads the back end of the phrase with a whitespace character; allows the program to read one-letter phrases

    for (i = 1; i < phrase.size(); i++) { // For-loop which scans the entire phrase
        if (isspace(phrase.at(i)) && !isspace(phrase.at(i - 1))) { // Increments the counter if there is a space with no preceding spaces; ignores long pauses in phrase
            numWords++;
        }
        else if (i == phrase.size() - 1 && !isspace(phrase.at(i))) { // Increments the counter if there is a word or character at the end with no leading whitespace
            numWords++;
        }
    }

    cout << "This phrase has " << numWords << " word(s)."<< endl; // Outputs the number of words in the phrase

    return 0;
}