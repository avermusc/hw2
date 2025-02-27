#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> output;
    int start = 0;
    int rawLength = rawWords.length();

    for (int i = 0; i < rawLength; i++){
        if (ispunct(rawWords[i]) || isspace(rawWords[i])){
            if (i - start >= 2){
                string word = convToLower(rawWords.substr(start,i - start));
                
                output.insert(word);
            }
            start = i + 1;
        }
    }
    if (start < rawLength){
        string word = convToLower(rawWords.substr(start,rawLength - start));
        if (word.length() >= 2){
          output.insert(word);
        }
    }
    // cout << "BOOKDEBGUDEBGUDEBGUDEGBUG" << endl << endl;
    // for (std::set<std::string>::iterator it = output.begin(); it!= output.end(); it++){
    //   (*it) = convToLower((*it));
    // }
    // cout << "END OF DEBGUDEBGUDEBGUDEGBUG" << endl << endl;
    return output;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
