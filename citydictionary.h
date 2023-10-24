#include <string>
#include "BST.h" 
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

const double PI = 3.14159265358979323846;

struct CityInfo {
    string cityName;
    double latitude;
    double longitude;
    string country;
    CityInfo() : cityName(""), latitude(0.0), longitude(0.0), country("") {}
    CityInfo(const CityInfo& other) : cityName(other.cityName), latitude(other.latitude), longitude(other.longitude), country(other.country) {}
    friend std::ostream& operator<<(std::ostream& os, const CityInfo& data) {
        os << "City Name: " << data.cityName << endl;
        os << "Latitude: " << data.latitude << endl;
        os << "Longitude: " << data.longitude << endl;
        os << "Country: " << data.country << endl;
        return os;
    }
};

  
    typedef CityInfo CityInfoType;

 class CityDictionary {
    private:
      
        BST<string, CityInfoType> Dictionary;

    public:
        CityDictionary() {}
        void readFile(const string& filename) {
            ifstream file(filename);
            if (!file.is_open()) {
                cerr << "Could not open file" << filename << endl;
                return;
            }

            CityInfoType cityInfo;
            string line;

            while (getline(file, line)) {
                stringstream ss(line);
                int cityNumber;
                string cityName, latStr, lonStr, country;
                ss >> cityNumber;
                ss >> ws;
                getline(ss, cityName, '\t');
                ss >> latStr;
                ss >> lonStr;
                ss >> ws;
                getline(ss, country);
                cityInfo.latitude = Coordinatecalc(latStr);
                cityInfo.longitude = Coordinatecalc(lonStr);
                cityInfo.cityName = cityName;
                cityInfo.country = country;
                if (cityInfo.latitude != 0.0 || cityInfo.longitude != 0.0) {
                    Dictionary.insert(cityName, cityInfo);
                }
            }
            file.close();
        }


        double Coordinatecalc(const string& coordStr) {
            double coordinate = 0.0;
            size_t posDegree = coordStr.find('°');
            size_t posDirection = coordStr.find_first_of("NSWE");
            if (posDegree != string::npos && posDirection != string::npos) {
                string degreesStr = coordStr.substr(0, posDegree);
                string minutesStr = coordStr.substr(posDegree + 1, posDirection - posDegree - 1);
                int degrees = stoi(degreesStr);
                int minutes = stoi(minutesStr);
                coordinate = static_cast<double>(degrees) + static_cast<double>(minutes) / 60.0;
                if (coordStr[posDirection] == 'S' || coordStr[posDirection] == 'W') {
                    coordinate = -coordinate;
                }
            }
            return coordinate;
        }






        bool searchCity(const string& cityName, CityInfoType& result) {
            return Dictionary.retrieve(cityName, result);
        }

      
        void listAllCities() {
            Dictionary.traverse();
        }


        double calculateDistance(const CityInfoType& city1, const CityInfoType& city2) {
            double degLat = Radians(city2.latitude, 'N') - Radians(city1.latitude, 'N');
            double degLon = Radians(city2.longitude, 'E') - Radians(city1.longitude, 'E');
            double a = sin(degLat / 2) * sin(degLat / 2) + cos(Radians(city1.latitude, 'N')) * cos(Radians(city2.latitude, 'N')) * sin(degLon / 2) * sin(degLon / 2);
            double c = 2 * atan2(sqrt(a), sqrt(1 - a));
            const double radius = 6371.0; 
            return radius * c;
        }

    private:
    
        double Radians(double degrees, char direction) {
            double decimalDegrees = degrees / 1.0; 
            if (direction == 'S' || direction == 'W') {
                decimalDegrees = -decimalDegrees;
            }
            return decimalDegrees * PI / 180.0;
        }
    };
