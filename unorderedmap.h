/*
 NOTES:
    -Uses as an array of size [7083] to to store each food from the database. Each individual slot of the array contains a pointer to an array of the data for that specific food
    -See main documentation for a reference of the slots in data
    -Uses the powers of 31 hash function as a basis for modulo to assign slots (e.g. s[i]*31^i % 7083)
    -Uses linear chaining as a matter of simplicity

*/

#pragma once
#include <string>
#include <iostream>

using namespace std;

class unorderedmap {
    public:
        void insert(string food, float nutrients[38]); //adds nutrients for a food to the hash table
        float* search(string food);                    //returns the nutrients* or nullptr if the food is not in the table
    private:
        float* foodNutrients[7083] = {nullptr};            //nutrient data stored by the hash table
        string foodNames[7083] = {""};                 //names of the foods stored at each index
        int hash(string food);                         //hashes the key to an index in the nutrient array
};


//FUNCTION DEFINITIONS

int unorderedmap::hash(string food) { //uses powers of 31 to determine an index for the key
    int result = 0;
    for (int i = 0; i < food.length(); i++) {
        result += food[i]*31^i;
    }
    return result % 7083;
}

float* unorderedmap::search(string food) { //uses linear probing to find the nutrient data for a food; returns nullptr if the food DNE
    int hashIndex = hash(food);
    cout << " hasheds ";

    if (foodNutrients[hashIndex] == nullptr) { //check is nothing is at the index
        return nullptr;
    } else if (foodNames[hashIndex] == food) { //check if the index contains the food
        cout << " opens ";
        return foodNutrients[hashIndex];
    } else { //linearly probe for the food
        cout << " closeds ";
        int probeIndex = hashIndex +1;
        while (hashIndex != probeIndex) { //could check every index once
            // cout << hashIndex -probeIndex << " ";
            if(probeIndex > 7082) { //gaurd from exceeding bounds on first iteration
                probeIndex = 7082;
            }
            if (foodNames[probeIndex] == food) { //check if the index contains the food
                return foodNutrients[probeIndex];
            } else { //move the probe otherwise
                probeIndex++;
                if(probeIndex > 7082) { //move to the top of the hash table if we reach the bottom
                        probeIndex = 0;
                 }
            }
        }
        return nullptr; //return null if no index has the food
    }
}

void unorderedmap::insert(string food, float nutrients[38]) {
    cout << " searching ";
    if (search(food) == nullptr) { //check that the food is not already in the hash table
        cout << " hashing ";
        int hashIndex = hash(food);
        cout << " " << hashIndex << " " << food << " ";

        if (foodNames[hashIndex] == "") { //if slot is open, add name and nutrients to table
            foodNames[hashIndex] = food;
            foodNutrients[hashIndex] = nutrients;
            cout << " open ";
        } else {
            cout << " closed ";
            int probeIndex = hashIndex +1;
            while (hashIndex != probeIndex) { //could check every index once
                // cout << hashIndex - probeIndex << " ";
                if(probeIndex > 7082) { //gaurd from exceeding boundaries on first run
                    probeIndex = 7082;
                }
                if (foodNames[probeIndex] == "") { //check if the index is taken and add data
                    foodNames[probeIndex] = food;
                    foodNutrients[probeIndex] = nutrients;
                    return;
                } else { //move the probe otherwise
                    probeIndex++;
                    if(probeIndex > 7082) { //move to the top of the hash table if we reach the bottom
                        probeIndex = 0;
                    }
                }
            }
        }
    }
    return;
}