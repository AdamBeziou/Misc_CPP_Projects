/* A program for classifying simple ordinary differential equations, ODEs */

#include <iostream> // For cin, cout, etc
#include <string> // For the equation, terms, etc.
#include <cctype> // For comparing term character's to numbers
#include <regex> // For identifying derivatives
using namespace std;

int main() {
    /* Declares variables for counting, # of terms, various properties of the equation, etc. */
    int numTerms = 0;
    int i = 0;
    int j = 0;
    int numOrder = 0;
    int numCheck = 0;
    string equation = "";
    bool linear = true;

    string term = "";
    
    cout << "Ordinary Differential Equation Classifier" << endl
         << "-----------------------------------------" << endl 
         << "Enter the number of terms in the equation (including the equal sign): "; // Prompts the user to enter the number of terms in the equation
    cin >> numTerms;

    cout << "USe 'x' for the independent variable and 'y' for the dependent."
         << "For derivative terms, write them as either dy/dx or y'," << endl 
         << "with higher order derivatives having the form d2y/dx2 or y''." << endl 
         << "Include a term's sign." << endl 
         << "Ex. dy/dx = y^2 + x has the terms +dy/dx, =, +y^2, and +x." << endl; // Declares formatting rules for entering in terms

    for (i = 0; i < numTerms; i++) {
        if (i == 0) {
            cout << endl << "Enter the first term: "; // Prompts the user to enter the first term
        }
        else {
            cout << endl << "Enter the next term: "; // Prompts the user to enter the next term
        }

        cin >> term; // Gets the term string

        /* Sets up two regular expressions for identifying derivatives in 2 different notations */
        regex derivative("(d)(.*)(y/dx)(.*)");
        regex derivative2("(y)(.*)");

        numCheck = 0; // Sets up a 'check' variable for holding counters

        if (regex_match(term.begin(), term.end(), derivative)) { // Checks if derivative is in form dy/dx
            if (isdigit(term.at(1))) { // If the second character is a digit (ex. d2y/dx2), set the check/term's order to that digit
                numCheck = term.at(1);
                numCheck %= 48;
            }
            else {
                numCheck = 1; // Else, the derivative's order is 1
            }

            if (numCheck > numOrder) { // IF the term's order is higher than the current highest order, replace the current order with the term's
                numOrder = numCheck;
            }
        }
        else if (regex_match(term.begin(), term.end(), derivative2)) { // Checks if the derivative is in the form y', y'', etc.
            for (j = 0; j < term.size(); j++) { // Counts the number of 's, which shows order
                if (term.at(j) == '\'') {
                    numCheck++;
                }
            }

            if (numCheck > numOrder) { // IF the term's order is higher than the current highest order, replace the current order with the term's
                numOrder = numCheck;
            }
        }

        numCheck = 0; // Resets the check variable

        for (j = 0; j < term.size(); j++) { // Counts how many y's are in the term
            if (term.at(j) == 'y') {
                numCheck++;
            }
        }

        if (numCheck > 1) { // If there is more than one y, the differential equation is not linear (dependent variables cannot be coefficients)
            linear = false;
        }

        equation.append(" " + term + " "); // Appends the term to the equation
    }

    cout << "The differential equation " << equation << endl; // Lists the equation
    cout << "is a "; // Begins description
    if (linear == true) {
        cout << "linear ";
    }
    else {
        cout << "non-linear ";
    }
    cout << "equation and is of order " << numOrder << "." << endl;
}