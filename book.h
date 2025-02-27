#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <set>
#include <string>

class Book : public Product{
public:
    Book(const std::string name, const std::string isbn, const std::string author, double price, int quantity);
            // : Product("book", name, price, quantity), isbn_(isbn), author_(author){}
    ~Book();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string isbn_;
    std::string author_;
};

#endif