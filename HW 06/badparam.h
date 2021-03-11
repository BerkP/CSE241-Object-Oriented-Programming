#ifndef BADPARAM_H
#define BADPARAM_H
/* #############################################*/
/* ###This file contains class for exceptions###*/
/* #############################################*/

#include <iostream>

using namespace std;

namespace std{

	class bad_param{
	public:
		bad_param():bad_param("Something happened wrong!"){}
		bad_param(const string& input):err(input){};
		void errMessage()const{
			cout << endl << err << endl ;
		}
	private:
		string err;
	};

}


#endif
