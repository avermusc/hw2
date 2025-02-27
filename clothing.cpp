#include "clothing.h"
#include "util.h"
#include <sstream>
#include <ostream>
#include <iomanip>
#include <string>
using namespace std;

    Clothing::Clothing(const std::string name, const std::string size, const std::string brand, double price, int quantity)
        :Product("clothing", name, price, quantity), size_(size), brand_(brand){}

    Clothing::~Clothing(){}

    std::set<std::string> Clothing::keywords() const{
        set<string> output = parseStringToWords(getName());
        set<string> brand = parseStringToWords(brand_);
        output.insert(brand.begin(), brand.end());
        return output;
    }

    std::string Clothing::displayString() const{
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << getPrice();
        string output = getName() + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + oss.str() 
                        + " " + to_string(getQty()) + " left.";
        return output;
    }
    
    void Clothing::dump(std::ostream& os) const{
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << getPrice();
        string output = string("clothing\n") + getName() + "\n" + oss.str() + "\n" + to_string(getQty())
                        + "\n" + size_ + "\n" + brand_ + "\n";
        os << output;
    }