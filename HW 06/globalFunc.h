#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
/* #################################################################################################*/
/* ###This file contains template functions, so implementions and headers have to be in same file###*/
/* #################################################################################################*/

#include <iostream>
#include "GTUIterator.h"
#include "GTUIteratorConst.h"

using namespace std;


namespace GTU_PKGZ{

	

	template<class IteratorType, class T>
	IteratorType find (IteratorType begin, IteratorType  end, const T& value){
		for(;begin != end ; begin++){
			if ((*begin) == value) 
				return begin;
		}
		return end;
	}

	template<class IteratorType, class functionType>
	functionType for_each(IteratorType begin, IteratorType end, functionType goalFunction){
		for(;begin != end ; begin++){
			goalFunction (*begin);
		}
		return goalFunction;
	}


	template<class IteratorType, class functionType>
	IteratorType find_if(IteratorType begin, IteratorType  end, functionType goalFunction){
		for(;begin != end ; begin++){
			if ( goalFunction(*begin) ) 
				return begin;
		}
		return end;
	}
}


#endif

