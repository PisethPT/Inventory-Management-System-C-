#pragma once
#include <iostream>
#include <sstream>
#include "DetectInvalid.cpp"
#include "DetectException.cpp"
#include "DataInputValidation.cpp"
using namespace std;

class Product 
{
private:
    int productCode;
    string productName;
    string productUnit;
    string expDate;
    double qty;
    DataInputValidation DIV;

public:
    // Contructors
    Product()
    {
        this->productCode = 0;
        this->productName = "unknow";
        this->productUnit = "unknow";
        this->expDate = "unknow";
        this->qty = 0;
    }
    Product(int productCode, string productName, string productUnit, string expDate, double qty)
    {
        setProductCode(productCode);
        setProductName(productName);
        setProductUnit(productUnit);
        setExpDate(expDate);
        setQty(qty);
    }

    // TODO: Encapsulation (Setter & Getter)
    void setProductCode(const int productCode)
    {
        try
        {
            this->productCode = DetectInvalid::invalidValue(productCode);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Invalid Product Code!");
        }
    }

    void setProductName(const string productName)
    {
        try
        {
            this->productName = DetectInvalid::invalidValue(productName);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("None Product Name!");
        }
    }

    void setProductUnit(const string productUnit)
    {
        try
        {
            this->productUnit = DetectInvalid::invalidValue(productUnit);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("None Product Unit!");
        }
    }
    void setExpDate(const string expDate)
    {
        try
        {
            this->expDate = DetectInvalid::invalidValue(expDate);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("None Exp Date!");
        }
    }
    void setQty(const double qty)
    {
        try
        {
            this->qty = DetectInvalid::invalidValue(qty);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Invalid Product Qty!");
        }
    }

    int getProductCode() const
    {
        return productCode;
    }
    string getProductName() const
    {
        return productName;
    }
    string getProductUnit() const
    {
        return productUnit;
    }
    string getExpDate() const
    {
        return expDate;
    }
    double getQty() const
    {
        return qty;
    }

    virtual void input()
    {
        int productCode;
        string productName;
        string productUnit;
        string expDate;
        double qty;

        productCode = DIV.inputInt("Input Product Code: ");
        setProductCode(productCode);
        productName = DIV.inputString("Input Product Name: ");
        setProductName(productName);
        productUnit = DIV.inputDate("Input Unit: ");
        setProductUnit(productUnit);
        expDate = DIV.inputDate("Enter Expiry Date (DD/MM/YY): ");
        setExpDate(expDate);
        qty = DIV.inputDouble("Input Product Quantity: ");
        setQty(qty);
    }

    virtual void toString()
    {
        cout << "Product Code: " << getProductCode() << endl;
        cout << "Product Name: " << getProductName() << endl;
        cout << "Unit: " << getProductUnit() << endl;
        cout << "Expired Date: " << getExpDate() << endl;
        cout << "Quantity: " << getQty() << endl;
        cout << endl;
    }
    bool readFromFile(std::istream &is)
    {
        // Deserialize the object from the input stream
        is.read(reinterpret_cast<char *>(this), sizeof(Product));
        return is.good();
    }
};
