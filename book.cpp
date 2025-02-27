#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

Book::Book(const std::string name, const std::string isbn, const std::string author, double price, int quantity)
    :Product("book", name, price, quantity), isbn_(isbn), author_(author){}

Book::~Book(){}

std::set<std::string> Book::keywords() const{
    set<string> output = parseStringToWords(getName());
    set<string> author = parseStringToWords(author_);
    output.insert(author.begin(), author.end());
    output.insert(isbn_);
    return output;
}

std::string Book::displayString() const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << getPrice();
    string output = getName() + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + oss.str() 
                    + " " + to_string(getQty()) + " left.\n\n\n";
    return output;
}

void Book::dump(std::ostream& os) const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << getPrice();
    string output = string("book\n") + getName() + "\n" + oss.str() + "\n" + to_string(getQty())
                    + "\n" + isbn_ + "\n" + author_ + "\n";
    os << output;
}