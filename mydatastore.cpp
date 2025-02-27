#include "datastore.h"
#include "mydatastore.h"
#include "user.h"
#include "util.h"
#include "product.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;





  MyDataStore::MyDataStore(){}
  MyDataStore::~MyDataStore(){
    for (std::vector<Product*>::iterator i = prods_.begin(); i!= prods_.end(); i++){
      delete *i;
    }
    for (std::map<std::string, User*>::iterator i = users_.begin(); i!= users_.end(); i++){
      delete i->second;
    }
  }

  /**
    * Adds a product to the data store
    */
  void MyDataStore::addProduct(Product* p){
    prods_.push_back(p);
    std::set<std::string> keys = p->keywords();
    for (std::set<std::string>::iterator i = keys.begin(); i!= keys.end(); i++){
        string lowKey = convToLower(*i);
        if (KeyDict_.count(lowKey) == 0){
          KeyDict_[lowKey] = std::set<Product*>();

        }
        // if (KeyDict_.find(*i) != KeyDict_.end()){
        //   KeyDict_[*i] = std::set<Product*>();
        // }
        // KeyDict_[*i].insert(p);
        KeyDict_[lowKey].insert(p);

    }
  }

  /**
    * Adds a user to the data store
    */
  void MyDataStore::addUser(User* u){
    users_[u->getName()] = u;
    carts_[u] = std::deque<Product*>();
  }

  /**
    * Performs a search of products whose keywords match the given "terms"
    *  type 0 = AND search (intersection of results for each term) while
    *  type 1 = OR search (union of results for each term)
    */
  std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::vector<Product*> hits;
    std::set<Product*> workingSet;
    bool setStart = false;
    int start = 0;
    if (terms.empty()){ // if there are no search terms
      cout << "first one" << endl;
      return hits;
    }
    // cout << "TERMS: " ;
    for (size_t i = 0; i < terms.size(); i++){
      terms[i] = convToLower(terms[i]);
          // CapitalTerms[i][0] = std::toupper(terms[i][0]);
      // for (int j = 0; j < terms[i].length(); j++){
      //     terms[i][j] = std::tolower(terms[i][j]);
      //   }
      // cout << terms[i] << ", ";
    }
    // for (std::map<std::string, std::set<Product*>>::iterator it = KeyDict_.begin(); it != KeyDict_.end(); it++){
    //   it->first =convToLower(it->first);
    // std::vector<std::string>& CapitalTerms = terms;
    // for (size_t i = 0; i < CapitalTerms.size(); i++){
    //     CapitalTerms[i][0] = std::toupper(terms[i][0]);
    // }



    ////IM PRETTY SURE THIS COUNT THING DOESNT WORK
    if ((KeyDict_.count(terms[0]) == 0)){ //first term has no matches //
      if (type == 0){ //AND
        cout << "Term:" << terms[0] << endl;
        cout << "second one" << endl;
        for (std::map<std::string, std::set<Product*>>::iterator it = KeyDict_.begin(); it != KeyDict_.end(); it++){
          cout << "Key: " << it->first << " -> ";
          for (std::set<Product*>::iterator pit = it->second.begin(); pit != it->second.end(); pit++){
            cout << (*pit)->displayString() << " | ";
          }
          cout << endl;
        }
        return hits; //exit

      }
      else{ //OR
        for (size_t i = 1; i < terms.size(); i++){ //find the first term that has a mtch
          if (KeyDict_.count(terms[i]) != 0){
            start = i + 1;
            workingSet = KeyDict_[terms[i]]; //initialize our set
            setStart = true;
            break; 
          }
          // else if(KeyDict_.count(CapitalTerms[i]) != 0){
          //   start = i + 1;
          //   workingSet = KeyDict_[CapitalTerms[i]]; //initialize our set
          //   setStart = true;
          //   break; 
          // }
        }
        if (setStart == false){
          cout << "Term:" << terms[0] << endl;
          cout << "third one" << endl;
          for (std::map<std::string, std::set<Product*>>::iterator it = KeyDict_.begin(); it != KeyDict_.end(); it++){
          cout << "Key: " << it->first << " -> ";
          for (std::set<Product*>::iterator pit = it->second.begin(); pit != it->second.end(); pit++){
            cout << (*pit)->displayString() << " | ";
          }
          cout << endl;
          }
          return hits;
        }
      }
    }
    else{ //first term has at least one match
      workingSet = KeyDict_[terms[0]];
      start = 1;
    }
    //at this point we either have a set to begin intersecting or we have returned
    for (size_t i = start; i < terms.size(); i++){
      if (type == 0){
        if (KeyDict_.count(terms[i]) == 0){
          workingSet.clear();
          break;
        }
        else{
          workingSet = setIntersection(KeyDict_[terms[i]], workingSet);
        }
      }
      else{
        if (KeyDict_.count(terms[i]) == 0){
          continue;
        }
        else{
          workingSet = setUnion(KeyDict_[terms[i]], workingSet);
        }
      }
    }//now we should have a set of hits, we just need to make it a vector
    for (std::set<Product*>::iterator it = workingSet.begin(); it != workingSet.end(); it++){
      hits.push_back(*it);
    }
    return hits;
  }

  /**
    * Reproduce the database file from the current Products and User values
    */
  void MyDataStore::dump(std::ostream& ofile){
    
    ofile << "<products>" << endl;
    for (std::vector<Product*>::iterator i = prods_.begin(); i!= prods_.end(); i++){
      (*i)->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (std::map<std::string, User*>::iterator i = users_.begin(); i!= users_.end(); i++){
      i->second->dump(ofile);
    }
    ofile << "</users>" << endl;
  }

  void MyDataStore::addToCart(const std::string user, Product* prod){
    // for (std::map<std::string, User*>::iterator i = users_.begin(); i!= users_.end(); i++){
    //   cout << "User:  " << i->second << ", " << endl;
    if (users_.find(user) != users_.end()){
      carts_[users_[user]].push_back(prod);
    }
    else{
      cout << "Invalid request!!!!" << endl;
      return;
    }
  }
  

  void MyDataStore::viewCart(const std::string user){
    if (users_.find(user) != users_.end()){ //user exists
      if (carts_[users_[user]].empty()){ //user cart is empty
        cout << "Empty cart" << endl;
        return;
      }
      else{
        for (size_t i = 0; i < carts_[users_[user]].size(); i++){ //display each item
          cout << "Item "  << (i+1) << endl << carts_[users_[user]].at(i)->displayString() << endl;
        }
      }
    }
    else{ //invalid user
      cout << "Invalid username" << endl;
      return;
    }
  }

  void MyDataStore::buyCart(const std::string user){
    if (users_.find(user) != users_.end()){ //user exists
      if (carts_[users_[user]].empty()){ //users cart is empty
        cout << "Empty cart, no items to buy" << endl;
        return;
      }
      else{
        for (std::deque<Product*>::iterator i = carts_[users_[user]].begin(); i != carts_[users_[user]].end();){
          if(((*i)->getQty() > 0) && (users_[user]->getBalance() >= (*i)->getPrice())){
            (*i)->subtractQty(1);
            users_[user]->deductAmount((*i)->getPrice());
            i = carts_[users_[user]].erase(i);
          }
          else{
            i++;
          }
        }
      }
    }
    else{
      cout << "Invalid username" << endl;
      return;
    }
  }


