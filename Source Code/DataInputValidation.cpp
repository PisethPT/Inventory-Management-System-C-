#pragma once
#include <iostream>

using namespace std;

class DataInputValidation {
private:
bool validateInt(int num){
    if(cin.fail() || num > 100000){
        return false;
    }
    return true;
}

bool validateDoublenum(double num){
    if(cin.fail() || num > 100000){
        return false;
    }
    return true;
}

bool validateString(string strings){
    if (strings.length() > 100) {
        return false;
  }

    for(int i = 0;i<strings.length();i++){
        if(!(strings[i] >= 65 && strings[i] <= 122)) {
            return false;
        }
    }
    return true;
}

bool validateDate(string strings){
    if (strings.length() > 100) {
        return false;
  }
    return true;
}
public:

int inputInt(string text){
    int num;
    while(true){
        cout << text;
        cin.ignore();
        cin>>num;
        if(!validateInt(num)){
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Error: Invalid Input Int" << endl;
        }else{
            return num;
        }
    }
}

double inputDouble(string text){
    double doubles;
    while(true){
        cout << text;
        cin.ignore();
        cin>>doubles;
        if(!validateDoublenum(doubles)){
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Error: Invalid Input Double" << endl;
        }else{
            return doubles;
        }
    }
}

string inputString(string text){
    string strings;
    while (true)
    {
       cout << text;
       cin>> strings;
       if(!validateString(strings)){
        cout << "Error: Invalid/max letter reached" << endl;
       }else{
        return strings;
       }
    }
    
}
string inputDate(string text){
    string strings;
    while (true)
    {
       cout << text;
       cin>> strings;
       if(!validateDate(strings)){
        cout << "Error: Invalid/max letter reached" << endl;
       }else{
        return strings;
       }
    }
    
}


};
