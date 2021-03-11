/* ###################################################################*/
/* ###########This is a test driver code for GTU CSE241 HW6###########*/
/* ###################################################################*/
/* #####Homework file contains only .h files because of templates#####*/
/* ###Templete functions have to be in same file with their headers###*/
/* ###################################################################*/

#include <iostream>
#include <memory>
#include "GTUVector.h"
#include "GTUSet.h"
#include "GTUContainer.h"
#include "GTUIterator.h"
#include "globalFunc.h"

using namespace std;
using namespace GTU_PKGZ;


bool isDividibleByFive(int num){
	return ((num%5) == 0);
}

int printIntiger(int num){
	cout <<  num << endl ;
	return num;
}


int main(int argc, char const *argv[]){

	cout << "*******************************" << endl;
	cout << "GTUVector TEST has been started" << endl;
	cout << "*******************************" << endl;

	GTUVector<int> myVec1;
	cout << "max_size of a GTUVector  is " << myVec1.max_size() << endl; 
	GTUIterator<int> myIte1 = myVec1.begin();
	myVec1.insert(1);
	myVec1.insert(2);
	myVec1.insert(3);
	myVec1.insert(4);
	myVec1.insert(5);

	cout << endl << "<int>myVec1 created and inserted 1-2-3-4-5 as value" << endl; 

	cout << "Current vector: ";
	for(myIte1 = myVec1.begin(); myIte1 != myVec1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << myVec1.size() << endl ;

	myIte1 = myVec1.begin();
	myVec1.insert(myIte1,0);

	cout << endl << "Value 0 inserted to myVec1 with begin() iterator" << endl; 

	cout << "Current vector: ";
	for(myIte1 = myVec1.begin(); myIte1 != myVec1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << myVec1.size() << endl ;

	
	myVec1.clear();
	myVec1.insert(9);
	myIte1 = myVec1.begin();
	myVec1.insert(myIte1,8);
	myVec1.insert(10);
	myVec1.insert(11);

	cout << endl << "clear() called and 9 - 8(with begin iterator) - 10 - 11 inserted in order" << endl; 

	cout << "Current vector: ";
	for(myIte1 = myVec1.begin(); myIte1 != myVec1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << myVec1.size() << endl ;


	
	myIte1 = myVec1.begin();
	myIte1++;
	myVec1.erase(myIte1);
	cout << endl << "erase() called with begin iterator++ (second element in vector)" << endl; 

	cout << "Current vector: ";
	for(myIte1 = myVec1.begin(); myIte1 != myVec1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << myVec1.size() << endl ;
	


	cout << endl << "For exception test, myVec2 created and insert() called 10001(max_size is 1000) times" << endl; 
	GTUVector<int> myVec2;
	try{
		for(int i=0 ; i < 1001 ; i++){
			myVec2.insert(i);
		}
	}
	catch(bad_param excp){
		cout << endl << "exception cathed and bad_param.errMessage() called : " ; 
		excp.errMessage();
	}	

	cout << "Current vector with size: " << myVec1.size() << endl ;


	cout << "*******************************" << endl;
	cout << "GTUSet TEST has been started" << endl;
	cout << "*******************************" << endl;

	GTUSet<int> mySet1;
	cout << "max_size of a GTUSet  is " << mySet1.max_size() << endl; 
	myIte1 = mySet1.begin();
	mySet1.insert(1);
	mySet1.insert(2);
	mySet1.insert(3);
	mySet1.insert(4);
	mySet1.insert(5);

	cout << endl << "<int>mySet1 created and inserted 1-2-3-4-5 as value" << endl; 

	cout << "Current set: ";
	for(myIte1 = mySet1.begin(); myIte1 != mySet1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << mySet1.size() << endl ;

	
	mySet1.clear();
	mySet1.insert(9);
	mySet1.insert(8);
	mySet1.insert(10);
	mySet1.insert(11);

	cout << endl << "clear() called and 9 - 8 - 10 - 11 inserted in order" << endl; 

	cout << "Current set: ";
	for(myIte1 = mySet1.begin(); myIte1 != mySet1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << mySet1.size() << endl ;


	
	myIte1 = mySet1.begin();
	myIte1++;
	mySet1.erase(myIte1);
	cout << endl << "erase() called with begin iterator++ (second element in set)" << endl; 

	cout << "Current set: ";
	for(myIte1 = mySet1.begin(); myIte1 != mySet1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << mySet1.size() << endl ;
	


	cout << endl << "For exception test, tried to insert 11 again(for duplicate)" << endl; 
	try{
		mySet1.insert(11);
	}
	catch(bad_param excp){
		cout << endl << "exception cathed and bad_param.errMessage() called : " ; 
		excp.errMessage();
	}	

	cout << "Current set with size: " << mySet1.size() << endl << endl;

	cout << "*****************************************************" << endl;
	cout << "Global Functions TEST with GTUVector has been started" << endl;
	cout << "*****************************************************" << endl;

	cout << "Current vector: ";
	for(myIte1 = myVec1.begin(); myIte1 != myVec1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << myVec1.size() << endl ;

	GTUIterator<int> myIte2 = myVec1.begin();
	GTUIterator<int> myIte3 = myVec1.end();
	myIte1 = find(myIte2,myIte3,11);
	cout << endl << "find function called with begin(),end() and value 11 " << endl; 
	cout  << "return value is: " << *myIte1 << endl;

	myIte1 = find_if(myIte2,myIte3,isDividibleByFive);
	cout << endl << "find_if function called with begin(),end() and function isDividibleByFive " << endl; 
	cout  << "return value is: " << *myIte1 << endl;

	cout << endl << "for_each function called with begin(),end() and function printIntiger " << endl; 
	cout  << "Output: " << endl;
	for_each(myIte2,myIte3,printIntiger);


	cout << "*****************************************************" << endl;
	cout << "Global Functions TEST with GTUSet has been started" << endl;
	cout << "*****************************************************" << endl;

	cout << "Current set: ";
	for(myIte1 = mySet1.begin(); myIte1 != mySet1.end() ; myIte1++ )
		cout << *myIte1 << " ";
	cout << "    with size: " << mySet1.size() << endl ;
	myIte2 = mySet1.begin();
	myIte3 = mySet1.end();
	myIte1 = find(myIte2,myIte3,11);
	cout << endl << "find function called with begin(),end() and value 11 " << endl; 
	cout  << "return value is: " << *myIte1 << endl;

	myIte1 = find_if(myIte2,myIte3,isDividibleByFive);
	cout << endl << "find_if function called with begin(),end() and function isDividibleByFive " << endl; 
	cout  << "return value is: " << *myIte1 << endl;

	cout << endl << "for_each function called with begin(),end() and function printIntiger " << endl; 
	cout  << "Output: " << endl;
	for_each(myIte2,myIte3,printIntiger);

	return 0;
}