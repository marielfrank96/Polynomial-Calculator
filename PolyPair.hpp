
//  PolyPair.hpp

#ifndef PolyPair_hpp
#define PolyPair_hpp

#include <stdio.h>
#include<iostream>

using std::ostream;


class PolyPair {
    
    //Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream &os, const PolyPair& rhsObj);
    
private:
    
    int coeff;
    int expon;
    
public:
    
    //Default constructor
    PolyPair();
    
    //Constructor with parameters
    PolyPair(int coefficient, int exponent);
    
    //Destructor
    ~PolyPair();
    
    //Get functions to return private data members
    int get_coeff() const {return coeff;}
    int get_exponent() const {return expon;}
    
    void set_coeff(int coefficient) {coeff = coefficient;}
    
    //Overloaded relational operator
    bool operator> (const PolyPair &pp);
    
    //Overloaded relational operator
    bool operator< (const PolyPair &pp);
    
    //Overloaded relational operator
    bool operator == (const PolyPair &pp);
    
    //Multiply two pairs
    PolyPair multiply(PolyPair);
    
};

#endif /* PolyPair_hpp */
