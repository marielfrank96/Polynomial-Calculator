
#include "PolyPair.hpp"

#include <iostream>
using std:: cout;
using std::endl;


//Default constructor
PolyPair::PolyPair(){
    
}

//Constructor with parameters
PolyPair::PolyPair(int coefficient, int exponent){
    
    this-> coeff = coefficient;
    this-> expon = exponent;    
}

//Destructor
PolyPair::~PolyPair(){
    
}

//Overloaded stream insertion operator
std::ostream& operator<<(std::ostream &os, const PolyPair& rhsObj){
    
    //Used to display the content of a polynomial
    //Called from linked list overloaded << operator
    
    //If exponent is zero, only display coefficient
    if(rhsObj.expon == 0){
        
        if(rhsObj.coeff > 0){
            
            os << "+" << rhsObj.coeff << "";
        }
        else
            os << rhsObj.coeff << "";
    }
    
    //If exponent is one, display x but do not display power
    else if(rhsObj.expon == 1){
        
        if(rhsObj.coeff > 0){
            
            os << "+" << rhsObj.coeff << "x ";
        }
        else
            os << rhsObj.coeff << "x ";
    }

    //Else display sign, coefficient, x, and power
    else{
    
        if(rhsObj.coeff > 0)
            os << "+" <<rhsObj.coeff << "x^" << rhsObj.expon << "";
    
        else
            os << rhsObj.coeff << "x^" << rhsObj.expon << "";
        }
    
    return os;
}

//Overloaded relational operator
bool PolyPair::operator == (const PolyPair &rhsObj){
    
    if ((coeff == rhsObj.get_coeff()) && (expon == rhsObj.get_exponent()))
        return true;
        
    else
        return false;
}

//Overloaded relational operator
bool PolyPair::operator>(const PolyPair &rhsObj){
    
    if(this->get_exponent() < rhsObj.get_exponent())
        return false;
    
    else
        return true;
}

//Overloaded relational operator
bool PolyPair::operator<(const PolyPair &rhsObj){
    
    if(this->get_exponent()> rhsObj.get_exponent())
        return false;
    else
        return true;
}


//Function to multiply two pairs
PolyPair PolyPair::multiply(PolyPair myPair){
    
    int newCoeff = (coeff * myPair.get_coeff());
    int newExpon = expon + myPair.get_exponent();
    PolyPair newPair(newCoeff, newExpon);
    
    return newPair;
}

