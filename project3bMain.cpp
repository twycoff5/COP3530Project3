#include "extraction.h"
#include <string>

int main () {
    //read out loading message
    cout << endl << "Food databases are being loaded..." << endl;
    mapBuild();
    unorderedMapBuild();
    cout << "Food databases are loaded!" << endl;

    //read out purpose / instructions
    cout << endl << "================================================================================" << endl;
    cout <<         "                             Diet Nutrient Analyzer                             " << endl;
    cout <<         "    The following program finds the proper balance of 7 foods to meet FDA daily " << endl;
    cout <<         "recommended values (DRVs) for adults. DRVs for key macronutrients are summarized" << endl;
    cout <<         "below: " << endl;
    cout << endl << "           Fat:           78g            Sodium:        2300mg";
    cout << endl << "           Saturated Fat: 20g            Fiber:         28g";
    cout << endl << "           Cholesterol:   300mg          Protein:       50g";
    cout << endl << "           Carbohydrates: 275g";
    cout << endl << "================================================================================" << endl;
    cout << endl << "Please enter 7 foods below: " << endl;

    //loop for user to input foods
    int numFoods = 0;
    string inFood = "";
    while (numFoods < 7) {
        getline(cin, inFood);
        if ( 1 == 1) { //check if the user input is an entry in the map
            //add nutrient info for that food to the matrix
            numFoods++;
        } else {
            cout << "   That food could not be found. Please try again." << endl;
        }
    }


    return 0;
}