#ifndef NODE_H
#define NODE_H
/* ######################################################################*/
/* ###This file contains node class for GTUContainer data(linked list)###*/
/* ######################################################################*/

#include <memory>

using namespace std;

namespace GTU_PKGZ{

	template <class T>
	class node{
	public:
		node():next(nullptr),prev(nullptr){};
		T data;
		shared_ptr<node> next;
		shared_ptr<node> prev;
	};

}

#endif	