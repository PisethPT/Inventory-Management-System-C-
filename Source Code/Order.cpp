#pragma once
#include <iostream>
#include <vector>
#include "Product.cpp"
using namespace std;

class Order : public Product
{

private:
    int orderId;

public:
    vector<Product> products;

    // int orderId;
    void setOrderId(const int orderId)
    {
        try
        {
            this->orderId = DetectInvalid::invalidValue(orderId);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Invalid Invoice Number!");
        }
    }

    int getOrderId() const
    {
        return orderId;
    }

    void toString() override
    {
        Product::toString();
    }

};
