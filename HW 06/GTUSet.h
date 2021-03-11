#ifndef GTUSET_H
#define GTUSET_H
/* #################################################################################################*/
/* ###This file contains template functions, so implementions and headers have to be in same file###*/
/* #################################################################################################*/

#include <memory>
#include "GTUContainer.h"

using namespace std;

namespace GTU_PKGZ{

	template <class T>
	class GTUSet:public GTUContainerWithLL<T>{
	public:
		GTUSet():GTUContainerWithLL<T>(0){}
		GTUSet(const GTUSet<T>& other):GTUContainerWithLL<T>(other){}
		
		GTUIterator<T> insert(const T& );

		const GTUSet<T>& operator=(const GTUSet<T>& );
		~GTUSet();

	private:
		bool isValueInSet(const T&)const;
		/* function for checking duplicate */

	};
	
	template <class T>
	bool GTUSet<T>::isValueInSet(const T& value)const{
		shared_ptr<node<T>> temp = this->containerHead;	

		while(temp!= nullptr){
			if(temp->data == value)
				return true;
			temp = temp->next;
		}
		
		return false;
	}

	template <class T>
	GTUIterator<T> GTUSet<T>::insert(const T& value){
		if(this->sizeOfContainer == this->MAX_SIZE)
			throw bad_param("MAX_SIZE reached!");
		if(isValueInSet(value))
			throw bad_param("Data is already in the set!");

		shared_ptr<node<T>> temp = this->containerHead;	
		shared_ptr<node<T>> newNode (new node<T>());
		newNode->data = value;
		if(this->sizeOfContainer == 0){
			this->containerHead = newNode;
		}
		else{
			this->containerTail->next = newNode;
			newNode->prev = this->containerTail;
		}
		this->containerTail = newNode;
		this->sizeOfContainer++;
		return GTUIterator<T>(newNode);
	}

	template <class T>
	const GTUSet<T>& GTUSet<T>::operator=(const GTUSet<T>& other){
		if(this == &other)
			return *this;

		GTUContainerWithLL<T>::operator=(other);
		return *this;
	}

	template <class T>
	GTUSet<T>::~GTUSet(){
		this->clear();
	}



}


#endif