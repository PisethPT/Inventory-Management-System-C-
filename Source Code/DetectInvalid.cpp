#pragma once
#include <iostream>
#include "DetectException.cpp"
using namespace std;

class DetectInvalid
{
public:
    static double invalidValue(double dataType){
        if (dataType > 0 )
        {
            return dataType;
        }else{
            throw DetectException();
           // return 0;
        } 
    }
    static int invalidValue(int dataType){
        if (dataType > 0 )
        {
            return dataType;
        }else{
            throw DetectException();
            return 0;
        } 
    }
    static string invalidValue(string dataType){
        if (!dataType.empty())
        {
            return dataType;
        }else{
            throw DetectException();
        } 
    }
};
