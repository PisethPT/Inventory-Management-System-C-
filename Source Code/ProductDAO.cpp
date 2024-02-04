#pragma once
#include <iostream>
#include "Product.cpp"

using namespace std;

class ProductDAO
{
protected:

    virtual void addProducts(Product* product) = 0;
    virtual void viewProducts() = 0;
    virtual bool removeProducts(int productCode) = 0;
    virtual bool removeProducts(string productName) = 0;
    virtual bool updateProduct(const int productCode, const Product *updatedProduct) = 0;
    virtual Product* searchProductByCode(int productCode) = 0;
    virtual void sortProducts() = 0;
    virtual void stockAndSaveDataTofile() = 0;
    virtual void loadFile() = 0;
    
};

