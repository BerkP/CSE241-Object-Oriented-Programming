#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <memory>
#include "node.h"

using namespace std;



namespace GTU_PKGZ{

	template <class T>
	class GTUIterator{
	public:
		GTUIterator(const shared_ptr<node<T>>& ptr):iteratorPtr(ptr){}
		T& operator*(){ return iteratorPtr->data;}
		T* operator->(){ return &(iteratorPtr->data);}
		GTUIterator operator++(){ 
			iteratorPtr=iteratorPtr->next;
			return iteratorPtr;
		}
		GTUIterator operator++(int){ 
			shared_ptr<node<T>> temp = iteratorPtr;
			iteratorPtr=iteratorPtr->next;
			return temp;
		}
		GTUIterator operator--(){ 
			iteratorPtr=iteratorPtr->prev;
			return iteratorPtr;
		}
		GTUIterator operator--(int){ 
			shared_ptr<node<T>> temp = iteratorPtr;
			iteratorPtr=iteratorPtr->prev;
			return temp;
		}
		bool operator==(const GTUIterator<T>& other){return other.iteratorPtr == iteratorPtr;}
		bool operator!=(const GTUIterator<T>& other){return other.iteratorPtr != iteratorPtr;}

	private:
		shared_ptr<node<T>> iteratorPtr;	
	};
}

#endif