//Main.cpp

#include <iostream>
#include <fstream>

#include "LinkedList.hpp"
#include "PolyPair.hpp"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int main(int argc, const char * argv[]) {
    
    string ErrorMessage = "Error has occured";
    
    try {
        
        if ( argc < 2){
        //Not enough command line arguments
         throw ErrorMessage;
        }   //End of if block
        
        else{
            
            //File path via command line argument
            string myFileName = argv[1];
            
            string fileOpenError;
            string line;
            ifstream inFile(myFileName.c_str());
            
            //Create two polynomial objects
            LinkedList<PolyPair> myPoly1;
            LinkedList<PolyPair> myPoly2;
            
            if(!inFile){
                
                inFile.close();
                fileOpenError = "Input file failed to open";
                throw fileOpenError;
            }
            
            else{
                
                //Incrementing variable used to distinguish between lines
                int k = 1;
                
                while(getline(inFile, line)){
                    
                    //If this is the first line, pass to Poly1 build
                    if(k == 1) {
                        myPoly1.build(line);
                    }
                    
                    //If this is the second line, pass to Poly2 build
                    if(k == 2) {
                        myPoly2.build(line);
                    }
                    
                    k++;
                    
                }   //End while loop
                
            }   //End else block
            
            
            cout << "Polynomial 1: "<< myPoly1 << endl << endl;
            
            cout << "Evaluating polynomial 1 for x = 1,2,3,10: "<< endl;
            cout<< "P(1) = " << myPoly1.evaluatePolynomial(1) << endl;
            cout<< "P(2) = " << myPoly1.evaluatePolynomial(2) << endl;
            cout<< "P(3) = " << myPoly1.evaluatePolynomial(3) << endl;
            cout<< "P(10) = " << myPoly1.evaluatePolynomial(10) << endl << endl;
            cout << "" << endl;
            
            cout << "Polynomial 2: "<< myPoly2 << endl << endl;
            
            cout << "Evaluating polynomial 2 for x = 1,2,3,10: "<< endl;
            cout<< "P(1) = " << myPoly2.evaluatePolynomial(1) << endl;
            cout<< "P(2) = " << myPoly2.evaluatePolynomial(2) << endl;
            cout<< "P(3) = " << myPoly2.evaluatePolynomial(3) << endl;
            cout<< "P(10) = " << myPoly2.evaluatePolynomial(10) << endl << endl;

            
            LinkedList<PolyPair> sumPoly = myPoly1 + myPoly2;
            cout << "Polynomial 1 + Polynomial 2 = " << sumPoly << endl << endl;

            
            cout << "Evaluating sum of Polynomial 1 and Polynomial 2 for x = 1,2,3,10: " << endl;
            cout<< "P(1) = " << sumPoly.evaluatePolynomial(1) << endl;
            cout<< "P(2) = " << sumPoly.evaluatePolynomial(2) << endl;
            cout<< "P(3) = " << sumPoly.evaluatePolynomial(3) << endl;
            cout<< "P(10) = " << sumPoly.evaluatePolynomial(10) << endl << endl;
    

            cout << "Polynomial 1 * Polynomial 2 = ";
            LinkedList<PolyPair> productPoly = myPoly1.multiply(myPoly2);
            cout << productPoly << endl << endl;
            
            cout << "Evaluating product of Polynomial 1 and Polynomial 2 for x = 1,2,3,10: " << endl;
            cout<< "P(1) = " << productPoly.evaluatePolynomial(1) << endl;
            cout<< "P(2) = " << productPoly.evaluatePolynomial(2) << endl;
            cout<< "P(3) = " << productPoly.evaluatePolynomial(3) << endl;
            cout<< "P(10) = " << productPoly.evaluatePolynomial(10) << endl << endl;
           
            
            cout << "Polynomial 1, raised to the fifth power = " << endl;
          
            cout << myPoly1.exponentiate(5) << endl << endl;
           
            
            cout << "Polynomial 2 evaluted at 5 = " << myPoly2.evaluatePolynomial(5) << endl;
            cout << "Polynomial 1, raised to the power of polynomial 2 evaluated at 5 = ";
            cout << myPoly1.exponentiate((int)myPoly2.evaluatePolynomial(5))<< endl << endl;
                        
            cout << "Polynomial 1, raised to the fifth power, evaluated at 2 = " << endl << endl;
            cout << "Poly1 ^ 5, x:2 = " << myPoly1.exponentiate(5).evaluatePolynomial(2) << endl << endl << endl;
           
            
        }   //End else Block
        
    } //end of try block
    
    catch (string Error){
        
        cout << Error << endl;
        
    }
    
    return 0;
    
}   // End function Main()

