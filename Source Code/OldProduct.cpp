#pragma once
#include <iostream>
#include "Product.cpp"
#include "Tostring.cpp"
using namespace std;

class OldProduct : public Product
{
private:
    double numberOfUses;

public:
    OldProduct() : Product()
    {
        this->numberOfUses = 0;
    }
    OldProduct(int productCode, string productName, string productUnit, string expDate, double qty, double numberOfUses) : Product(productCode, productName, productUnit, expDate, qty)
    {
        setNumberOfUses(numberOfUses);
    }

    void setNumberOfUses(const double numberOfUses)
    {
        try
        {
            this->numberOfUses = DetectInvalid::invalidValue(numberOfUses);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Invalid Product Uses!");
        }
    }

    double getNumberOfUses() const{
        return numberOfUses;
    }

    void input() override{
        int numberOfUses;
        cout<<"Input Number Of Uses: ";
        cin>>numberOfUses;
        setNumberOfUses(numberOfUses);
        Product::input();
    };

    void toString() override{
        Product::toString();
        cout<<"     Number Of Uses: "<<getNumberOfUses()<<endl;
    }
};
