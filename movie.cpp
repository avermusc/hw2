#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

    Movie::Movie(const std::string name, const std::string genre, const std::string rating, double price, int quantity)
        :Product("movie", name, price, quantity), genre_(genre), rating_(rating){}

    Movie::~Movie(){}

    std::set<std::string> Movie::keywords() const{
        set<string> output = parseStringToWords(getName());
        output.insert(genre_);
        return output;
    }

    std::string Movie::displayString() const{
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << getPrice();
        string output = getName() + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + oss.str() 
                        + " " + to_string(getQty()) + " left.";
        return output;
    }
    
    void Movie::dump(std::ostream& os) const{
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << getPrice();
        string output = string("movie\n") + getName() + "\n" + oss.str() + "\n" + to_string(getQty())
                        + "\n" + genre_ + "\n" + rating_ + "\n";
        os << output;
    }