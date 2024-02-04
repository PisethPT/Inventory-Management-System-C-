#pragma once
#include <iostream>
#include <exception>
using namespace std;
class DetectException :public exception
{
public:
    virtual const char* what() const throw(){
        return "";
    }
    virtual const string commentException(string comments ) const throw(){
        return comments;
    };
};

