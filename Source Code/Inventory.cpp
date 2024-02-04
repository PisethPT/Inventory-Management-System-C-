#pragma once
#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>
#include "Utils.cpp"
#include "UI.cpp"
#include "OldProduct.cpp"
#include "NewProduct.cpp"
#include "ProductInspector.cpp"
#include "Product.cpp"
#include "Customer.cpp"
#include "CustomerInspector.cpp"
#include "DataInputValidation.cpp"

using namespace std;

enum ProductOptions
{
    ADDPRODUCT = 'A',
    DISPLAYPRODUCT = 'D',
    SEARCHPRODCUT = 'S',
    REMOVEBYCODE = 'R',
    REMOVEBYNAME = 'N',
    UPDATEPRODUCT = 'U',
    SORTPRODUCT = 'I',
    NEWPRODUCT = 'W',
    OLDPRODUCT = 'O'
};
enum OrderOptions
{
    ADDCUSTOMER = 'A',
    VIEWBILLS = 'V',
    DELETECUSTOMER = 'D',
    REMOVEPRODUCTORDER = 'R',
    UPDATECUSTOMER = 'U',
    SEARCHCUSTOMER = 'S',
    SORTCUSTOMER = 'I',
    SAVECUSTOMERTOFILE = 'F'
};

class Inventory : public UI, public Utils, public DataInputValidation
{
private:
    char StockMenu()
    {
        system("cls");
        char opt;
        UI::setBorder(30, 2, 29, 6, " INVENTORY MANAGERMNET SYSTEM ", 220);
        UI::setColorsAttribute(7);
        cout << R"(
                                    [ PRODUCT MANAGE ]

                                                    (A)- Add Products to Stock & save Data to file
                                                    (D)- Display Current Stock 
                                                    (S)- Search Item in Stock
                                                    (R)- Remove Item in Stock
                                                    (U)- Update Item in Stock
                                                    (I)- Sort Item
                                                    (O)- Goto Order Manage
                                                    (Q)- Quit Application


    )";
        UI::setUI(51, 13);
        for (int i = 0; i < 47; i++)
            cout << (char)220;
        UI::setUI(65, 15);
        opt = getChoisOption();
        UI::setUI(50, 17);
        cout << opt;
        return opt;
    }

    char addProduct()
    {
        system("cls");
        char opt;
        UI::setBorder(30, 2, 29, 6, " INVENTORY MANAGERMNET SYSTEM ", 220);
        UI::setColorsAttribute(7);
        cout << R"(

                                                    (W)- Add New Product
                                                    (O)- Add Old Product
                                                    (Q)- Quit Application


    )";
        UI::setUI(51, 12 - 4);
        for (int i = 0; i < 47; i++)
            cout << (char)220;
        UI::setUI(65, 14 - 4);
        opt = getChoisOption();
        UI::setUI(50, 16 - 4);
        cout << opt;
        return opt;
    }

    char OrderMenu()
    {
        system("cls");
        char opt;
        UI::setBorder(30, 2, 29, 6, " INVENTORY MANAGERMNET SYSTEM ", 220);
        UI::setColorsAttribute(7);
        cout << R"(
                                    [ ORDER MANAGE ]

                                                    (A)- Add Customer and  Products Order
                                                    (V)- View Bills
                                                    (D)- Delete Customer Cancel Order
                                                    (R)- Remove Product From Order
                                                    (U)- Update and Generate Bill(Can only Generate a Bill for one Item purchased)
                                                    (S)- Search order
                                                    (I)- Sort orders
                                                    (P)- Goto Product Manage
                                                    (F)- Save Customer To File
                                                    (Q)- Quit Application


    )";
        UI::setUI(51, 15);
        for (int i = 0; i < 47; i++)
            cout << (char)220;
        UI::setUI(65, 17);
        opt = getChoisOption();
        UI::setUI(50, 19);
        cout << opt;
        return opt;
    }

protected:
    char getChoisOption()
    {
        char option = Utils::getChar("Chois Options: ");
        return option;
    }

public:
    ProductInspector products;
    CustomerInspector customers;
    Customer customer;
    void productOptions()
    {
        //  products.loadFile();
    again:
        char opt;
        int check;
        bool isTrue;
        opt = StockMenu();
        switch (opt)
        {
        case ADDPRODUCT:
        {
        invalid:
            // system("cls");
            char add;
            add = addProduct();
            switch (add)
            {
            case NEWPRODUCT:
            {
                do
                {
                    system("cls");
                    auto newProduct = make_unique<NewProduct>();
                    newProduct->input();
                    products.addProducts(newProduct.release());
                    isTrue = Utils::gotoMenu(check, "Add More Products (Y/N): ");
                } while (isTrue);

                //  products.stockAndSaveDataTofile();
                products.saveProduct();
                goto again;
                break;
            }
            case OLDPRODUCT:
            {
                do
                {
                    system("cls");
                    auto oldProduct = make_unique<OldProduct>();
                    oldProduct->input();
                    products.addProducts(oldProduct.release());
                    isTrue = Utils::gotoMenu(check, "Add More Products (Y/N): ");
                } while (isTrue);

                // products.stockAndSaveDataTofile();
                products.saveProduct();
                goto again;
                break;
            }

            default:
                goto invalid;
                break;
            }
            break;
        }
        case DISPLAYPRODUCT:
        {
            while (true)
            {
                system("cls");
                products.viewProducts();

                cout << endl;
                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case SEARCHPRODCUT:
        {
            while (true)
            {
                int productCode;
                system("cls");
                productCode = DataInputValidation::inputInt("Input Product Code For Search: ");

                try
                {
                    Product *foundProduct = products.searchProductByCode(productCode);
                    foundProduct->toString();
                    cout << endl;
                }
                catch (const runtime_error &e)
                {
                    cout << e.what() << endl;
                }

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case REMOVEBYCODE:
        {
            while (true)
            {
                system("cls");
                int productCode;
                cout << "Input Code for Remove: ";
                cin >> productCode;
                products.removeProducts(productCode);
                system("cls");
                products.viewProducts();

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case REMOVEBYNAME:
        {
            while (true)
            {
                system("cls");
                string productName;
                cout << "Input Product Name for Remove: ";
                cin >> productName;
                products.removeProducts(productName);
                system("cls");
                products.viewProducts();

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case UPDATEPRODUCT:
        {
            while (true)
            {
                system("cls");
                int productCode, productTrue = 0;
                productCode = DataInputValidation::inputInt("Input Product Code For Update: ");
                productTrue = products.findProductByCode(productCode);

                if (productTrue != 0)
                {
                    auto updateProduct = make_unique<NewProduct>();
                    updateProduct->input();
                    products.updateProduct(productCode, updateProduct.get());
                    system("cls");
                    products.viewProducts();
                }
                else
                {
                    cout << "Product Code Not Found!" << endl;
                }

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case SORTPRODUCT:
        {
            while (true)
            {
                system("cls");

                cout << "Product List After Sort >----------------" << endl;
                products.sortProducts();
                products.viewProducts();

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case 'Q':
        {
            exit(0);
        }
        case 'O':
        {
            system("cls");
            orderOptions();
            break;
        }
        default:
            goto again;
            break;
        }
    }

    void orderOptions()
    {
    again:
        char opt;
        int check;
        bool isTrue;
        opt = OrderMenu();
        switch (opt)
        {
        case ADDCUSTOMER:
        {
            do
            {
                system("cls");
                auto cus = make_unique<Customer>();
                cus->inputCustomer();
                customers.addCustomers(cus.release(), products);
                isTrue = Utils::gotoMenu(check, "Add More Customer (Y/N): ");
            } while (isTrue);
            goto again;
            break;
        }
        case VIEWBILLS:
        {
            system("cls");
            int customerId;
            bool isTrue = true;

            while (isTrue)
            {
                customerId = DataInputValidation::inputInt("Input Customer Id: ");
                int customerIndex = customers.findCustomerId(customerId);

                if (customerIndex != -1)
                {
                    customers.viewCustomerOrders(customerId);
                }
                else
                {
                    cout << "Customer Id Not Found!" << endl;
                }

                cout << endl;
                isTrue = Utils::gotoMenu(check, "Please Press Key (Y/y) to Find Again: ");
            }
            goto again;
            break;
        }
        case DELETECUSTOMER:
        {
            int customerId;
            do
            {
                system("cls");
                customerId = DataInputValidation::inputInt("Input Customer Id: ");
                customers.removeCustomers(customerId);
                isTrue = Utils::gotoMenu(check, "Add More Customer (Y/N): ");
            } while (isTrue);
            goto again;
            break;
        }
        case REMOVEPRODUCTORDER:
        {
            system("cls");
            int customerId, orderId, productCode;
            bool isValid = false;

            while (!isValid)
            {
                customerId = DataInputValidation::inputInt("Input Customer Id For Update: ");
                customers.findCustomerId(customerId);
                if (customers.findCustomerId(customerId) != 0)
                {
                    orderId = DataInputValidation::inputInt("Input Order Id For Update: ");
                    if (customer.findOrderId(customers.customers, orderId) != 0)
                    {
                        productCode = DataInputValidation::inputInt("Input Product Code For Update: ");
                        if (products.findProductByCode(productCode) != 0)
                        {
                            customers.removeProductFromOrder(customerId, orderId, productCode);
                            isValid = true; // Set isValid to true to exit the loop
                        }
                        else
                        {
                            cout << "Product Code Not Found!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Order Id Not Found!" << endl;
                    }
                }
                else
                {
                    cout << "Customer Not Found!" << endl;
                }
            }
            goto again;
            break;
        }
        case UPDATECUSTOMER:
        {
            system("cls");
            int customerId, orderId, productCode;
            bool isValid = false;

            while (!isValid)
            {
                customerId = DataInputValidation::inputInt("Input Customer Id For Update: ");
                customers.findCustomerId(customerId);
                if (customers.findCustomerId(customerId) != 0)
                {
                    orderId = DataInputValidation::inputInt("Input Order Id For Update: ");
                    if (customer.findOrderId(customers.customers, orderId) != 0)
                    {
                        productCode = DataInputValidation::inputInt("Input Product Code For Update: ");
                        if (products.findProductByCode(productCode) != 0)
                        {
                            customers.updateCustomerProduct(customerId, orderId, productCode, products);
                            isValid = true; // Set isValid to true to exit the loop
                        }
                        else
                        {
                            cout << "Product Code Not Found!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Order Id Not Found!" << endl;
                    }
                }
                else
                {
                    cout << "Customer Not Found!" << endl;
                }
            }
            goto again;
            break;
        }
        case SEARCHCUSTOMER:
        {
            system("cls");
            int customerCode;
            customerCode = DataInputValidation::inputInt("Enter the customer code: ");
            Customer *foundCustomer = customers.searchCustomersByCode(customerCode);

            if (foundCustomer != nullptr)
            {
                foundCustomer->Tostring();
                cout << endl;
            }
            else
            {
                cout << "Customer not found." << endl;
            }

            cout << endl;
            bool gotoMenu = Utils::gotoMenu(check, "Please press Y/y to search again: ");
            if (gotoMenu)
            {
                goto again;
                break;
            }
            break;
        }
        case SORTCUSTOMER:
        {
            while (true)
            {
                system("cls");

                cout << "Customer List After Sort >----------------" << endl;
                customers.sortCustomers();
                customers.viewAllCustomerOrders();

                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
        }
        case SAVECUSTOMERTOFILE:
        {
            while (true)
            {
                system("cls");
                customers.saveAllCustomers(customers.customers, "Customers.txt");
                bool goToMenu = Utils::gotoMenu(check, "Please Press Key (Y/y) to Menu: ");

                if (goToMenu)
                {
                    goto again;
                    break;
                }
            }
            break;
        }
        case 'Q':
        {
            exit(0);
            break;
        }
        case 'P':
        {
            system("cls");
            productOptions();
            break;
        }
        default:

            break;
        }
    }
};
