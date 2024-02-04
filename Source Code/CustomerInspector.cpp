#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Customer.cpp"
#include "CustomerDAO.cpp"
#include "ProductInspector.cpp"

class CustomerInspector : public CustomerDAO, public ProductInspector
{
private:
    
    vector<int> productsCode;

    Customer *findCustomerById(int customerId)
    {
        auto it = find_if(customers.begin(), customers.end(), [&](const Customer *c)
                          { return c->getCustomerId() == customerId; });
        if (it != customers.end())
        {
            return (*it);
        }
        return nullptr;
    }

    int generateOrderId()
    {
        static int orderId_static = 1;
        return orderId_static++;
    }

    vector<int> productCodes()
    {
        char addMoreOrders;
        int code;
        do
        {
            cout << "Input Product Code: ";
            cin >> code;
            productsCode.push_back(code);
            cout << "Add more orders? (Y/N): ";
            cin >> addMoreOrders;
        } while (addMoreOrders == 'Y' || addMoreOrders == 'y');

        return productsCode;
    }

public:
    vector<Customer *> customers;
    int findCustomerId(int customerId)
    {
        auto it = find_if(customers.begin(), customers.end(), [&](const Customer *c)
                          { return c->getCustomerId() == customerId; });
        if (it != customers.end())
        {
            return customerId;
        }
        return 0;
    }

    void addCustomers(Customer *customer, ProductInspector productsIn) override
    {
        customers.push_back(customer);
        placeOrder(customer->getCustomerId(), productsIn);
    }

    void placeOrder(int customerId, ProductInspector &productsIn) override
    {
        Customer *customer = findCustomerById(customerId);
        if (customer == nullptr)
        {
            cout << "Customer not found." << endl;
            return;
        }

        Order order;
        order.setOrderId(generateOrderId());

        vector<int> productList = productCodes();
        for (int productCode : productList)
        {
            Product *product = productsIn.searchProductByCode(productCode);

            if (product == nullptr)
            {
                continue;
            }

            int amount;
            cout << "Input amount of product: ";
            cin >> amount;

            if (amount <= product->getQty())
            {
                product->setQty(amount);
                productsIn.reduceInventory(productCode, amount);
                order.products.push_back(*product);
                cout << "Order code: " << order.getOrderId() << endl;
            }
        }

        if (order.products.empty())
        {
            cout << "Order placed fail." << endl;
        }
        else
        {
            customer->orders.push_back(order);
            cout << "Order placed successfully." << endl;
        }
    }

    void viewCustomerOrders(int customerId) override
    {
        Customer *customer = findCustomerById(customerId);
        if (customer == nullptr)
        {
            cout << "Customer not found." << endl;
            return;
        }

        customer->Tostring();

        for (const auto &order : customer->orders)
        {
            cout << "Order ID: " << order.getOrderId() << endl;
            cout << "------------------> Invoice <----------------------" << endl;

            for (auto product : order.products)
            {
                product.toString();
                cout << endl;
            }

            cout << endl;
        }
    }

    void viewAllCustomerOrders()
    {
        for (const auto &customer : customers)
        {
            customer->Tostring();
            cout << "----------------------" << endl;

            const auto &orders = customer->orders;
            if (orders.empty())
            {
                cout << "No orders found for this customer." << endl;
            }
            else
            {
                for (const auto &order : orders)
                {
                    cout << "Order ID: " << order.getOrderId() << endl;
                    cout << "------------------> Invoice <----------------------" << endl;

                    const auto &products = order.products;
                    if (products.empty())
                    {
                        cout << "No products found for this order." << endl;
                    }
                    else
                    {
                        for (auto product : products)
                        {
                            product.toString();
                            cout << endl;
                        }
                    }

                    cout << endl;
                }
            }

            cout << endl;
        }
    }

    // remove Customer with Product Order
    bool removeCustomers(int customerId) override
    {
        auto customerItr = find_if(customers.begin(), customers.end(), [customerId](const Customer *customer)
                                   { return customer->getCustomerId() == customerId; });

        if (customerItr != customers.end())
        {
            customers.erase(customerItr, customers.end());
            cout << "Customer with ID " << customerId << " has been removed." << endl;

            // Remove customer's product orders
            for (Customer *customer : customers)
            {
                customer->orders.clear();
                for (Order &order : customer->orders)
                {
                    order.products.clear();
                }
            }
            return true;
        }
        else
        {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
            return false;
        }
    }

    void removeProductFromOrder(int customerId, int orderId, int productCode) override
    {
        Customer *customer = findCustomerById(customerId);

        if (customer != nullptr)
        {
            Order *order = customer->findOrderById(customer, orderId);

            if (order != nullptr)
            {
                Product *product = searchProductByCode(productCode);

                if (product != nullptr)
                {
                    auto productItr = std::find_if(order->products.begin(), order->products.end(), [productCode](const Product &product)
                                                   { return product.getProductCode() == productCode; });

                    if (productItr != order->products.end())
                    {
                        order->products.erase(productItr);
                        cout << "Product with ID " << productCode << " has been removed from order " << orderId << " for customer " << customerId << "." << endl;
                    }
                    else
                    {
                        cout << "Product with ID " << productCode << " does not exist in order " << orderId << " for customer " << customerId << "." << endl;
                    }
                }
                else
                {
                    cout << "Product with ID " << productCode << " does not exist." << endl;
                }
            }
            else
            {
                cout << "Order with ID " << orderId << " does not exist for customer " << customerId << "." << endl;
            }
        }
        else
        {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
        }
    }

    void updateCustomerProduct(int customerId, int orderId, int productCode, ProductInspector productsIn) override
    {
        Customer *customer = findCustomerById(customerId);

        if (customer != nullptr)
        {
            Order *order = customer->findOrderById(customer, orderId);

            if (order != nullptr)
            {
                Product *product = productsIn.searchProductByCode(productCode);

                if (product != nullptr)
                {
                    auto productItr = std::find_if(order->products.begin(), order->products.end(), [productCode](const Product &product)
                                                   { return product.getProductCode() == productCode; });

                    if (productItr != order->products.end())
                    {
                        order->products.erase(productItr);
                        int setOrder = order->getOrderId();
                        setOrder--;
                        // Update the product information
                        placeOrder(customer->getCustomerId(), productsIn);
                        order->setOrderId(setOrder);
                    }
                }
                else
                {
                    cout << "Product with ID " << productCode << " does not exist." << endl;
                }
            }
            else
            {
                cout << "Order with ID " << orderId << " does not exist for customer " << customerId << "." << endl;
            }
        }
        else
        {
            cout << "Customer with ID " << customerId << " does not exist." << endl;
        }
    }

    bool updateCustomers(const int customerCode, const Customer *updateCustomer) override
    {
        auto it = find_if(customers.begin(), customers.end(), [customerCode](const Customer *customer)
                          { return customer->getCustomerId() == customerCode; });

        if (it != customers.end())
        {
            **it = *updateCustomer;
            cout << "Customer Updated." << endl;
            return true;
        }
        else
        {
            cout << "Customer Not Found." << endl;
            return false;
        }
    }

    Customer *searchCustomersByCode(int customerCode)
    {
        for (Customer *customer : customers)
        {
            if (customer->getCustomerId() == customerCode)
            {
                return customer;
            }
        }
        return nullptr;
    }

    void sortCustomers() override
    {
        sort(customers.begin(), customers.end(), [](const Customer *customerFirst, const Customer *customerEnd)
             { return customerFirst->getCustomerId() < customerEnd->getCustomerId(); });
    }

    void saveAllCustomers(const vector<Customer *> customers, const string &filename) override
    {
        ofstream outputFile(filename);
        if (outputFile.is_open())
        {
            for (const Customer *customer : customers)
            {
                outputFile << "==================== Invoice ====================" << endl;
                outputFile << " Customer Id: " << customer->getCustomerId() << "\t";
                outputFile << " Customer Name: " << customer->getCustomerName() << "\t";
                outputFile << " Phone Number: " << customer->getPhoneNumber() << "\t";
                outputFile << " Address: " << customer->getAddress() << endl;
                // Save other customer properties
                outputFile << "----------------------------------------" << endl;
                for (const Order order : customer->orders)
                {
                    outputFile << " Order Id: " << order.getOrderId() << endl;
                    // Save other order properties

                    for (const Product &product : order.products)
                    {
                        outputFile << " Product Code: " << product.getProductCode() << "\t";
                        outputFile << " Product Name: " << product.getProductName() << "\t";
                        outputFile << " Unit: " << product.getProductUnit() << "\t";
                        outputFile << " Expiry Date (DD/MM/YY): " << product.getExpDate() << "\t";
                        outputFile << " Quantity: " << product.getQty() << endl;
                        // Save other product properties
                    }

                    outputFile << "----------------------------------------" << endl;
                }

                outputFile << "========================================" << endl;
            }

            outputFile.close();
            cout << "All customers saved to " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    vector<Customer *> loadAllCustomers(const string &filename) override
    {
        vector<Customer *> customers;
        ifstream inputFile(filename);
        if (inputFile.is_open())
        {
            string line;

            while (getline(inputFile, line))
            {
                Customer *customer;
                stringstream ss(line);
                int customerId;
                if (ss >> customerId)
                {
                    customer->setCustomerId(customerId);
                }

                getline(inputFile, line);
                customer->setCustomerName(line);

                getline(inputFile, line);
                customer->setPhoneNumber(line);

                getline(inputFile, line);
                customer->setAddress(line);

                // Load other customer properties

                while (getline(inputFile, line) && line != "========================================")
                {
                    Order order;
                    stringstream ssOrderId(line);
                    int orderId;
                    if (ssOrderId >> orderId)
                    {
                        order.setOrderId(orderId);
                    }
                    // Load other order properties

                    while (getline(inputFile, line) && line != "----------------------------------------")
                    {
                        Product product;
                        stringstream ssProductCode(line);
                        int productCode;
                        if (ssProductCode >> productCode)
                        {
                            product.setProductCode(productCode);
                        }

                        getline(inputFile, line);
                        product.setProductName(line);

                        getline(inputFile, line);
                        product.setProductUnit(line);

                        getline(inputFile, line);
                        product.setExpDate(line);

                        stringstream ssQty(line);
                        int qty;
                        if (ssQty >> qty)
                        {
                            product.setQty(qty);
                        }

                        // Load other product properties

                        order.products.push_back(product);
                    }

                    customer->orders.push_back(order);
                }

                customers.push_back(customer);
            }

            inputFile.close();
            cout << "Customers loaded from " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for reading." << endl;
        }

        return customers;
    }

    
};
