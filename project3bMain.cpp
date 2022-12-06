/*
 PROGRAMMING REFERENCES:
    https://cplusplus.com/reference/fstream/ifstream/ (Used for reading in data from a csv)
    https://cplusplus.com/reference/string/stof/      (Used for converting strings to floats)
    https://cplusplus.com/doc/tutorial/arrays/        (Used to remember the way to initialize arrays)
    https://stackoverflow.com/questions/66521745/eigen-dense-no-such-file-or-directory-in-visual-studio-code (Used to finally figure out how to include the external library)
    https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html (Used to set up the basic linear algebra with the external library)
    https://eigen.tuxfamily.org/dox/unsupported/classEigen_1_1NNLS.html#a7e5748cfa4db56e9605ba34b8c6e7764 (Used to setup nonnegative least squares problem solving)

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
*/

#include "extraction.h"
#include <string>
#include <Eigen/Dense>
#include <unsupported/Eigen/NNLS>

int main () {
    //read out loading message
    cout << endl << "Food databases are being loaded..." << endl;
    orderedmap map1 = mapBuild();
    unorderedmap map2 = unorderedMapBuild();
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

    // map1.print(map1.thisroot());

    //loop for user to input foods
    Eigen::Matrix<float, 7, 7> foods;
    int numFoods = 0;
    string inFood = "";

    /*while (numFoods < 7) { //USING ORDERED MAP
        getline(cin, inFood);
        float* foodData = map1.findsecond(inFood);
        if ( foodData != nullptr) { //check if the user input is an entry in the map
            foods(numFoods, 0) = *(foodData + 21);
            foods(numFoods, 1) = *(foodData + 20);
            foods(numFoods, 2) = *(foodData + 5);
            foods(numFoods, 3) = *(foodData + 4);
            foods(numFoods, 4) = *(foodData + 28);
            foods(numFoods, 5) = *(foodData + 7);
            foods(numFoods, 6) = *(foodData + 11);
            numFoods++;
        } else {
            cout << "   That food could not be found. Please try again." << endl;
        }
    }*/

    while (numFoods < 7) { //USING UNORDERED MAP
        getline(cin, inFood);
        float* foodData = map2.search(inFood);
        if ( foodData != nullptr) { //check if the user input is an entry in the map
            foods(0, numFoods) = *(foodData + 21);
            foods(1, numFoods) = *(foodData + 20);
            foods(2, numFoods) = *(foodData + 5);
            foods(3, numFoods) = *(foodData + 4);
            foods(4, numFoods) = *(foodData + 28);
            foods(5, numFoods) = *(foodData + 7);
            foods(6, numFoods) = *(foodData + 11);
            numFoods++;
        } else {
            cout << "   That food could not be found. Please try again." << endl;
        }
    }

    //perform matrix reduction to solve Ax = b (where A is the food nutrient values, b is the DRVs, and x is the amounts needed)
    Eigen::Vector<float, 7> DRVs;
    DRVs << 78, 20, 300, 275, 2300, 28, 50;
    // Eigen::VectorXf amounts = foods.colPivHouseholderQr().solve(DRVs);

    //attempt to solve with nonnegative least squares
    Eigen::NNLS nnls(foods, -1, 1e-10);
    auto amounts = nnls.solve(DRVs);

    //outpout the linear algebra setup and solution
    cout << endl << "Matrix of given food nutritional values: \n" << foods << endl;
    cout << endl << "Vector of given DRVs: \n" << DRVs << endl;
    cout << endl << "Amounts for FDA DRVS (in 100g edible): \n" << amounts << endl;

    return 0;
}