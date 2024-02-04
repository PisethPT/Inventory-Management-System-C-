#include <iostream>
#include "Customer.cpp"
using namespace std;
class CustomerDAO
{
protected:
    virtual void addCustomers(Customer *customer,ProductInspector productsIn) = 0;
    virtual void placeOrder(int customerId, ProductInspector& productsIn)= 0;
    virtual void viewCustomerOrders(int customerId) = 0;
    virtual bool removeCustomers(int customerId) = 0;
    virtual void removeProductFromOrder(int customerId, int orderId, int productId) = 0;
    virtual void updateCustomerProduct(int customerId, int orderId, int productId, ProductInspector productsIn) = 0;
    virtual bool updateCustomers(const int customerCode, const Customer *customer) = 0;
    virtual Customer *searchCustomersByCode(int customerId) = 0;
    virtual void sortCustomers() = 0;
    virtual void saveAllCustomers(const vector<Customer *> customers, const string &filename) = 0;
    virtual vector<Customer*> loadAllCustomers(const string &filename) = 0;
};
