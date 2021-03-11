#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include <memory>
#include "node.h"

using namespace std;



namespace GTU_PKGZ{

	template <class T>
	class GTUIteratorConst{
	public:
		GTUIteratorConst(const shared_ptr<node<T>>& ptr):iteratorPtr(ptr){}
		const T& operator*(){ return iteratorPtr->data;}
		const T* operator->(){ return &(iteratorPtr->data);}
		GTUIteratorConst operator++(){ 
			iteratorPtr=iteratorPtr->next;
			return iteratorPtr;
		}
		GTUIteratorConst operator++(int){ 
			shared_ptr<node<T>> temp = iteratorPtr;
			iteratorPtr=iteratorPtr->next;
			return temp;
		}
		GTUIteratorConst operator--(){ 
			iteratorPtr=iteratorPtr->prev;
			return iteratorPtr;
		}
		GTUIteratorConst operator--(int){ 
			shared_ptr<node<T>> temp = iteratorPtr;
			iteratorPtr=iteratorPtr->prev;
			return temp;
		}
		bool operator==(GTUIteratorConst<T>& other){return other.iteratorPtr == iteratorPtr;}
		bool operator!=(GTUIteratorConst<T>& other){return other.iteratorPtr != iteratorPtr;}

	private:
		shared_ptr<node<T>> iteratorPtr;	
	};
}

#endif