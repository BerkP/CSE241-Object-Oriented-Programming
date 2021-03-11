#ifndef GTUVECTOR_H
#define GTUVECTOR_H
/* #################################################################################################*/
/* ###This file contains template functions, so implementions and headers have to be in same file###*/
/* #################################################################################################*/

#include <memory>
#include "GTUContainerWithLL.h"
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "node.h"

using namespace std;

namespace GTU_PKGZ{


	template <class T>
	class GTUVector:public GTUContainerWithLL<T>{
		public:
		GTUVector():GTUVector(0){}
		GTUVector(const GTUVector<T>& other):GTUContainerWithLL<T>(other){}
		/*Copy constructer */
		GTUVector(int);
		/* Constructer with initial size */	

		GTUIterator<T> insert(const T& );
		GTUIterator<T> insert(const GTUIterator<T>& it, const T& );
		T& operator[](int );
		const T& operator[](int )const;

		const GTUVector<T>& operator=(const GTUVector<T>& );
		~GTUVector();
	};


	template <class T>
	GTUVector<T>::GTUVector(int inputSize):GTUContainerWithLL<T>(inputSize){
		shared_ptr<node<T>> newHeadNode (new node<T>());
		shared_ptr<node<T>> temp = newHeadNode;
		for(int i=0; i< this->sizeOfContainer-1 ; i++){
			shared_ptr<node<T>> newNode (new node<T>());
			temp->next = newNode;
			newNode->prev = temp;
			temp= temp->next;
		}
		this->containerHead=newHeadNode;
		this->containerTail=temp;
	}

	template <class T>
	GTUIterator<T> GTUVector<T>::insert(const T& value){
		if(this->sizeOfContainer == this->MAX_SIZE)
			throw bad_param("MAX_SIZE reached!");

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
	GTUIterator<T> GTUVector<T>::insert(const GTUIterator<T>& it, const T& value){
		if(this->sizeOfContainer == this->MAX_SIZE)
			throw bad_param("MAX_SIZE reached!");

		shared_ptr<node<T>> temp = this->containerHead ;
		shared_ptr<node<T>> newNode (new node<T>());
		newNode->data = value;

		for(GTUIterator<T> i=this->begin() ; i!=it ; i++)
			temp = temp->next;

		GTUIterator<T> tempIt=this->begin();
		if(tempIt != it)
			temp->prev->next = newNode;
		else
			this->containerHead = newNode;

		newNode->prev = temp->prev;
		newNode->next = temp;
		temp->prev = newNode;	
		this->sizeOfContainer++;

		return GTUIterator<T>(newNode);
	}


	template <class T>
	const GTUVector<T>& GTUVector<T>::operator=(const GTUVector<T>& other){
		if(this == &other)
			return *this;

		GTUContainerWithLL<T>::operator=(other);
		return *this;
	}


	template <class T>
	T& GTUVector<T>::operator[](int index){
		shared_ptr<node<T>> temp = this->containerHead ;
		for(int i=0 ; i<index ; i++)
			temp=temp->next;

		return temp->data;
	}

	template <class T>
	const T& GTUVector<T>::operator[](int index)const{
		shared_ptr<node<T>> temp = this->containerHead ;
		for(int i=0 ; i<index ; i++)
			temp=temp->next;

		return temp->data;
	}



	template <class T>
	GTUVector<T>::~GTUVector(){
		this->clear();
	}

}

#endif