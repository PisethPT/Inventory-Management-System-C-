#pragma once
#include <iostream>
#include <sstream>
#include "Inventory.cpp"

using namespace std;

enum Inventorys
{
    PRODUCTMANAGEMENT = 'S',
    ORDERPROCESSING = 'O'
};

class Application : public Inventory
{
private:
    Inventory inventory;
    char InventoryMenu()
    {
        system("cls");
        char opt;
        UI::setBorder(30, 2, 29, 6, " INVENTORY MANAGERMNET SYSTEM ", 220);
        UI::setColorsAttribute(7);
        cout << R"(

                                                                S. Stock Management
                                                                O. Order Processing
                                                                Q. Quit Application


    )";
        UI::setUI(51, 8);
        for (int i = 0; i < 47; i++)
            cout << (char)220;
        UI::setUI(65, 10);
        opt = getChoisOption();
        UI::setUI(50, 12);
        return opt;
    }

public:
    void Run()
    {
        // inventory.customers.customers = customers.loadAllCustomers("Customers.txt");
        inventory.products.loadProduct();
    invalid:

        char choiseInventory;
        choiseInventory = InventoryMenu();
        switch (choiseInventory)
        {
        case PRODUCTMANAGEMENT:
        {
            inventory.productOptions();
            break;
        }

        case ORDERPROCESSING:
        {
            inventory.orderOptions();
            break;
        }

        case 'Q':
        {
            exit(0);
            break;
        }
        default:
            goto invalid;
            break;
        }
    }
};
