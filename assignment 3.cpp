// assignment 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BST.h"
#include"Queuet.h"
#include "citydictionary.h"
#include "Stackt.h"
using namespace std;

int main() {
    string filename;
    cout << "Enter the name of the file ";
    cin >> filename;

    CityDictionary cityDict;  
    cityDict.readFile(filename);

   
        cout << "1. Search for a City"<<endl;
        cout << "2. List All Cities"<<endl;
        cout << "3. Calculate Distance"<<endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            string cityName;
            cout << "Enter the city name to search: ";
            cin >> cityName;

            CityInfoType cityInfo;
            if (cityDict.searchCity(cityName, cityInfo)) {
                cout << "City found:\n" << cityInfo;
            }
            else {
                cout << "City not found.\n";
            }
        }
        else if (choice == 2) {
            cout << "List of all cities:\n";
            cityDict.listAllCities();
        }
        else if (choice == 3) {
            string city1, city2;
            cout << "Enter the first city name: ";
            cin >> city1;
            cout << "Enter the second city name: ";
            cin >> city2;

            CityInfoType info1, info2;
            if (cityDict.searchCity(city1, info1) && cityDict.searchCity(city2, info2)) {
                double distance = cityDict.calculateDistance(info1, info2);
                cout << "Distance between " << city1 << " and " << city2 << " is " << distance << " kilometers.\n";
            }
            else {
                cout << "One or both cities not found.\n";
            }
        }
      
     
    

    return 0;
    }


