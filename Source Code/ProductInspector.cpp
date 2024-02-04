#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "ProductDAO.cpp"
#include "Product.cpp"
#include "ProductInputOutput.cpp"

using namespace std;

class ProductInspector : public ProductDAO, public ProductInputOutput
{

public:
    vector<Product *> products;
    void addProducts(Product *product) override
    {
        if (product)
        {
            products.push_back(product);
        }
        else
        {
            cout << "Invalid product. Cannot add to inventory." << endl;
        }
    }

    void viewProducts() override
    {
        if (products.empty())
        {
            cout << "No products available." << endl;
            return;
        }

        cout << "Product List:" << endl;
        cout << "-------------" << endl;

        for (const auto &productPtr : products)
        {
            productPtr->toString();
            cout << endl;
        }
    }

    bool removeProducts(int productCode) override
    {
        auto it = find_if(products.begin(), products.end(), [productCode](const Product *product)
                          { return product->getProductCode() == productCode; });

        if (it != products.end())
        {
            delete *it;
            products.erase(it);
            cout << "Removal successful." << endl;
            return true;
        }
        else
        {
            cout << "Product not found." << endl;
            return false;
        }
    }

    bool removeProducts(string productName) override
    {
        auto it = std::find_if(products.begin(), products.end(), [productName](const Product *product)
                               { return product->getProductName() == productName; });

        if (it != products.end())
        {
            delete *it;
            products.erase(it);
            cout << "Removal successful." << endl;
            return true;
        }
        else
        {
            cout << "Product not found." << endl;
            return false;
        }
    }

    // Update Products
    bool updateProduct(const int productCode, const Product *updatedProduct) override
    {
        auto it = find_if(products.begin(), products.end(), [productCode](const Product *product)
                          { return product->getProductCode() == productCode; });

        if (it != products.end())
        {
            **it = *updatedProduct;
            cout << "Product Updated." << endl;
            return true;
        }
        else
        {
            cout << "Product Not Found." << endl;
            return false;
        }
    }

    Product *searchProductByCode(int productCode) override
    {
        auto it = find_if(products.begin(), products.end(), [&](const Product *product)
                          { return product->getProductCode() == productCode; });
        if (it != products.end())
        {
            cout << endl;
            cout << "Product found." << endl;
            return *it;
        }
        else
        {
            cout << "Product: " << productCode << endl;
            throw runtime_error("Product not found");
            return nullptr;
        }
    }

    void reduceInventory(int productCode, int amountDecrease)
    {
        Product *product = searchProductByCode(productCode);

        if (product == nullptr)
        {
            cout << "Product not found." << endl;
            return;
        }

        product->setQty(product->getQty() - amountDecrease);
    }

    void sortProducts() override
    {
        std::sort(products.begin(), products.end(), [](const Product *product1, const Product *product2)
                  { return product1->getProductCode() < product2->getProductCode(); });
    }

    int findProductByCode(int productCode)
    {
        auto it = find_if(products.begin(), products.end(), [&](const Product *p)
                          { return p->getProductCode() == productCode; });
        if (it != products.end())
        {
            cout << "Find Product." << endl;
            return productCode;
        }
        else
        {
            cout << "Note Find." << endl;
            return 0;
        }
    }

    void stockAndSaveDataTofile() override
    {
        ofstream saveFile("Products.txt");
        if (saveFile.is_open())
        {
            for (const auto &product : products)
            {
                saveFile << "Product Code: " << product->getProductCode() << "\t";
                saveFile << "Product Name: " << product->getProductName() << "\t";
                saveFile << "Unit: " << product->getProductUnit() << "\t";
                saveFile << "Expire Date: " << product->getExpDate() << "\t";
                saveFile << "Quantity: " << product->getQty() << "\n";
                saveFile << "\n";
            }
            saveFile.close();
            cout << "Products saved to file successfully." << endl;
        }
        else
        {
            cout << "Error opening the file." << endl;
        }
    }

    void loadFile() override
    {
        ifstream inputFile("Products.txt");
        if (inputFile.is_open())
        {
            products.clear(); // Clear the existing products vector

            int productCode;
            string productName;
            string productUnit;
            string expDate;
            int qty;

            while (inputFile >> productCode >> productName >> productUnit >> expDate >> qty)
            {
                Product *product = new Product(productCode, productName, productUnit, expDate, qty);
                products.push_back(product);
            }

            inputFile.close();
            cout << "Products loaded from file successfully." << endl;
        }
        else
        {
            cout << "Error opening the file." << endl;
        }
    }

    void saveProduct()
    {
        ofstream outputFile("Products.txt", ios::out | ios::binary);

        if (!outputFile.is_open())
        {
            cout << "Error in creating file...\n";
            exit(1);
        }
        else
        {
            for (const auto &productPtr : products)
            {
                outputFile.write(reinterpret_cast<char *>(productPtr), sizeof(Product));
            }
            cout << "File saved successfully" << endl;
        }

        outputFile.close();
    }

    vector<Product *> loadProduct()
    {
        vector<Product *> pro;
        ifstream inputFile("Products.txt", ios::in | ios::binary);

        if (!inputFile.is_open())
        {
            cout << "Error in opening file...\n";
            exit(1);
        }

        try
        {
            while (true)
            {
                Product *product = new Product();
                if (!inputFile.read(reinterpret_cast<char *>(product), sizeof(Product)))
                {
                    // Reached end of file
                    delete product; // Clean up the dynamically allocated memory
                    break;
                }

                pro.push_back(product);
                cout << "File loaded successfully" << endl;
            }
        }
        catch (const std::exception &e)
        {
            cerr << "Exception: " << e.what() << endl;
        }
        return pro;
        inputFile.close();
    }
};
