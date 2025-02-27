#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "user.h"
#include "util.h"
#include "product.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include <deque>
#include <cctype>




class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    void addToCart(const std::string user, Product* prod); //shoudl this take an int hitIndex? or should i just extract the product from the list of hits deoending on the hitindex provided by the user in amazon(as is currently so)
    void viewCart(const std::string user);
    void buyCart(const std::string user);

private:
    std::map<std::string, std::set<Product*>> KeyDict_;
    std::vector<Product*> prods_;
    std::map<std::string, User*> users_;
    std::map<User*, std::deque<Product*>> carts_;
};

#endif
