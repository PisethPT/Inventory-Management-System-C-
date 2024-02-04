#pragma once
#include <iostream>
#include "Tostring.cpp"
#include "Product.cpp"
using namespace std;
class NewProduct : public Product
{
public:
    NewProduct() : Product() {}
    NewProduct(int productCode, string productName, string productUnit, string expDate, double qty) : Product(productCode, productName, productUnit, expDate, qty) {}

    void input() override{
        Product::input();
    };
    void toString() override{
        Product::toString();
    }
};
