#pragma once
#include <iostream>
#include <cctype>
#include <string>
using namespace std;
class Utils
{
protected:
    string getString(string label)
    {
        string text;
        cout << label;
        getline(cin, text);
        return text;
    }
    char getChar(string label)
    {
        char text, convert;
        cout << label;
        cin >> text;
        convert = toupper(text); // convert to Uppercase <cctype>
        return convert;
    }

    int getInteger(string label)
    {
        int number;
        cout << label;
        cin >> number;
        return number;
    }

    double getDouble(string label)
    {
        double number;
        cout << label;
        cin >> number;
        return number;
    }

    bool gotoMenu(char check, string text)
    {
        while (true)
        {
            cout << text;
            cin >> check;
            if (check=='Y' || check=='y')
            {
                return true;
                break;
            }else{
                return false;
            }
        }
    }
};