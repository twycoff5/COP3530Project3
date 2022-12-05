#include "extraction.h"
#include <string>
#include <Eigen/Dense>
#include "orderedmap.h"

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
    while (numFoods < 7) {
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
    }

    //perform matrix reduction to solve Ax = b (where A is the food nutrient values, b is the DRVs, and x is the amounts needed)
    
    Eigen::Vector<float, 7> DRVs;
    // foods    << 1,0,0,0,0,0,0,  0,1,0,0,0,0,0,  0,0,1,0,0,0,0,  0,0,0,1,0,0,0,  0,0,0,0,1,0,0,  0,0,0,0,0,1,0,  0,0,0,0,0,0,1; //THIS IS AN EXAMPLE
    DRVs << 78, 20, 300, 275, 2300, 28, 50;
    Eigen::VectorXf amounts = foods.colPivHouseholderQr().solve(DRVs);

    //outpout the linear algebra setup and solution
    cout << "Matrix of given food nutritional values: \n" << foods << endl;
    cout << "Vector of given DRVs: \n" << DRVs << endl;
    cout << "Amounts for FDA DRVS: \n" << amounts << endl;

    return 0;
}