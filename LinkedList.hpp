
#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>

#include "PolyPair.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

//Node template class definition
template <class T>
class Node
{
    
public:
    
    //Data type to hold coefficient, exponent pair
    T polyInfo;
    
    //Self-referential Node
    Node<T>* next;
    
    //Constructor
    Node(T = T(), Node<T>* = NULL);
    
};  //End of Node class definition


//LL class definition
template <class T>
class LinkedList
{
    //Overloaded stream insertion operator
    template <class F>
    friend std::ostream& operator<< (std::ostream&, const LinkedList<F> &rhsObj);
    
private:
    
    //Integer to keep track of list size
    int countNodes;
    
    //pointer to list head
    Node<T>* head;
    
    //pointer to list tail
    Node<T>* tail;
    
    //copyList private member function
    void copyList(const LinkedList<T> &listToCopy);
    
public:
    
    //Constructor
    LinkedList();
    
    //Copy constructor
    LinkedList(const LinkedList<T>& otherLL);
    
    //Polynomial build function
    void build(string);
    
    //Destructor
    ~LinkedList();
    
    //Overloaded = operator
    const LinkedList& operator=(const LinkedList<T>& rhsObj);
    
    //Inserts polyPair into linked list
    void insert(T insertValue);
    
    //clear function
    void clear();
    
    //size function
    int size() const {return countNodes;};
    
    //Overloaded addition operator
    const LinkedList operator+(const LinkedList<T>& rhsObj);
    
    //Overloaded subtraction operator
    const LinkedList operator-(const LinkedList<T>& rhsObj);
    
    //Function to multiply two linked lists
    const LinkedList<T> multiply(const LinkedList<T>& p2);    //added const
    
    //Function to raise polynomial to an exponent
    LinkedList<T> exponentiate(int exponent);
    
    //Evaluates polynomial given x value
    long long evaluatePolynomial (int xValue);
    
    //Raises integer to a power
    long long raiseTo (long long xValue, int exponent);
    
    //Squares an integer
    long long square (long long baseToSquare);
    
    //Squares a linked list and returns new linked list
    LinkedList<T> squarePoly ();
    
};  //End of LinkedList class definition


/************************************************************************
 *                                                                      *
 *                     Node Template Class Implementation               *
 *                                                                      *
 ************************************************************************/

/************************************************
 *             Node Constructor                 *
 ************************************************/
template <class T>
Node<T>:: Node(T value, Node<T> *nPtr)
{
    polyInfo = value;
    next = nPtr;
}

/************************************************************************
 *                                                                      *
 *                     LL Template Class Implementation                 *
 *                                                                      *
 ************************************************************************/

/************************************************
 *              LL Constructor                  *
 ************************************************/
template <class T>
LinkedList<T>::LinkedList()
{
    countNodes = 0;
    head = NULL;
    tail = NULL;
}

/************************************************
 *              LL Build function               *
 ************************************************/

template <class T>
void LinkedList<T>::build(string line){
    
    int coefficient = 0 , exponent = 0;
    
    std::stringstream stream (line);
    
    while(stream.good()){
        
        stream >> coefficient >> exponent;
        
        if(coefficient == 0){
            cout << "Error in build function. Coefficient is zero" << endl;
            break;
        }
        
        else{
            PolyPair newPair(coefficient, exponent);
            insert(newPair);
        }
        
    }   //End of while loop

}

/************************************************
 *              LL Copy Constructor             *
 ************************************************/
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLL)
{
    countNodes = 0;
    head = NULL;
    
    //call copy List function
    this->copyList(otherLL);
    
}

/************************************************
 *            LL copyList function              *
 ************************************************/
template <class T>
void LinkedList<T>::copyList(const LinkedList<T> &myListToCopy)
{
    Node<T>* current = myListToCopy.head;
    
    while(current!= NULL)
    {
        this -> insert(current->polyInfo);
        current = current->next;
    }
    
}

/************************************************
 *              LL Destructor                   *
 ************************************************/
template <class T>
LinkedList<T>::~LinkedList()
{
    this -> clear();
}

/************************************************
 *            LL Overloaded = operator          *
 ************************************************/
template <class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &myObj)
{
    //Test for self-assignment
    if(this->head!= myObj.head)
    {
        this->clear();
        this->copyList(myObj);
    }
    
    return *this;
}

/************************************************
 *            LL Overloaded + operator          *
 ************************************************/
template <class T>
const LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& rhsObj){
    
    Node<T>* current = head;
    Node<T>* rhsCurrent = rhsObj.head;
    
    LinkedList<PolyPair> mySumList;
    string overflow = "Overflow error has occured";
   
    try{
   
        while((current!= NULL) && (rhsCurrent != NULL)){
        
            //If the exponents are equal, add the terms
            if( ( current->polyInfo.get_exponent() ) ==  (rhsCurrent->polyInfo.get_exponent()) ){
            
                //Test whether the terms will cancel first
                if(current->polyInfo.get_coeff() == -(rhsCurrent->polyInfo.get_coeff())){
                
                    //Terms will cancel, dont add to list
                    current = current->next;
                    rhsCurrent = rhsCurrent->next;
                
                }
            
                else{
                
                    //Add the coefficients and create a new polyPair
                    int coeff1 = current->polyInfo.get_coeff();
                    int coeff2 = rhsCurrent->polyInfo.get_coeff();
                    int newCoeff = (coeff1 + coeff2);
                    //overflow testing
                    if((newCoeff - coeff1) == coeff2){
                
                        PolyPair newPair (newCoeff, current->polyInfo.get_exponent());
                        mySumList.insert(newPair);
                        current = current -> next;
                        rhsCurrent = rhsCurrent->next;
                    }
                    else
                        throw overflow;
                }
            }
        
            //If the exponent is larger, insert it and move to next place in the list
            else if (( current->polyInfo.get_exponent() ) >  (rhsCurrent->polyInfo.get_exponent())){
            
                //Insert term 1
                //Advance current point in list 1
                PolyPair newPair (current->polyInfo);
                current = current -> next;
                mySumList.insert(newPair);
            }
        
            //Otherwise, the other exponent must be larger so insert that and move forward in the second list
            else {
            
                PolyPair newPair ( rhsCurrent -> polyInfo);
                mySumList.insert(newPair);
                rhsCurrent = rhsCurrent -> next;
            }
        
        }   //End of while loop
    
    
        //Then add all remaining terms from first polynomial into list
        while(rhsCurrent!= NULL){
        
            PolyPair newPair = rhsCurrent->polyInfo;
            mySumList.insert(newPair);
            rhsCurrent = rhsCurrent->next;
        }

    }   //End of try block
    catch(string){
        
    }
    catch(...){
        
    }
    
    return mySumList;
}

/************************************************
 *            LL Overloaded - operator          *
 ************************************************/
//Functions the same way as the overloaded addition operator but subtracts rather than adds
template <class T>
const LinkedList<T> LinkedList<T>::operator-(const LinkedList<T>& rhsObj){
    
    Node<T>* current = head;
    Node<T>* rhsCurrent = rhsObj.head;
    LinkedList<T> mySubList;
    
    
    while((current!= NULL) && (rhsCurrent != NULL)){
        
        //If the exponents are equal, add the terms
        if( ( current->polyInfo.get_exponent() ) ==  (rhsCurrent->polyInfo.get_exponent()) ){
            
            //Test whether the terms will cancel first
            if(current->polyInfo.get_coeff() == -(rhsCurrent->polyInfo.get_coeff())){
                
                //Terms will cancel
                //Dont add to the new linked list
                current = current->next;
                rhsCurrent = rhsCurrent->next;
                
            }   //end of if statement
            
            else{
                
                //Add the coefficients and create a new polyPair
                int newCoeff = (current->polyInfo.get_coeff()) - (rhsCurrent->polyInfo.get_coeff());
                PolyPair newPair (newCoeff, current->polyInfo.get_exponent());
                mySubList.insert(newPair);
                
            }
        }
        
        else if (( current->polyInfo.get_exponent() ) >  (rhsCurrent->polyInfo.get_exponent())){
            
            //insert term 1
            //advance current point in list 1
            PolyPair newPair (current->polyInfo);
            current = current -> next;
            mySubList.insert(newPair);
            
        }   //End of else if statement
        
        else {
            
            //Change the sign of the coefficient
            int coefficient = - (rhsCurrent->polyInfo.get_coeff());
            int exponent = rhsCurrent->polyInfo.get_exponent();
            
            PolyPair newPair ( coefficient, exponent);
            mySubList.insert(newPair);
            rhsCurrent = rhsCurrent -> next;
        }
        
    }   //End of while loop
    
    
    //Then add all remaining terms from first polynomial into list
    while(rhsCurrent!= NULL){
        
        int coefficient = - (rhsCurrent->polyInfo.get_coeff());
        int exponent = rhsCurrent->polyInfo.get_exponent();
        
        PolyPair newPair (coefficient, exponent);
        
        mySubList.insert(newPair);
        rhsCurrent = rhsCurrent->next;
        
    }
    
    return mySubList;
}

/************************************************
 *        Multiply two polys function           *
 ************************************************/
template <class T>
const LinkedList<T> LinkedList<T>::multiply(const LinkedList<T>& p2){
 
    Node<T>* p1current = head;
    Node<T>* p2current = p2.head;
    LinkedList<T> productList;
    string overflow = "Overflow error has occured";
    
    try{
        
        //Check to make sure that neither list is empty
        if(p1current == NULL || p2current == NULL){
            cout << "Error in multiply polynomial function" << endl;
        }
    
        //Iterate through list one, and multiply by each entry in list two
        while(p1current!= NULL){
        
            int coeff1 = p1current->polyInfo.get_coeff();
            int expon1 = p1current->polyInfo.get_exponent();
        
            while(p2current!= NULL){
        
                int coeff2 = p2current->polyInfo.get_coeff();
                int expon2 = p2current->polyInfo.get_exponent();
                int resultCoeff = coeff1 * coeff2;
                int resultExpon = expon1 + expon2;
                
                if(((resultCoeff/coeff1) == coeff2) && ((resultExpon - expon1) == expon2)){
                    
                    PolyPair newPair (resultCoeff, resultExpon);
                    productList.insert(newPair);
                    p2current = p2current->next;
                }
                else
                    throw overflow;
                
            }   //End of while loop
        
            p1current = p1current -> next;
            p2current = p2.head;
        } //End of while loop
        
    }   //End try block
    catch (string overflowError){
        cout << overflowError;
        throw overflowError;
    }
    
    return productList;
}
/************************************************
 *              LL insert()                     *
 ************************************************/
template <class T>
void LinkedList<T>::insert(T polyObject)
{
    Node<T>* trailCurrent = head;
    Node<T>* current = head;
    Node<T>* addMe = NULL;
    string overflow = "Overflow error has occured";

    try
    {
        //The coefficient should only be zero if an overflow has occured
        //No other code would set the coefficient to zero
        if(polyObject.get_coeff() == 0)
            throw overflow;
        
        //If the linked list is empty
        if (current == NULL){
            //Create a new node and add it to the list
            //Both head and tail point to one node
            addMe = new Node<T>(polyObject);
            addMe -> next = head;
            head = addMe;
            tail = addMe;
            
        }
        //If the list isnt empty but node should be inserted at front
        else if(((polyObject.get_exponent()) > (head -> polyInfo.get_exponent()))){
           
            addMe = new Node<T>(polyObject);
            addMe -> next = head;
            head = addMe;
        }
        
        //Else the list is not empty
        else{
            
            //If exponent is smaller than the exponent at the tail, immedietly insert into back
            if ((polyObject.get_exponent() < (tail->polyInfo.get_exponent()))){
            
                //If the exponents are equal, combine the terms
                if((current!= NULL) && (polyObject.get_exponent() == tail -> polyInfo.get_exponent())){
                    
                    //Add the coefficients
                    int coeff1 = polyObject.get_coeff();
                    int coeff2 = tail->polyInfo.get_coeff();
                    int newCoeff = (coeff1 + coeff2);
                    
                    //Overflow test
                    if(newCoeff - coeff1 == coeff2)
                        tail -> polyInfo.set_coeff(newCoeff);
                    else
                        throw overflow;
                }
                //Otherwise insert new node into back of list
                else{
                    
                    Node<T>* addMe = new Node<T> (polyObject, NULL);
                    tail -> next = addMe;
                    addMe -> next = NULL;
                    tail = addMe;
                }
            }
            
            
            else{
            
                //While the exponent to insert is smaller than the exponent in the list, keep moving through the list
                while((current!= NULL) && ((polyObject.get_exponent()) < (current->polyInfo.get_exponent()))){
                    trailCurrent = current;
                    current = current -> next;
                }
            
                //If the exponents are equal, combine the terms
                if((current!= NULL) && (polyObject.get_exponent() == current -> polyInfo.get_exponent())){
                
                    //Add the coefficients
                    int coeff1 = polyObject.get_coeff();
                    int coeff2 = current->polyInfo.get_coeff();
                    int newCoeff = coeff1 + coeff2;
                    if((newCoeff - coeff1) == coeff2)
                        current -> polyInfo.set_coeff(newCoeff);
                    else
                        throw overflow;
                }
            
                else{
                    //current points to correct insertion location
                    Node<T> *addMe = new Node<T> (polyObject, NULL);
                    trailCurrent-> next = addMe;
                    addMe ->next = current;
                }
            }
        }
        
        countNodes++;
    }
    catch(string overFlow){
        //cout << overFlow;
        throw overFlow;
    }
    catch(std::bad_alloc bad)
    {
        cout << bad.what();
        throw bad;
    }
    catch(...)
    {
        string errorMessage = "Error in insert()";
        cout << "In catch all for insert()" << endl;
        throw errorMessage;
    }
}

/************************************************
 *              LL Clear()                      *
 ************************************************/
template <class T>
void LinkedList<T>::clear()
{
    try
    {
        Node<T>* current = head;
        
        while(current!= NULL)
        {
            head = head-> next;
            delete current;
            current = head;
        }
        
        head = NULL;
        tail = NULL;
        current = NULL;
        countNodes = 0;
        
    }   //end of try block
    
    catch(...)
    {
        string errorMessage = "Error in clear()";
        cout << "In clear() catch all" << endl;
        throw errorMessage;
    }
}

/************************************************
 *         Overloaded << Operator               *
 ************************************************/
template <class F>
std::ostream& operator<< (std::ostream& os, const LinkedList<F> &rhsObj)
{
    if (rhsObj.head == NULL)
    {
        os << "0" << endl;
        return os;
    }
    
    Node<F>* current = rhsObj.head;
    
    while(current!= NULL)
    {
        os << current-> polyInfo;
        current = current->next;
    }
    
    return os;
}   //End of overloaded stream insertion operator

/************************************************
 *            Evaluate Polynomial               *
 ************************************************/

template <class T>
long long LinkedList<T>::evaluatePolynomial (int xValue){
    
    long long updatedValue = 0;
    int coefficient = 0;
    int exponent = 0;
    long long toAdd = 0;
    string overflow = "An over flow has occured \n";
    
    Node<PolyPair>* current = head;
    
    try{
    
        // When x is 1, result of that term is 1 regardless of exponent
        // so traverse list and add up all coefficients
        if(xValue == 1){
        
            while(current!= NULL){
            
                coefficient = current -> polyInfo.get_coeff();
                long long tempUpdatedValue = updatedValue;
                updatedValue = updatedValue + (long long)coefficient;
                
                if( updatedValue - (long long)coefficient == tempUpdatedValue)
                    current = current -> next;
                else
                    throw overflow;
            }
            return updatedValue;
        }   //End of if statement
    
    
        //For all cases when x is not 1
        else{
    
            while(current!= NULL){
        
                //Extract info from current node
                coefficient = current -> polyInfo.get_coeff();
                exponent = current -> polyInfo.get_exponent();
            
                //If the exponent is 0, x^0 is 1 so only add coeff value
                if(exponent == 0){
                
                    //store values and perform overflow testing
                    toAdd = (long long)coefficient;
                    long long tempUpdatedValue = updatedValue;
                    
                    updatedValue = updatedValue+toAdd;
                    if( updatedValue - toAdd == tempUpdatedValue)
                        current = current -> next;
                    else
                        throw overflow;
                }
            
                //If the exponent is 1
                else if(exponent == 1){
            
                    toAdd = coefficient * xValue;
                    
                    long long tempUpdatedValue = updatedValue;
                    
                    updatedValue = updatedValue+toAdd;
                    if( updatedValue - toAdd == tempUpdatedValue)
                        current = current -> next;
                    else
                        throw overflow;
                }
            
                //If the exponent is 2, call square function
                else if(exponent == 2){
            
                    toAdd = (square(xValue)) * coefficient;
                    
                    long long tempUpdatedValue = updatedValue;
                    
                    updatedValue = updatedValue+toAdd;
                    if( updatedValue - toAdd == tempUpdatedValue)
                        current = current -> next;
                    else
                        throw overflow;
                }
            
                //If the coefficient equals the xvalue, add their exponents
                else if(coefficient == xValue){
            
                    toAdd = raiseTo(coefficient, (exponent+1));
                    long long tempUpdatedValue = updatedValue;
                    
                    updatedValue = updatedValue+toAdd;
                    if( updatedValue - toAdd == tempUpdatedValue)
                        current = current -> next;
                    else
                        throw overflow;
                }
        
                //Exponent is not 0, 1, or 2, or equal to xValue
                else{
            
                    toAdd = (raiseTo(xValue, exponent)) * coefficient;
                    
                    long long tempUpdatedValue = updatedValue;
                    
                    updatedValue = updatedValue+toAdd;
                    if( updatedValue - toAdd == tempUpdatedValue)
                        current = current -> next;
                    else
                        throw overflow;

                }   //end of else block
        
            }   //End of while loop
        
        }   // End ouf outer else block
        
    }//End of try block
    catch(string ErrorMessage){
        
        throw ErrorMessage;
    }
    catch(...){
        
        throw "Error in Evaluate function";
    }
    
    return updatedValue;
}

/************************************************
 *           Square Integer Function            *
 ************************************************/
template <class T>
long long LinkedList<T>::square (long long baseToSquare) {
    
    //Function takes a number and returns the square
    
    long long result;
    return result = (baseToSquare * baseToSquare);
}

/************************************************
 *          Raise to power function             *
 ************************************************/

template <class T>
long long LinkedList<T>::raiseTo (long long value, int power) {

    //This function raises a known integer to a given power
   
        if (power == 0 || value == 1)
            return 1;
        
        else if(power == 1)
            return value;
    
        //Even power, can use 'short cut' to avoid excessive multiplication
        else if(power % 2 == 0){
        
            long long newNum = raiseTo(value, power/2);
            return square(newNum);
        }
    
        //Does not catch all odd powers but handles 6, 9, 12, etc efficiently
        else if (power % 3 == 0){
        
            long long newNum2 = raiseTo(value, power/3);
            return newNum2 * square(newNum2);
        }
        else if(value == (-1)){
        
            if(power % 2 == 0)
                return 1;
            else
                return -1;
        }
        //Raises any value to a power, uses recursion
        else{
            return value * raiseTo(value, power-1);
        }
}

/************************************************
 *               Square Polynomial              *
 *                                              *
 ************************************************/
template <class T>
LinkedList<T> LinkedList<T>::squarePoly (){
    
    Node<PolyPair> *current = head;
    Node<PolyPair> *mover = head;
    
    LinkedList<T> resultList;
    
    current = head;
   
    //Multiply first term by itself then multiply it by every term in list.
    //Move to second term, multply by itself, then multiply by remaining terms in list (but not first term)
    //Continue until end of list is reached.
    while(current != NULL){
        
        while(mover!= NULL){
            
            PolyPair newPair = current->polyInfo.multiply(mover->polyInfo);
            resultList.insert(newPair);
            mover = mover -> next;
        }
        
        mover = head;
        current = current -> next;
        
    }
    
    return resultList;
}

/************************************************
 *          Exponentiate Polynomial             *
 ************************************************/

template <class T>
LinkedList<T> LinkedList<T>::exponentiate(int power){
    
    LinkedList<PolyPair> resultList;
    
    
    if (power == 0) {
        cout << "Error, cannot exponentiate a polynomial to zero-ith power" << endl;

    }

    //Raising to the power of 1 does not change the polynomial
    if(power == 1){
        return *this;
    }
    
    //Power is even, use equation for even exponentiation
    if(power % 2 == 0 ){
     
            return squarePoly().exponentiate((power/2));
    }
    //Else power is odd, use equation for odd exponentiation
    else{
        return multiply(squarePoly().exponentiate((power-1)/2));
    
    }
    
        return resultList;
    
}   //End exponentiate function

#endif /* LinkedList_hpp */
