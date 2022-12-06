/*


 NOTES:
    - Contains 2 functions. Each one reads the data into a different map
    - Documentation gives that all info is per 100 edible grams

*/

#include <iostream>
#include <fstream>
#include <string>
#include "orderedmap.h"
#include "unorderedmap.h"

using namespace std;


orderedmap mapBuild() {
    string delS = "";                                    // voiding string
    string foodType = "";                                // description of food
    float delF = 0;                                      // voiding float
    float nutrients [38] = {};                           // floats for the nutrients

    orderedmap result;                                   // desired map

    ifstream data("data/food.csv"); // open the data file
    if (!data) {
        cout << "ERROR: Could not open data file. Check file path" << '\n';
        return result;
    }
    getline(data, delS); // pull off the first line (column headers)

    int numRows = 0;

    while (getline(data, delS)) { // temporarily store each line of data
        delS.erase(0, delS.find("\",\"")+3); //remove the category
        foodType = delS.substr(0, delS.find("\",\"")); //store the type of food for map keys
        // cout << foodType << ": ";

        for (int i = 0; i < 38; i++) { //put the remainder of the data in the temporary array of floats
            delS.erase(0, delS.find("\",\"")+2); //remove the previous nutrient
            nutrients[i] = stof(delS.substr(1, delS.find("\",\"")));
            // cout << nutrients[i] << " || ";
        }
        result.insert(foodType, nutrients);
        // cout << numRows++ << " " << foodType << endl;
        // cout << endl;
    }
    return result;
}

unorderedmap unorderedMapBuild() {
    string delS = "";                                    // voiding string
    string foodType = "";                                // description of food
    float delF = 0;                                      // voiding float
    float nutrients [38] = {};                           // floats for the nutrients

    unorderedmap result;

    ifstream data("data/food.csv"); // open the data file
    if (!data) {
        cout << "ERROR: Could not open data file. Check file path" << '\n';
        return result;
    }
    getline(data, delS); // pull off the first line (column headers)

    int numRows = 0;

    while (getline(data, delS)) { // temporarily store each line of data
        delS.erase(0, delS.find("\",\"")+3); //remove the category
        foodType = delS.substr(0, delS.find("\",\"")); //store the type of food for map keys
        // cout << foodType << ": ";

        for (int i = 0; i < 38; i++) { //put the remainder of the data in the temporary array of floats
            delS.erase(0, delS.find("\",\"")+2); //remove the previous nutrient
            // cout << " " << delS.substr(1, delS.find("\",\"")-1);
            nutrients[i] = stof(delS.substr(1, delS.find("\",\"")-1));
            // cout << nutrients[i] << " || ";
        }
        result.insert(foodType, nutrients);
        // cout << numRows++ << " " << foodType << endl;
        // cout << endl;
    }
    return result;
}