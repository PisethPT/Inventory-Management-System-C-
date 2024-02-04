#pragma once
#include <iostream>
#include <vector>
#include "DetectInvalid.cpp"
#include "DetectException.cpp"
#include "DataInputValidation.cpp"
#include "Order.cpp"
using namespace std;
class Customer 
{
private:
    int customerId;
    string customerName;
    string phoneNumber;
    string address;

    DataInputValidation DIV;

public:
    vector<Order> orders;
    Customer()
    {
        customerId = 0;
        customerName = "unknow";
        phoneNumber = "unknow";
        address = "unknow";
    }
    Customer(int customerId, string customerName, string phoneNumber, string address)
    {
        setCustomerId(customerId);
        setCustomerName(customerName);
        setPhoneNumber(phoneNumber);
        setAddress(address);
    }

    // Setter, Getter Methods

    void setCustomerId(const int customerId)
    {
        try
        {
            this->customerId = DetectInvalid::invalidValue(customerId);
        }
        catch (DetectException e)
        {
            cout << e.commentException("Customer Id: Null!") << '\n';
        }
    }
    void setCustomerName(const string customerName)
    {
        try
        {
            this->customerName = DetectInvalid::invalidValue(customerName);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Customer: Null!") << '\n';
        }
    }

    void setPhoneNumber(const string phoneNumber)
    {
        try
        {
            this->phoneNumber = DetectInvalid::invalidValue(phoneNumber);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Phone Number: Null!") << '\n';
        }
    }

    Order *findOrderById(Customer *customer, int orderId)
    {
        for (Order &order : customer->orders)
        {
            if (order.getOrderId() == orderId)
            {
                return &order;
            }
        }
        return nullptr;
    }

    int findOrderId(vector<Customer *> customers, int orderId)
    {
        for (auto customer : customers)
        {
            for (Order &order : customer->orders)
            {
                if (order.getOrderId() == orderId)
                {
                    return orderId;
                }
            }
        }

        return 0;
    }

    void setAddress(const string address)
    {
        try
        {
            this->address = DetectInvalid::invalidValue(address);
        }
        catch (DetectException &e)
        {
            cout << e.commentException("Address: Null!") << '\n';
        }
    }

    int getCustomerId() const
    {
        return customerId;
    }
    string getCustomerName() const
    {
        return customerName;
    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }

    string getAddress() const
    {
        return address;
    }

    virtual void inputCustomer()
    {
        int customerId;
        string customerName;
        string phoneNumber;
        string address;

        customerId = DIV.inputInt("Input Customer Id: ");
        setCustomerId(customerId);
        customerName = DIV.inputString("Input Customer Name: ");
        setCustomerName(customerName);
        phoneNumber = DIV.inputDate("Input Phone Number: ");
        setPhoneNumber(phoneNumber);
        address = DIV.inputDate("Input Address: ");
        setAddress(address);
    }

    virtual void Tostring()
    {
        cout << "Customer Id: " << getCustomerId() << endl;
        cout << "Customer Name: " << getCustomerName() << endl;
        cout << "Phone Number: " << getPhoneNumber() << endl;
        cout << "Address: " << getAddress() << endl;
    }
};
