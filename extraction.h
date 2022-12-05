/*
 PROGRAMMING REFERENCES:
    https://cplusplus.com/reference/fstream/ifstream/ (Used for reading in data from a csv)
    https://cplusplus.com/reference/string/stof/      (Used for converting strings to floats)
    https://cplusplus.com/doc/tutorial/arrays/        (Used to remember the way to initialize arrays)
    https://stackoverflow.com/questions/66521745/eigen-dense-no-such-file-or-directory-in-visual-studio-code (Used to finally figure out how to include the external library)
    https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html (Used to set up the basic linear algebra with the external library)

 DATA REFERENCES:
    https://www.fda.gov/media/99059/download (Daily reccomended values of macronutrients from the FDA)
        Fat:         78g
        Sat Fat:     20g
        Cholesterol: 300mg
        Carbs:       275g
        Sodium:      2300mg
        Fiber:       28g
        Protein:     50g
        Added Sugar: 50g*      
        *(Neglecting since only total sugar is tracked in the source)
    https://think.cs.vt.edu/corgis/csv/ingredients/ (CSV form of the data from the USDA)
    https://www.ars.usda.gov/ARSUserFiles/80400530/pdf/fndds/FNDDS_2019_2020_factsheet.pdf (Information about the raw data source)

 ORDER OF DATA: 1 Category, 2 Description, 3 Database Number, 4 Alpha Carotene, 5 Beta Carotene, 6 Beta Cryptoxanthin, 7 Carbohydrate, 8 Cholesterol, 9 Choline, 10 Fiber,
                11 Lutein and Zeaxanthin, 12 Lycopene, 13 Niacin, 14 Protein, 15 Retinol, 16 Riboflavin, 17 Selenium, 18 Total Sugar, 19 Thiamin, 20 Water,
                21 Monosaturated Fat, 22 Polysaturated Fat, 23 Saturated Fat, 24 Total Lipid, 25 Calcium, 26 Copper, 27 Iron, 28 Magnesium, 29 Phosphorus, 30 Potassium,
                31 Sodium, 32 Zinc, 33 Vitamin A, 34 Vitamin B12, 35 Vitamin B6, 36 Vitamin C, 37 Vitamin E, 38 Vitamin K

                => NEED: 2 (desc), 7 (carbohydrates), 8 (cholesterol), 10 (fiber), 14 (protein), 23 (saturated fat), 24 (fat), 31 (sodium)

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
        delS.erase(0, delS.find("\",\"")+2); //remove the category
        foodType = delS.substr(0, delS.find("\",\"")); //store the type of food for map keys
        // cout << foodType << ": ";

        for (int i = 0; i < 38; i++) { //put the remainder of the data in the temporary array of floats
            delS.erase(0, delS.find("\",\"")+2); //remove the previous nutrient
            nutrients[i] = stof(delS.substr(1, delS.find("\",\"")));
            // cout << nutrients[i] << " || ";
        }
        cout << foodType << " ";
        result.insert(foodType, nutrients);
        cout << numRows++ << " " << foodType << endl;
        // cout << endl;
    }
    return result;
}