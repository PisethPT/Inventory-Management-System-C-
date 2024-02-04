#pragma once
#include <iostream>
#include <sstream>
#include "Product.cpp"
#include "DataInputValidation.cpp"
using namespace std;
class ProductInputOutput
{
    private:
    DataInputValidation DIV;
    Product product;
public:
    virtual void input()
    {
        int productCode;
        string productName;
        string productUnit;
        string expDate;
        double qty;

        productCode = DIV.inputInt("Input Product Code: ");
        product.setProductCode(productCode);
        productName = DIV.inputString("Input Product Name: ");
        product.setProductName(productName);
        productUnit = DIV.inputString("Input Unit: ");
        product.setProductUnit(productUnit);
        expDate = DIV.inputString("Enter Expiry Date (DD/MM/YY): ");
        product.setExpDate(expDate);
        qty = DIV.inputDouble("Input Product Quantity: ");
        product.setQty(qty);
    }
    virtual string toString()
    {
        stringstream ss;
        ss << "Product Code: " << product.getProductCode() << ", Product Name: " << product.getProductName() 
        << "\nUnit: " << product.getProductUnit() << ", Expired Date: " << product.getExpDate() << ", Quantity: " << product.getQty() << endl;
        return ss.str();
    }
};
