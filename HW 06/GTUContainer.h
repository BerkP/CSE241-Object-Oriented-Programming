#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H
/* ######################################################################################*/
/* ###This file contains only pure virtual function class, so there is no implemention###*/
/* ######################################################################################*/

#include<iostream>
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "badparam.h"

using namespace std;

namespace GTU_PKGZ{

	template <class T>
	class GTUContainer{
	public:
		virtual GTUIterator<T> insert(const T&) = 0;
		virtual void erase(GTUIterator<T>& it) = 0;
		virtual void clear() = 0;
		virtual bool empty()const = 0;
		virtual int size()const = 0;
		virtual int max_size()const = 0;
		virtual GTUIterator<T> begin() = 0;
		virtual GTUIterator<T> end() = 0;
		virtual GTUIteratorConst<T> begin()const = 0;
		virtual GTUIteratorConst<T> end()const = 0;
		virtual ~GTUContainer(){}
	};

}




#endif