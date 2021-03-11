#ifndef GTUCONTAINERWITHLL_H
#define GTUCONTAINERWITHLL_H

#include<iostream>
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "GTUContainer.h"
#include "node.h"

using namespace std;

namespace GTU_PKGZ{

	template <class T>
	class GTUContainerWithLL:public GTUContainer<T>{
	public:
		GTUContainerWithLL(int sizeInput):containerHead(nullptr),containerTail(nullptr),sizeOfContainer(sizeInput){}
		GTUContainerWithLL(const GTUContainerWithLL<T>&);
		virtual GTUIterator<T> insert(const T&) = 0;
		void erase(GTUIterator<T>&);
		void clear();
		bool empty()const;
		int size()const;
		int max_size()const;
		GTUIterator<T> begin();
		GTUIterator<T> end();
		GTUIteratorConst<T> begin()const;
		GTUIteratorConst<T> end()const;
		
		const GTUContainerWithLL<T>& operator=(const GTUContainerWithLL<T>&);
		virtual ~GTUContainerWithLL(){}
		

	protected:
		shared_ptr<node<T>> containerHead;
		shared_ptr<node<T>> containerTail;
		int sizeOfContainer;
		const int MAX_SIZE = 1000;

	private:
		void copyFromOther(const GTUContainerWithLL<T>&);
			
	};

	template <class T>
	GTUContainerWithLL<T>::GTUContainerWithLL(const GTUContainerWithLL<T>& other):containerHead(nullptr),containerTail(nullptr),sizeOfContainer(other.sizeOfContainer){
		if(sizeOfContainer > 0){
			copyFromOther(other);
		}
	}

	template <class T>
	void GTUContainerWithLL<T>::clear(){
		if(sizeOfContainer ==0)
			return;

		shared_ptr<node<T>> temp = containerHead->next;
		while(temp !=nullptr){
			temp->prev->next = nullptr;
			temp->prev = nullptr;
			temp = temp->next;
		}

		containerHead = nullptr;
		containerTail = nullptr;
		sizeOfContainer = 0;
	}

	template <class T>
	const GTUContainerWithLL<T>& GTUContainerWithLL<T>::operator=(const GTUContainerWithLL<T>& other){
		if(this == &other)
			return *this;

		clear();
		copyFromOther(other);
		sizeOfContainer = other.sizeOfContainer;
	}


	template <class T>
	void GTUContainerWithLL<T>::erase(GTUIterator<T>& it){
		if(sizeOfContainer > 0){
			shared_ptr<node<T>> temp = this->containerHead ;
			for(GTUIterator<T> i=this->begin() ; i!=it ; i++)
				temp = temp->next;

			if(temp != containerHead)
				temp->prev->next = temp->next;	
			if(temp != containerTail)
				temp->next->prev = temp->prev;
			if(temp == containerHead )
				containerHead = temp->next;
			if(temp == containerTail )
				containerTail = temp->prev;

			temp->prev = nullptr;
			temp->next = nullptr;
			sizeOfContainer--;
		}
	}


	template <class T>
	GTUIterator<T> GTUContainerWithLL<T>::begin(){
		return GTUIterator<T>(this->containerHead);
	}

	template <class T>
	GTUIterator<T> GTUContainerWithLL<T>::end(){
		return GTUIterator<T>(this->containerTail->next);
	}

	template <class T>
	GTUIteratorConst<T> GTUContainerWithLL<T>::begin()const{
		return GTUIteratorConst<T>(this->containerHead);
	}

	template <class T>
	GTUIteratorConst<T> GTUContainerWithLL<T>::end()const{
		return GTUIteratorConst<T>(this->containerTail->next);
	}

	template <class T>
	bool GTUContainerWithLL<T>::empty()const{
		if(sizeOfContainer > 0)
			return false;
		else 
			return true;
	}

	template <class T>
	int GTUContainerWithLL<T>::size()const{ 
		return sizeOfContainer;
	}

	template <class T>
	int GTUContainerWithLL<T>::max_size()const{ 
		return MAX_SIZE;
	}

	template <class T>
	void GTUContainerWithLL<T>::copyFromOther(const GTUContainerWithLL<T>& other){
		shared_ptr<node<T>> newHeadNode (new node<T>());
		shared_ptr<node<T>> temp = newHeadNode;
		shared_ptr<node<T>> tempForOther = other.containerHead;
		temp->data = tempForOther->data;

		for(tempForOther = tempForOther->next; tempForOther != nullptr ; tempForOther=tempForOther->next){
			shared_ptr<node<T>> newNode (new node<T>());
			newNode->data = tempForOther->data;
			temp->next = newNode;
			newNode->prev = temp;
			temp= temp->next;

		}
		this->containerHead=newHeadNode;
		this->containerTail=temp;
	}






}






#endif