#ifndef _LIST_HPP
#define _LIST_HPP

#include "kernel.hpp"

template<typename T> class list_iterator;

template<typename T> class list{
private:
	friend class list_iterator<T>;
	struct list_node{
		T value;
		list_node *next, *prev;
		list_node(const T val, list_node *n=NULL, list_node *p=NULL) : value(val), next(n), prev(p){
			if(next){
				next->prev=this;
			}
			if(prev){
				prev->next=this;
			}
		}

		void remove(){
			if(next){
				next->prev=prev;
			}
			if(prev){
				prev->next=next;
			}
		}
	} *head, *tail;
public:
	typedef list_iterator<T> iterator;

	void add(const T value){
		if(!head){
			head=new list_node(value);
			return;
		}
		list_node *node=head;
		while(node->next) node=node->next;
        node->next=new list_node(value, NULL, node);
        tail=node->next;
	}

	list_iterator<T> begin(){
		return list_iterator<T>(head);
	}

	list_iterator<T> end(){
		return list_iterator<T>(tail);
	}

	void remove(list_iterator<T> itr){
		if(itr.node->prev)itr.node->prev->next=itr.node->next;
		if(itr.node->next)itr.node->next->prev=itr.node->prev;
		if(itr.node==head) head=itr.node->next;
		if(itr.node==tail) tail=itr.node->prev;
		delete itr.node;
	}
};

template<typename T> class list_iterator{
private:
	friend class list<T>;
	typedef typename list<T>::list_node node_type;
	node_type *node;
	typedef list_iterator<T> this_type;
	list_iterator(node_type *n) : node(n) {}
public:

	this_type operator++(){
		node=node->next;
		return *this;
	}
	this_type operator++(int){
		this_type ret=*this;
		++(*this);
		return ret;
	}
	operator bool(){
		return node==NULL;
	}
	this_type operator--(){
		node=node->prev;
		return *this;
	}
	this_type operator--(int){
		this_type ret=*this;
		--(*this);
		return ret;
	}
	T operator *(){
		return node->value;
	}
	T* operator->(){
		return &node->value;
	}
	operator T*(){
		return &node->value;
	}
};

#endif