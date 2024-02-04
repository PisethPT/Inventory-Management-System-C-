#pragma once
#include <iostream>
#include <sstream>
#include "Product.cpp"
using namespace std;
class Tostring : public Product
{
public:
    // virtual string toString()
    // {
    //     stringstream ss;
    //     ss << "Product Code: " << getProductCode() << ", Product Name: " << getProductName() << ", Unit: " << getProductUnit() << ", Expired Date: " << getExpDate() << ", Quantity: " << getQty() << endl;
    //     return ss.str();
    // }
};
