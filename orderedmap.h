/*
NOTES:
insert(string first, float second[38])
orderedmap* search(string first)
    returns pointer to node with given key
    if nonexistent, returns pointer to would-be parent
float* findsecond(string first)
    Second is stored as a pointer to the first element in the array
    Access other indices by adding 0, 1, 2, 3..., 37 to raw pointer value
    First is internally stored as a pointer to a string
print(orderedmap* root)
    currently prints out all map's keys in order
    keys are stored in alphabetical order
*/

#pragma once
#include <string>
#include <iostream>

using namespace std;

class orderedmap {
public:
    //root node of map
    orderedmap* root;

    //number of elements in map
    int count;

    //left and right node child
    orderedmap* left;
    orderedmap* right;

    //key
    string* first;

    //value
    //index i in array accessed by adding 0,1,2,3,...,37 to raw pointer value
    float* second;

    orderedmap() : root(nullptr), count(0), left(nullptr), right(nullptr), first(nullptr), second(nullptr) {}

    orderedmap* search(string first) {

        //function to return a pointer in any need case
        //if search term exists, returns a pointer to its location in the map
        //if search term does not exist, returns a pointer to its would-be parent

        orderedmap* curr = root;

        //travel down the tree starting at root
        //stop when either search term is found or the next branch would be a nullptr

        while (*(curr->first) != first) {
            if (first < *(curr->first)) {
                if (curr->left != nullptr) {
                    curr = curr->left;
                }
                else {
                    return curr;
                }
            }
            else if (first > *(curr->first)) {
                if (curr->right != nullptr) {
                    curr = curr->right;
                }
                else {
                    return curr;
                }
            }
        }
        return curr;


    }


    void insert(string first, float second[38]) {

        //function to insert a new node into the map

            //increase node count of map by 1
        count++;

        //initialize new node with given attributes
        orderedmap* newnode = new orderedmap;

        newnode->first = new string;
        *(newnode->first) = first;

        newnode->second = new float[38]();
        //*(newnode->second) = *second;
        for (int i = 0; i < 38; i++) {
            *(newnode->second + i) = *(second + i);
        }

        //base case. Replace map root with new node if empty
        if (root == nullptr) {
            root = newnode;
            return;
        }

        //use search helper function to determine proper place in the map
        orderedmap* curr = search(first);
        if (first < *(curr->first)) {
            curr->left = newnode;
        }
        else if (first > *(curr->first)) {
            curr->right = newnode;
        }
        else {

            //if key already exists, replace second with new second
            //should never be needed but functionality is here for completeness
            count--;
            for (int i = 0; i < 38; i++) {
                *(curr->second + i) = *(second + i);
            }
        }

        //balance tree after insertion
        root = balance(root);
    }

    float* findsecond(string first) {

        //return a pointer to the second for the given first
        //return nullptr if does not exist

        orderedmap* curr = search(first);
        if (*(curr->first) == first) {
            return curr->second;
        }
        else {
            return nullptr;
        }
    }

    int findcount() {
        return count;
    }

    void print(orderedmap* root) {

        //print all keys inorder
        //keys are strings sorted alphabetically

        if (root == nullptr) {
            return;
        }
        if (root->left != nullptr) {
            print(root->left);
        }
        cout << *(root->first) << " ";

        if (root->right != nullptr) {
            print(root->right);
        }
    }

    int height(orderedmap* route) {

        //helper function to find height of a given node
        //recursively find greatest height from leaf

        int result = 0;
        if (route != nullptr) {
            int left = height(route->left);
            int right = height(route->right);
            int max = 0;
            if (left > right) {
                max = left;
            }
            else {
                max = right;
            }
            result = max + 1;
        }
        return result;
    }

    int diff(orderedmap* route) {

        //helper function to find the balance factor of a given node

        if (route == nullptr) {
            return 0;
        }
        int left = height(route->left);




        int right = height(route->right);
        int bal = left - right;

        return bal;
    }

    orderedmap* leftleft(orderedmap* parent) {
        orderedmap* temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    orderedmap* rightright(orderedmap* parent) {
        orderedmap* temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    orderedmap* rightleft(orderedmap* parent) {
        orderedmap* temp = parent->right;
        parent->right = leftleft(temp);
        return rightright(parent);
    }

    orderedmap* leftright(orderedmap* parent) {
        orderedmap* temp = parent->left;
        parent->left = rightright(temp);
        return leftleft(parent);
    }

    orderedmap* balance(orderedmap* route) {

        //helper function to balance the tree at a given node and call needed rotations

        if (route == nullptr) {
            //cout<<"Balance nullptr return nullptr"<<endl;
            return nullptr;
        }

        //route->left = balance(left);
        //route->right = balance(right);

        int bal = diff(route);

        //cout<<"Balance "<<*(route->first)<<" balfactor "<<bal<<" ";

        if (bal > 1) {
            if (diff(route->left) > 0) {
                route = leftleft(route);
            }
            else {
                route = leftright(route);
            }
        }
        else if (bal < -1) {
            if (diff(route->right) > 0) {
                route = rightleft(route);
            }
            else {
                route = rightright(route);
            }
        }

        return route;
    }

    orderedmap* thisroot() {
        return root;
    }

};
