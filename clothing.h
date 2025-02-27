#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <set>
#include <string>

class Clothing : public Product{
public:
    Clothing(const std::string name, const std::string size, const std::string brand, double price, int quantity);
    ~Clothing();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};

#endif